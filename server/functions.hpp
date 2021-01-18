#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once
#include <stdio.h>
#include <string.h>
#include "server.hpp"
	
// class functions  
// {
// 	private:

// 	public:

// 		functions();
// 		~functions();

// };

void build_wrq(char * buffer, WRQ * wrq); // designed to parse the wrq from the buffer we gon deliverd to
void acc_general(int sockfd, int ack_num, struct sockaddr_in* client_addr, socklen_t client_addr_len);
void clearBuffer(char * buffer); // over loading of a function to clear buffers memset 0
void clearBuffer(WRQ * wrq, char * buffer);
#endif