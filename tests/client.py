import socket

"""
    usage: the function creates the client socket
    in: no
    out: the socket
"""
def createSocket():
    port = 0

    while port < 1024 or port > 65535:
        port = int(input("Enter the port: "))

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverAddress = ("127.0.0.1", port)
    sock.connect(serverAddress)

    return sock

def main():
    isConnected = True

    try:
        sock = createSocket()
    except:
        isConnected = False
        print("the server is currently down...")

    if isConnected:
        response = sock.recv(1024)
        if response == "Hello":
            sock.sendall(response)

if __name__ == '__main__':
    main()