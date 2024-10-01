#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <arpa/inet.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int PORT;
int MAX_CLIENTS;
int MAX_THREADS;

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

        // Process message
        std::string message(buffer);
        std::cout << "Received: " << message << std::endl;

        // Send response (echo in this case)
        send(client_socket, buffer, bytes_received, 0);
    }
    close(client_socket);
}

int main() {
    // Load configuration
    load_config("config.json");

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, MAX_CLIENTS) == -1) {
        std::cerr << "Error listening on socket" << std::endl;
        close(server_socket);
        return 1;
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
    return 0;
}
