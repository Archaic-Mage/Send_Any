import socket
import json
import struct

TEST = "/home/mage/Documents/send_any/test"

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
    return received_payload

def open_and_read_file(filename):
    with open(TEST + "/" + filename, "rb") as f:
        data = f.read()
        return data

def __main__():
    
    host = "127.0.0.1"
    port = 8080
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((host, port))
        file_name = input("Enter file name: ")
        data = open_and_read_file(file_name)
        file_name = bytes(file_name, "utf-8")
        #send the file name
        sock.sendall(struct.pack('>I', len(file_name)))
        sock.sendall(file_name)
        #send the file data
        sock.sendall(struct.pack('>I', len(data)))
        sock.sendall(data)
        data = receive_response(sock)
        print(data.decode("utf-8"))
        sock.close()
        
if __name__ == "__main__":
    __main__()

