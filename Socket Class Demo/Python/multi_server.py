#this allows us to multi-thread a server, to handle multiple connections
from logging import exception
from operator import length_hint
import socket
import select
import time

BUFFSIZE = 1024
HEADER_LENGTH = 10
def main():
    host = "192.168.1.6"
    port = 2345
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  
        s.bind((host, port))
        s.listen()          
        socket_list = [s]   #list of sockets so OS can handle it
        clients = {}        #this is creating a key value pair, called a dictionary
        
        while True:
            read_socket, _ ,exception_socket = select.select(socket_list, [], socket_list)
            for notified_socket in read_socket:
                if notified_socket == s: #if theres a new connection coming in? Accept!
                    conn,addr = s.accept()
                    print(f"Accepted new connection from: {addr}")
                    print('\n\n\n\n')
                    socket_list.append(conn) #append new connection to the list
                    message_header = conn.recv(HEADER_LENGTH)
                    username = conn.recv(int(message_header.decode().strip()))  #we take message header, decode it, and strip whitespace, then cast to int
                    clients[conn] = username.decode()
                    print(f"{clients}")

                else:   #Otherwise we are working with an established connection
                    message_header = notified_socket.recv(HEADER_LENGTH)
                    message = notified_socket.recv(int(message_header.decode().strip()))
                    
                    username = clients[notified_socket]
                    username_length = len(username)
                    message_header = f"{username_length:,{HEADER_LENGTH}}".encode()
                    print(f"{message}")

                    for k,v in clients.items():
                        if k!=notified_socket:
                            k.send(message_header+username.encode())
                            message_header2 = f"{message:<{HEADER_LENGTH}}".encode()
                    
main()