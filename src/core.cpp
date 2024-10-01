#include <iostream>
#include <fstream>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>
#include "core.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json; // Alias untuk nlohmann::json

void load_config(const std::string& filename) {
    std::ifstream config_file(filename);
    if (!config_file.is_open()) {
        std::cerr << "Could not open config file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    json config;
    config_file >> config;

    PORT = config["port"];
    MAX_CLIENTS = config["max_clients"];
    MAX_THREADS = config["max_threads"];
}

void handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            break; // Client disconnected
        }
        buffer[bytes_received] = '\0';

        // Parse JSON message
        std::string message(buffer);
        try {
            json j = json::parse(message); // Parsing JSON message

            std::string client_id = j["client_id"];
            std::string channel = j["channel"];
            json payload = j["payload"];

            // Handle message based on action
            std::string action = j["action"];
            if (action == "publish") {
                std::cout << "Received data from " << client_id << " on channel " << channel << ": "
                          << payload.dump() << std::endl;
            } else if (action == "subscribe") {
                if (client_channels[client_id].size() < 2) {
                    client_channels[client_id].push_back(channel);
                    std::cout << client_id << " subscribed to " << channel << std::endl;
                } else {
                    std::cout << client_id << " already has max channels subscribed." << std::endl;
                }
            }
        } catch (const nlohmann::json::parse_error& e) { // Pastikan ini benar
            std::cerr << "Parse error: " << e.what() << std::endl;
        }
    }
    close(client_socket);
}
