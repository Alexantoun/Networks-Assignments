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
#include <fcntl.h>

const static int MODESIZE = 103;
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
    
    int incomingSocket = 0;
    int addrlen = 0;

    char mode [MODESIZE]; //100 Characters + Carriage return + LineFeed + nullterminator
    memset(mode, 0, MODESIZE);
    while(1){
        listen(serverSocket, 1);    //listen on a socket and will accept 1 connection
        addrlen = sizeof(struct sockaddr_storage);
        incomingSocket = accept(serverSocket, (struct sockaddr*)&remoteAddress, &addrlen);
        recv(incomingSocket, mode, 103, 0); //recv_len == 0 iff client disconnects
        printf("Received %s\n", mode);
        
        if (strcmp(mode, "1")==0){
            send(incomingSocket, returnEcho, strlen(returnEcho), 0);
        }
        else if (strcmp(mode, "2")==0){
            off_t remaining, sentbytes, read_buffer;
            char buffer[1024] = {0};
            char fileSize[1024] = {0};
            int fileDescriptor = open("test.txt", O_RDONLY);
            struct stat st;
            stat("test.txt", &st);
            sprintf(fileSize, "%ld",st.st_size);
            send(incomingSocket, fileSize, strlen(fileSize), 0);
            remaining = st.st_size;

            while(remaining > 0){
                read_buffer = read(fileDescriptor, buffer, 1024);
                sentbytes = send(incomingSocket, buffer, read_buffer, 0);
                remaining = remaining - sentbytes;
                memset(buffer, 0, strlen(buffer));
            }
        }
        else if(strcmp(mode,"close")==0){
            send(incomingSocket, "Goodbye!", strlen("Goodbye"),0);
            break;
        }
        else{
            printf("Sending %s\n", mode);
            char response [113] = "You sent: ";
            strcat(response, mode);
            send(incomingSocket, response, strlen(response), 0);
        }
        memset(mode, 0, 103);
    }
    printf("Goodbye\n");

    return 0;
}