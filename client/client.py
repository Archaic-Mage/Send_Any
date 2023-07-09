import socket
import json
import struct

def receive_response(sock):
    """!
    The function receives the response from the server and returns it.
    """
    data_size = struct.unpack('>I', sock.recv(4))[0]
    received_payload = b""
    reamining_payload_size = data_size

    while reamining_payload_size != 0:
        received_payload += sock.recv(reamining_payload_size)
        reamining_payload_size = data_size - len(received_payload)
    resp = json.loads(received_payload)
    return resp

def __main__():
    
    host = "127.0.0.1"
    port = 8080
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((host, port))
        txt = input("Enter your message: ")
        message = json.dumps({"message": txt})
        sock.sendall(struct.pack('>I', len(message)))
        sock.sendall(bytes(message,encoding="utf-8"))
        data = receive_response(sock)
        print(data)
        sock.close()
        
if __name__ == "__main__":
    __main__()

