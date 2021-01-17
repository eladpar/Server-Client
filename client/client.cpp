#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "client.hpp"
#include "functions.hpp"


int main(int argc, char *argv[]) {
    int sockfd, portno;
    struct sockaddr_in server_addr = {0};
    struct hostent *server;
    // char buffer[256];
if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
}
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0)
    perror("ERROR opening socket");
portno = atoi(argv[2]);
server = gethostbyname(argv[1]);
if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
}
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = *((long*)server->h_addr);
server_addr.sin_port = htons(portno);

WRQ wrq;

// wrq.Opcode = 21;
strcpy(wrq.FileName, "/home/hana.txt");
strcpy(wrq.TransmissionMode, "octet");
wrq.Opcode = htons((uint16_t)2);
// cout << real << endl;
// strncpy(buffer, "512", 2);
// strncpy(buffer+3, "/home/text.ds", 14);
// strncpy(buffer+17, "octet", 5);

if (sendto(sockfd, &wrq, 200, 0, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 256)
        perror("sendto() sent a different number of bytes than expected");
close(sockfd);
return 0;
}


































// // Client side C/C++ program to demonstrate Socket programming 
// #include <stdio.h> 
// #include <sys/socket.h> 
// #include <arpa/inet.h> 
// #include <unistd.h> 
// #include <string.h> 
// #define PORT 8080 
   
// int main(int argc, char const *argv[]) 
// { 
//     int sock = 0, valread; 
//     struct sockaddr_in serv_addr; 
//     char *hello = "Hello from client"; 
//     char buffer[1024] = {0}; 
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
//     { 
//         printf("\n Socket creation error \n"); 
//         return -1; 
//     } 
   
//     serv_addr.sin_family = AF_INET; 
//     serv_addr.sin_port = htons(PORT); 
       
//     // Convert IPv4 and IPv6 addresses from text to binary form 
//     if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
//     { 
//         printf("\nInvalid address/ Address not supported \n"); 
//         return -1; 
//     } 
   
//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
//     { 
//         printf("\nConnection Failed \n"); 
//         return -1; 
//     } 
//     send(sock , hello , strlen(hello) , 0 ); 
//     printf("Hello message sent\n"); 
//     valread = read( sock , buffer, 1024); 
//     printf("%s\n",buffer ); 
//     return 0; 
// }