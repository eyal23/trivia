import socket
import json
import bson

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

"""
    usage: the function constructs a binary-formated message
    in: the message code, the json data
    out: the binary-formated message
"""
def constructMessage(code, jsonData):
    binaryJson = bson.dumps(jsonData)

    request = bytearray()
    request.append(code)
    dataSize = len(binaryJson).to_bytes(4, byteorder = "little");

    for byte in dataSize:
        request.append(byte)

    for byte in binaryJson:
        request.append(byte)

    return request

"""
    usage: the function sends a request to the server, and recives it's response
    in: the socket, the request
    out: none
"""
def sendAndRecive(sock, request):
    sock.sendall(request)
    response = sock.recv(1024)

    print("response code: " + str(response[0]))
    print("data size: " + str(int.from_bytes(response[1 : 5], "little")))
    print("data: " + str(bson.loads(response[5:])))

"""
    usage: the function sends a "login request"
    in: the socket
    out: none
"""
def sendLoginRequest(sock):
    jsonData = {
        "username": "user1",
        "password": "1234"
    }

    sendAndRecive(sock, constructMessage(1, jsonData))

"""
    usage: the function sends a "sign up request"
    in: the socket
    out: none
"""
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
        while True:
            choice = input("""1. login request
2. sign up request
enter you choice: """)

            if choice == "1":
                sendLoginRequest(sock)
            elif choice == "2":
                sendSingUpRequest(sock)
            else:
                print("ilegal choice!")

if __name__ == '__main__':
    main()