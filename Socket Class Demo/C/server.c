//What is happening is this program creates a socket, and binds to that socket 
//then continues to listen

//WATCH THE LECTURE ON 04/11/2022 YOU'RE AT TIME 21:53
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


int main(int argc, char **argv){
    struct addrinfo hints, *res;
    struct sockaddr_storage remoteAddress;
    int serverSocket;
    char buffer[1024] = {0};
    //This will set a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&hints, 0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "12345", &hints, &res);       //What is looks up, a port, and then a addrinfo
    //now we tell it to bind to a port
    bind(serverSocket, res->ai_addr, res->ai_addrlen);      //bind takes in a socket, and specific address, 
                                                            //and then the length of the address

    //Now that we have bind, we now tell it to listen to connections, listen(takes a socket number, and then a backlog num)
    listen(serverSocket, 1);    //listens on a socket socket, and the '1' indicates how many connections it can listen to

    int addrlen = sizeof(struct sockaddr_storage);
    int incomingSocket = accept(serverSocket, (struct sockaddr*)&remoteAddress, &addrlen);    //We need to pass an instance of the struct that represent the remote address
                                                                                            // The accept needs to have the clients IP address so that you can talk back
    printf("Accepted Connection\n");
    //At this point all we do is accept a connection then end both the connection and the program
    
    while(1){
        //Now we will try to recieve some sort of information (buffer) from the client socket (incomingSocket) and store the 
        int recv_len = recv(incomingSocket, buffer, 1024, 0);
        printf("recieved message: %s\n", buffer);
        char returnMessage[1024] = "Message Recieved: ";
        strcat(returnMessage, buffer);
        printf("%s\n",returnMessage);
        send(incomingSocket, returnMessage, strlen(returnMessage),0);
        returnMessage[0] = '\0';
    }
    return 0;
}