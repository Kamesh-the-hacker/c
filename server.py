import socket

HOST = "0.0.0.0"
PORT = 54321

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)

print("[+] Server listening on port", PORT)
client, addr = server.accept()
print("[+] Connected from", addr)

while True:
    cmd = input("remote@client$ ")

    if cmd.lower() == "exit":
        client.send(b"exit")
        break

    client.send(cmd.encode())
    data = client.recv(16384)

    print(data.decode(errors="ignore"))

client.close()
server.close()
