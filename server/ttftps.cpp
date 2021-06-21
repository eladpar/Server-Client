#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include "ttftps.hpp"
#include "functions.hpp"
#define ECHOMAX 255 

using namespace std;

//**************************************************************************************
// function name: main
// Description: main function
//**************************************************************************************
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "ERROR, no port provided" << endl;
        exit(1);
    }
    FILE *fptr;
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
     while(1)
     {
        /* Set the size of the in-out parameter */
        cliAddrLen = sizeof(echoClntAddr);
        socklen_t client_adrr_len = (socklen_t)cliAddrLen;
        /* Clear buffers */
        clearBuffer(&Wrq , buffer);
        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, buffer, MAX_WRQ, 0,(struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
        {
            perror("TTFTP_ERROR:");
            continue;
            //TODO EXIT?
        }
        build_wrq(buffer, &Wrq);

        if ((Wrq.Opcode !=2) || strcmp(Wrq.TransmissionMode, "octet"))
        {
            cerr << "no wrq" << endl; //DEBUG
            continue;
            //TODO EXIT?
        }
        else
        {
            cout << "IN:WRQ, " << Wrq.FileName << " ," << Wrq.TransmissionMode <<  endl;
        }
        
        //ACK on WRQ
        ack_general(sock, 0, &echoClntAddr, client_adrr_len);
        //OPEN FILE TO WRITE
        fptr = fopen(Wrq.FileName,"w");
        if (fptr == NULL)
        {
            perror("TTFTP_ERROR:");
            continue;
            //TODO EXIT?
        }

        if (GetData(sock, fptr, &echoClntAddr, &cliAddrLen) == true)
            cout << "RECVOK" << endl;
        else
            cout << "RECVFAIL" << endl;
        
        if (fclose(fptr) != 0)
        {
            perror("TTFTP_ERROR:");
            continue;
            //TODO EXIT?
        }        

     }

    /* NOT REACHED */
} 

