#ifndef CORE_H
#define CORE_H

#include <string>
#include <unordered_map>
#include <vector>

// Fungsi untuk memuat konfigurasi dari file JSON
extern "C" {
    void starting_point();
}

// Fungsi untuk memuat konfigurasi dari file JSON
void load_config(const std::string& filename);
// Fungsi untuk menangani koneksi klien
void handle_client(int client_socket);

#endif