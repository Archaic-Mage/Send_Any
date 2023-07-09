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
    """!
    The function is used to test the server.
    """
    port = 8080
    sock = socket.socket()
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(('', port))
    sock.listen(2)
    
    while True:
        print(f"Running on {port}")
        connection, address = sock.accept()
        data = receive_response(connection)
        message = json.dumps(data)
        # first send the length of the message
        connection.send(struct.pack('>I', len(message)))
        # then send the message
        connection.send(bytes(message, encoding="utf-8"))
        connection.close()


if __name__ == "__main__":
    __main__()