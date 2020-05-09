import socket
import json

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

def constructMessage(code, jsonData):
    bsonData = json.dumps(jsonData).encode("utf-8")

    message = bytearray()
    message.append(code)
    message.append(len(bsonData))

    for byte in bsonData:
        message.append(byte)

    return message

def sendAndRecive(sock, message):
    sock.sendall(message)
    response = sock.recv(1024).deocde("utf-8")
    print(response)

def sendLoginRequest(sock):
    jsonData = {
        "username": "user1",
        "password": "1234"
    }

    sendAndRecive(sock, constructMessage(1, jsonData))

def sendSingUpRequest(sock):
    jsonData = {
        "username": "user1",
        "password": "1234",
        "email": "user1@gmail.com"
    }

    sendAndRecive(sock, constructMessage(2, jsonData))

def main():
    isConnected = True

    try:
        sock = createSocket()
    except:
        isConnected = False
        print("the server is currently down...")

    if isConnected:
        response = sock.recv(1024).decode()
        if response == "Hello":
            sock.sendall(response.encode())
        while True:
            choice = input("""1. login request
            2. sign up request
            enter you choice: """)

            if choice == 1:
                sendLoginRequest(sock)
            elif choice == 2:
                sendSingUpRequest(sock)
            else:
                print("ilegal choice!")

if __name__ == '__main__':
    main()