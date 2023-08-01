#!/bin/bash

# Step 1: Compile the C++ code
g++ main.cpp -lboost_system -lboost_thread -pthread -o websocket_server

# Step 2: Run the C++ WebSocket server in the background
./websocket_server &

# Step 3: Run the main.css interface file
xdg-open main.css

