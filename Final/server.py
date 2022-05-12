import socket   #low level networking interface for python
                #supports bluetooth protocols tojo
import csv

def main():
    host = "192.168.1.6" #input("Enter my IP: ")
    port = 2345
    recieved = ""
    arduinoList = list()
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #like s = socket.socket... except automatically handles closing
        s.bind((host,port)) #Binding to this host and port
        while True:
            s.listen()  #returns a positive integer for success, negative for an issue
            print("Waiting for connection...")
            conn, addr = s.accept() #waiting loop, waiting to accept a new connection
            print(f"Recieved connection om {addr}")
            x=0
            while True:
                data = conn.recv(1024)
                recieved = data.decode()
                #print(f"{recieved}\n")  #if this fails then change recieved to data.decode
                if recieved=="close\r\n":
                    break   #Go back to wait-for-connection state
                arduinoList.append(recieved)
                x+=1
                if x==3:
                    x = x%3
                    writer.writerow(arduinoList)
                    print(arduinoList)
                    arduinoList.clear() 

header = ['Button', 'Temp-C', 'Humidity-%']
file = open('Arduino Data.csv', 'w')
with open('arduinoData', 'w') as f:    
    writer = csv.writer(f)
    writer.writerow(header)
    main()      
    