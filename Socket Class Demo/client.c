//So you first need to telnet to the IP address and correct port number for the client to work 
//This program just makes a connection to a server and sends something 

#include <stdio.h>
#include <sys/socket.h> //This allows us to make a socket
#include <arpa/inet.h>  //This lets us specify IP addresses
#include <unistd.h>     // This gives us some macros to use
#include <string.h>     //You know this one
#include <netdb.h>      
#include <getopt.h>     //gives us command line arguments much easier

int main(int argc, char **argv){
    struct sockaddr_in serv_addr;       //Not defining a struct, in C when you use a struct, you must specifiy that it is a struct.
    serv_addr.sin_family = AF_INET;     //Need to give the family type of our sockaddr
    serv_addr.sin_port = htons(12345);  //We specify the port we want to connect to --> networks use big endian --> htons = host to networks 
                                        //So htons is converting the number to big endian
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.3"); // the ip address that you want to connect to

    char buffer[1024] = "\0";

    int sock;   //socket function below returns a socket
                //Socket function is int socket(int domain, int type, int protocol), specify 0 for protocol 
                //to mean "any" from <sys/socket>

    sock = socket(AF_INET, SOCK_STREAM, 0);     // creates a socket
    char *name = "Alexander";                   //C-string the C way
    
    //int connect(int sockfd, struct sockaddr, int addrlen)
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); 

    //send you give it a socket, a mesasge, the length of message, then finally some options or 0 for no options
    //printf("Our string is: %s\n", name);
    send(sock, name, strlen(name), 0);
    recv(sock, buffer, 1024,0 );  //Recv recieves a message from a socket(sock) stores it into a buffer (buffer), 
                                //then len is the length of the recieve signal the zero is for no flags

    //Instead of recv() try this --> read(sock,buffer, 16);
    printf("%s\n",buffer);                    
 
    return 0;
}