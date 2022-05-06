import socket   #low level networking interface for python
                #supports bluetooth protocols too

def main():
    host = input("Enter my IP: ")
    port = 2345
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #like s = socket.socket... except automatically handles closing
        s.bind((host,port)) #Binding to this host and port
        while True:
            s.listen()  #returns a positive integer for success, negative for an issue
            print("Waiting for connection...")
            conn, addr = s.accept() #waiting loop, waiting to accept a new connection
            while True:
                data = conn.recv(1024)
                print(f"{data.decode()}")
                if not data or data.decode()=="close\r\n":
                    break   #Go back to wait-for-connection state
                #conn.sendall(data)  #parrot what we recieved back to client
                                    #Returns a connection, and address
            print(f"Recieved connection from {addr}")
main()      
