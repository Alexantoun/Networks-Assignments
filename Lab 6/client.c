#include <stdio.h>
#include <sys/socket.h> //This allows us to make a socket
#include <arpa/inet.h>  //This lets us specify IP addresses
#include <unistd.h>     // This gives us some macros to use
#include <string.h>     //You know this one
#include <netdb.h>      
#include <getopt.h>     //gives us command line arguments much easier

int main(int argc, char **argv){
    struct sockaddr_in serv_addr;
    serv_addr.sin_port = htons(4321);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.6");
    printf("IP Address is 192.168.1.6\n");
    


    return 0;
}