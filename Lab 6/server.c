#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>     
#include <string.h>    
#include <netdb.h>      
#include <getopt.h>   
#include <errno.h>
#include <getopt.h>
#include <arpa/inet.h>


const static char* returnEcho = "This is the returned message\n";
const static char* invalidOption = "That wasn't very cash money of you\n";

int main(int argc, char **argv){
    struct addrinfo hints, *results; 
    struct sockaddr_storage remoteAddress;

    int serverSocket;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset (&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    //IPv4 or IPv6...Doesnt matter
    hints.ai_socktype = SOCK_STREAM;    //TCP stream sockets
    hints.ai_flags = AI_PASSIVE;        //Fills in IP for me

    getaddrinfo(NULL, "4321", &hints, &results);    //Fills in the struct information for us
    bind(serverSocket, results->ai_addr, results->ai_addrlen);  //Associate the socket with a specific port
    listen(serverSocket, 1);    //listen on a socket and will accept 1 connection
    int addrlen = sizeof(struct sockaddr_storage);
    int incomingSocket = accept(serverSocket, (struct sockaddr*)&remoteAddress, &addrlen);
    
    char mode [103]; //100 Characters + Carriage return + LineFeed + nullterminator
    memset(mode, '\0', 103);
    int recv_len = -1;
    
    while(recv_len != 0){
        recv_len = recv(incomingSocket, &mode, 102, 0); //recv_len == 0 iff client disconnects
        printf("Recieved %c\n", mode[0]);
        if (mode[0] == '1'){
            send(incomingSocket, returnEcho, strlen(returnEcho), 0);
        }
        else if (mode[0] == '2'){
             send(incomingSocket, "Selected file transfer\n", strlen("Selected file transfer\n"), 0);
        }
        else{
            send(incomingSocket, "You sent: ", strlen("You sent: "), 0);
            send(incomingSocket, &mode, strlen(mode), 0);
        }
        memset(mode, '\0', 103);
    }
    printf("Goodbye\n");

}