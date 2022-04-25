#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res); // yields a pointer to a linked list called res
                                                                                                                   //returns non-zero if there was an error 
int status;
struct addrinfo hints;
struct addrinfo *serverInfo;

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; //will operate with both IPv4 or IPv6
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE; // assigns the address of my local host to the socket structures

if ((status = getaddrinfo(NULL, "3490", &hints, &serverInfo)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(stat));//the last parameter will allow us to print the error
                                                                   //Else serverInfo points to a linked list of struct 'addrinfo'     
    exit(1);
}
//Server info will now point to a linked lists of struct addresses
freeaddrinfo(servinfo);//Empies the linked list

//Everything above this line only sets up the structures that will be used.
status = getaddrinfo("www.example.net", "3490", &hints, &serverInfo);