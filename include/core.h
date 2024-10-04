#ifndef CORE_H
#define CORE_H

#include <string>
#include <unordered_map>
#include <vector>

// Fungsi untuk memuat konfigurasi dari file JSON
void load_config(const std::string& filename);

// Fungsi untuk menangani koneksi klien
void handle_client(int client_socket);
extern int PORT;
extern int MAX_CLIENTS;
extern int MAX_THREADS;
std::unordered_map<std::string, std::vector<std::string>> client_channels;



#endif // MQTT_SERVER_H
