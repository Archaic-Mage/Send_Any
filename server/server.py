import socket
import json
import struct

TEST_TANSFER_LOC = "/home/mage/Documents/send_any/test_transfer_check"

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

def write_to_file(filename, data, is_new=False):
    """
    The function writes the bytes to the file.
    filename (str): the name of the file to be written to.
    data (bytes): the data to be written to the file.
    is_new (bool): if True, the file will be overwritten.
    """
    mode = "ab" if not is_new else "wb"
    with open(TEST_TANSFER_LOC + "/" + filename, mode) as f:
        f.write(data)

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
        file_name = receive_response(connection).decode("utf-8")
        data = receive_response(connection)
        write_to_file(file_name, data, is_new=True)
        message = b'File received successfully!'
        # first send the length of the message
        connection.send(struct.pack('>I', len(message)))
        # then send the message
        connection.send(message)
        connection.close()


if __name__ == "__main__":
    __main__()