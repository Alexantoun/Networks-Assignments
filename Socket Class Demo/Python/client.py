import socket

host = "192.168.192.1"  #hardcoding variables for debugging simplicity
port = 2345
def main():
    #first we need to create a socket that server can commune with 
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        message=input('Type message: ')
        message +="\r\n"
        s.connect((host,port))
        #(host, port) is a tuple --> list that cannot be changed
        #[host, port] is a list
        s.send(message.encode())    #The decode function turns the string 
                                    #into a byte string

                                    #send will allow you to send anything as
                                    #long as its in bytes
        data = s.recv(1024)
        print(f"Recieved back from server: {data.decode()}")#data.decode() is just making it humanreadable -> dropping the data variables
        #We are creating the socket, then we are waiting for connection if we are accepted we send hello world, then we 
        #recieve whatever, and spit it back out on the client machine

main()