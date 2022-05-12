//So you first need to telnet to the IP address and correct port number for the client to work 
//This program just makes a connection to a server and sends something 

#include <stdio.h>
#include <sys/socket.h> //This allows us to make a socket
#include <arpa/inet.h>  //This lets us specify IP addresses
#include <unistd.h>     // This gives us some macros to use
#include <string.h>     //You know this one
#include <netdb.h>      
#include <getopt.h>     //gives us command line arguments much easier
#include <fcntl.h>

int main(int argc, char **argv){
    struct sockaddr_in serv_addr;      
    serv_addr.sin_family = AF_INET;     
    serv_addr.sin_port = htons(4321);  
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    char buffer[1024] = {0};
    int sock;  
    sock = socket(AF_INET, SOCK_STREAM, 0);     // creates a socket
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock, argv[1], strlen(argv[1]), 0);
    if(argc > 1){
        if(strcmp(argv[1], "2") == 0){
            printf("File trasnfer, size is: ");

            off_t fileSize, offset;
            int fileDescriptor = open("recieved.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

            recv(sock, buffer, 1024, 0);
            fileSize = atoi(buffer);
            printf("%ld\n", fileSize);
            
            while (fileSize > 0){
                memset(buffer, 0 ,strlen(buffer));
                offset = recv(sock, buffer, 1024, 0);
                write(fileDescriptor, buffer, offset);
                fileSize = fileSize - offset;
            }
            close(fileDescriptor);
            printf("Done\n");
        }
        else{
            printf("Sending %s\n",argv[1]);
            send(sock, argv[1], strlen(argv[1]), 0);
            recv(sock, buffer, 1024, 0);  
            printf("%s\n",buffer); 
        }
    }
    //send(sock, argv[1], strlen(argv[1]), 0);
    //recv(sock, buffer, 1023, 0);  
    //printf("%s\n",buffer);                    
 
    return 0;
}