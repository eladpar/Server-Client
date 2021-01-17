#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include "server.hpp"
#include "functions.hpp"
#define ECHOMAX 255 

using namespace std;


// struct server
// {
// 	int opcode; // 2 bytes
// 	string filename;
	
// }__attribute__((packed));

// void error(string msg) {
//     cerr << msg << endl;
//     exit(0);
// }
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

    char buffer[MAX_WRQ]; /* Buffer for echo string */
    WRQ Wrq;

    unsigned short echoServPort; /* Server port */
    int recvMsgSize; /* Size of received message */
    
    echoServPort = atoi(argv[1]);

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        perror("socket() failed");
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
        perror("bind() failed");
    }
     
        /* Set the size of the in-out parameter */
        cliAddrLen = sizeof(echoClntAddr);

        /* Clear buffers */
        clearBuffer(&Wrq , buffer);
        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, buffer, MAX_WRQ, 0,(struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
        {
            perror("TTFTP_ERROR:");
            //TODO EXIT?
        }
        cout << "buffer is " << buffer << endl;
        cout << "buffer+2 is " << buffer+3 << endl;
        cout << "buffer+17 is " << buffer+17 << endl;
        build_wrq(buffer, &Wrq);

        printf("the recived msg size is %d\n", recvMsgSize);
        //TODO CHECK THE TEST FILE FOR OPCODE AND FILE NAME
		cout << "opcode is " << Wrq.Opcode << " filename is " << Wrq.FileName << " transmission is " << Wrq.TransmissionMode << endl;







        /* Send received datagram back to the client */
        // if (sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize)
       	// 	 error("sendto() sent a different number of bytes than expected");
    // }
    /* NOT REACHED */
} 

