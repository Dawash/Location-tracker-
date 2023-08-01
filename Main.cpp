#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    std::string ngrokAuthorities;
    std::cout << "Enter your ngrok auth token: ";
    std::getline(std::cin, ngrokAuthorities);

    // Your logic to host the HTML page using ngrok goes here...
    std::string hostedLink = "https://abc123.ngrok.io"; // Replace with actual hosted link

    std::cout << "HTML page hosted at: " << hostedLink << std::endl;
    std::cout << "Waiting for victim's response..." << std::endl;
    
    // Simulating victim's response (1 for Allow, 0 for Deny)
    int victimResponse;
    std::cout << "Victim pressed Allow (1) or Deny (0): ";
    std::cin >> victimResponse;

    if (victimResponse == 1) {
        // Your logic to get user's location link goes here...
        std::string locationLink = "https://example.com/location"; // Replace with actual location link

        std::cout << "Victim's location link: " << locationLink << std::endl;
    } else {
        std::cout << "Victim denied the request for location" << std::endl;
    }

    return 0;
}
