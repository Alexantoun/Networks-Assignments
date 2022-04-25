#this allows us to multi-thread a server, to handle multiple connections
from logging import exception
import socket
import select
import time

BUFFSIZE = 1024
HEADER_LENGTH = 10
def main():
    host = "127.0.0.1"
    port = 1234
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
                    socket_list.append(conn) #append new connection to the list
                    message_header = conn.recv(HEADER_LENGTH)
                    username = conn.recv(int(message_header.decode().strip()))  #we take message header, decode it, and strip whitespace, then cast to int
                    clients[conn] = username.decode()
                    print(f"{clients}")
                else:   #Otherwise we are working with an established connection
                    #recieve new message from existing connection
                    #message = notified_socket.recv(BUFFSIZE)
                    #print(f"Recieved {message.decode()}")
                    #time.sleep(2)
                    message_header = conn.recv(HEADER_LENGTH)
                    message = conn.recv(int(message_header.decode().strip()))
                    print(f"{message.decode()}")
                    for k,v in clients.items():
                        if k!=notified_socket:
                            k.send(message)
                    

main()