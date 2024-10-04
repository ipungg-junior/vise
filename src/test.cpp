#include <iostream>
#include <fstream>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>
#include "test.h"
#include <nlohmann/json.hpp>


int PORT, MAX_CLIENTS, MAX_THREADS;

// Struktur untuk menyimpan saluran klien
std::unordered_map<std::string, std::vector<std::string>> client_channels;

void starting_point() {
    
    load_config("config.json");

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error creating socket" << std::endl;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        close(server_socket);
        
    }

    if (listen(server_socket, MAX_CLIENTS) == -1) {
        std::cerr << "Error listening on socket" << std::endl;
        close(server_socket);
        
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket == -1) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }
        std::cout << "Client connected: " << client_socket << std::endl;

        std::thread(handle_client, client_socket).detach(); // Handle client in a new thread
    }

    close(server_socket);
    
}


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

    }
    close(client_socket);
}