#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>

// Fungsi untuk memuat konfigurasi dari file JSON
void load_config(const std::string& filename);

// Fungsi untuk menangani koneksi klien
void handle_client(int client_socket);



#include <unordered_map>
// Struktur untuk menyimpan saluran klien
extern std::unordered_map<std::string, std::vector<std::string>> client_channels;

#endif // MQTT_SERVER_H
