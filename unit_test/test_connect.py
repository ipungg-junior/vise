import socket
import json

def start_client():
    # Membuat socket TCP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Menghubungkan ke server
    client_socket.connect(('10.251.11.66', 9911))

    # Membuat data dalam format JSON
    data = {
        "client_id": "client_1",
        "channel": "news",
        "payload": {
            "message": "Hello, this is a test message!"
        },
        "action": "publish"
    }

    # Mengubah data menjadi string JSON dan mengirim
    json_data = json.dumps(data).encode('utf-8')  # Encode to bytes
    client_socket.sendall(json_data)

    # Menerima balasan dari server
    response = client_socket.recv(1024)
    print(f"Balasan dari server: {response.decode()}")

    # Menutup koneksi
    client_socket.close()

if __name__ == "__main__":
    start_client()

