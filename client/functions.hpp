#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once
#include <stdio.h>
#include <string.h>
#include "client.hpp"
	
// class functions  
// {
// 	private:

// 	public:

// 		functions();
// 		~functions();

// };

void build_wrq(char* buffer, WRQ * wrq); // designed to parse the wrq from the buffer we gon deliverd to
void clearBuffer(char * buffer); // over loading of a function to clear buffers memset 0
void clearBuffer(WRQ * wrq, char * buffer);
#endif