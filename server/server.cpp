#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>

#define ECHOMAX 255 

using namespace std;

void error(string msg) {
    cerr << msg << endl;
    exit(0);
}
//**************************************************************************************
// function name: main
// Description: main function
//**************************************************************************************
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "ERROR, no port provided" << endl;
    }

    int sock; /* Socket */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned int cliAddrLen; /* Length of incoming message */
    char echoBuffer[ECHOMAX]; /* Buffer for echo string */
    unsigned short echoServPort; /* Server port */
    int recvMsgSize; /* Size of received message */

    echoServPort = atoi(argv[1]);

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        error("socket() failed");
    }
    
    /* Construct local address structure */

    /* Zero out structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    /* Internet address family */
    echoServAddr.sin_family = AF_INET;
    /* Any incoming interface */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Local port */
    echoServAddr.sin_port = htons(echoServPort);
    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    {
        error("bind() failed");
    }
     


    // for (;;) 
    // { /* Run forever */
        /* Set the size of the in-out parameter */
        cliAddrLen = sizeof(echoClntAddr);
        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
                            (struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
        {
            error("recvfrom() failed");
        }
        
        printf("Handling client %s\n",inet_ntoa(echoClntAddr.sin_addr));
		printf("the message is %s", echoBuffer);
        /* Send received datagram back to the client */
        // if (sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize)
       	// 	 error("sendto() sent a different number of bytes than expected");
    // }
    /* NOT REACHED */
} 

// // Server side C/C++ program to demonstrate Socket programming 
// #include <unistd.h> 
// #include <stdio.h> 
// #include <sys/socket.h> 
// #include <stdlib.h> 
// #include <netinet/in.h> 
// #include <string.h> 
// #define PORT 8080 
// int main(int argc, char const *argv[]) 
// { 
// 	int server_fd, new_socket; 
// 	struct sockaddr_in address; 
// 	int opt = 1; 
// 	int addrlen = sizeof(address); 
// 	char buffer[1024] = {0}; 
// 	const char *hello = "Hello from server"; 
	
// 	// Creating socket file descriptor 
// 	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
// 	{ 
// 		perror("socket failed"); 
// 		exit(EXIT_FAILURE); 
// 	} 
	
// 	// Forcefully attaching socket to the port 8080 
// 	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
// 												&opt, sizeof(opt))) 
// 	{ 
// 		perror("setsockopt"); 
// 		exit(EXIT_FAILURE); 
// 	} 
// 	address.sin_family = AF_INET; 
// 	address.sin_addr.s_addr = INADDR_ANY; 
// 	address.sin_port = htons( PORT ); 
	
// 	// Forcefully attaching socket to the port 8080 
// 	if (bind(server_fd, (struct sockaddr *)&address, 
// 								sizeof(address))<0) 
// 	{ 
// 		perror("bind failed"); 
// 		exit(EXIT_FAILURE); 
// 	} 
// 	if (listen(server_fd, 3) < 0) 
// 	{ 
// 		perror("listen"); 
// 		exit(EXIT_FAILURE); 
// 	} 
// 	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
// 					(socklen_t*)&addrlen))<0) 
// 	{ 
// 		perror("accept"); 
// 		exit(EXIT_FAILURE); 
// 	} 
// 	read( new_socket , buffer, 1024); 
// 	printf("%s\n",buffer ); 
// 	send(new_socket , hello , strlen(hello) , 0 ); 
// 	printf("Hello message sent\n"); 
// 	return 0; 
// } 
