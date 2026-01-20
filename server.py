import socket

HOST = "0.0.0.0"   # Listen on all interfaces
PORT = 54321

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)

print(f"[+] Server listening on port {PORT}")
client, addr = server.accept()
print(f"[+] Connected from {addr}")

while True:
    cmd = input("Enter command (or 'exit'): ")
    if cmd.lower() == "exit":
        client.send(b"exit")
        break

    client.send(cmd.encode())
    data = client.recv(8192)
    print(data.decode(errors="ignore"))

client.close()
server.close()
