#ifndef CLIENT_H
#define CLIENT_H
#pragma once
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

#define MAX_WRQ 512
#define MAX_STRING 254
#define MAX_DATA 512
#define DATA_PACKET_SIZE 516

using namespace std;

typedef struct WRQ_
{
    uint16_t Opcode; // 2 bytes
    char FileName[MAX_STRING];
    char TransmissionMode[MAX_STRING];
    
}__attribute__((packed)) WRQ;

typedef struct ACK_
{
    uint16_t Opcode; // 2 bytes
    uint16_t BlockNumber; // 2 bytes 

}__attribute__((packed)) ACK;

typedef struct DATA_
{
    uint16_t Opcode; // 2 bytes
    uint16_t BlockNumber;  // 2 bytes
    char Data[MAX_DATA]; //(MAX_DATA,'\0');

}__attribute__((packed)) DATA;
#endif