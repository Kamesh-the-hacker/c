import socket
import sys

HOST = "0.0.0.0"
PORT = 54321

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)

print("[+] Server listening on port", PORT)
client, addr = server.accept()
print("[+] Connected from", addr)

while True:
    try:
        cmd = raw_input("remote@client$ ")   # Python 2
    except:
        cmd = input("remote@client$ ")       # Python 3

    if cmd.lower() == "exit":
        client.send(cmd.encode())
        break

    client.send(cmd.encode())

    data = client.recv(65535)
    if not data:
        break

    print(data.decode(errors="ignore"))

client.close()
server.close()
