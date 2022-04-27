#This allows us to multi-thread a server, to handle multiple connections
from logging import exception
import socket
import errno
import time

BUFFSIZE = 1024
MESSAGE_LEN = 10
def main():
    host = "127.0.0.1"
    port = 1234
    username = input("Please enter your username: ")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.setblocking(False)
        username_length = len(username)
        message_header = f"{username_length:<{MESSAGE_LEN}}".encode()    #will take the username length and make a padding to fill in the max size
                                                                #size of the username
        print(f"'{message_header.decode()}'")
        s.send(message_header+username.encode())
        #message=input('Type a message: ')
        #message += "\r\n"
        #s.send(message.encode())
        while True:
            try:
                message = input(f"{username} > ")
                message_length = len(message)
                message_header = f"{message_length:<{MESSAGE_LEN}}".encode()
                print(f"'{message_header}'")
                s.send(message_header+(message.encode()))

                while True:
                    message_header = s.recv(MESSAGE_LEN)
                    recv_username = s.recv(int(message_header.decode().strip()))    

                    message_header = s.recv(MESSAGE_LEN)
                    message = s.recv(int(message_header.decode().strip()))
                    print(f"Recieved from {recv_username.decode()} : {message.decode()}")
                    
            except IOError as e:
                if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                    sys.exit()
                    continue

main()