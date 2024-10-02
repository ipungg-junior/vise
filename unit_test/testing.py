import socket

def start_server():
    # Membuat socket TCP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Mengikat socket ke alamat dan port
    server_socket.bind(('10.251.11.66', 9911))
    server_socket.listen()

    print("Server sedang menunggu koneksi...")

    while True:
        # Menerima koneksi dari klien
        client_socket, address = server_socket.accept()
        print(f"Koneksi dari {address} telah diterima.")

        # Menerima data dari klien
        data = client_socket.recv(1024)
        print(f"Data yang diterima: {data.decode()}")

        # Mengirimkan balasan ke klien
        client_socket.sendall(b'Selamat datang di server TCP!')

        # Menutup koneksi
        client_socket.close()

if __name__ == "__main__":
    start_server()

