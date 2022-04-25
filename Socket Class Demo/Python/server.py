import socket   #low level networking interface for python
                #supports bluetooth protocols too

#Python makes this way easier, specify a host, specify a port --> Done!
def main():
    host = "192.168.192.1"
    port = 2345
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #like s = socket.socket... except automatically handles closing
        s.bind((host,port))     #Binding to this host and port
        s.listen()              #returns a positive integer for success, negative for an issue
        while True:
            conn, addr = s.accept() #waiting loop, waiting to accept a new connection
                                    #Returns a connection, and address
            print(f"Recieved connection from {addr}")
            while True:
                data = conn.recv(1024)
                print(f"Recieved {data} bytes") #Say on server machine that we recieved some string
                if not data:
                    break   #once client breaks connection, we break out of loop
                conn.sendall(data)  #Parrot what we recieved back to client
main()