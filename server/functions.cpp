#include "functions.hpp"  

using namespace std;

void build_wrq(char * buffer, WRQ * wrq)
{
    memcpy(&wrq->Opcode, buffer, 2 );
    int file_len = strlen(buffer+3);
    cout << "here is buffer " << buffer+6 <<endl;
    wrq->Opcode = ntohs(wrq->Opcode);
    strncpy(wrq->FileName, buffer + 3, file_len);
	if (strrchr(wrq->FileName,'/')) // go to lsat occurunce and extract file name from full path
		strcpy(wrq->FileName, strrchr(wrq->FileName, '/') + 1);
	strncpy(wrq->TransmissionMode, buffer + 3 + file_len + 1,
		strlen(buffer + 3 + file_len + 1));    // copy transmission mode
}

void clearBuffer(char * buffer)
{
    memset(buffer, 0, MAX_WRQ);
}

void clearBuffer(WRQ * wrq, char * buffer)
{
    memset(buffer, 0, MAX_WRQ);
    memset(wrq, 0, sizeof(WRQ));
}