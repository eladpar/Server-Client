#include "functions.hpp"  

using namespace std;

void build_wrq(char * buffer, WRQ * wrq)
{
    char tmp[3];
    memcpy(&tmp, buffer, 2);
    int file_len = strlen(buffer+2);
    wrq->Opcode = ntohs(atoi(tmp));
    strncpy(wrq->FileName, buffer + 2, file_len);
	if (strrchr(wrq->FileName,'/')) // go to lsat occurunce and extract file name from full path
		strcpy(wrq->FileName, strrchr(wrq->FileName, '/') + 1);
	strncpy(wrq->TransmissionMode, buffer + 2 + file_len + 1,
		strlen(buffer + 2 + file_len + 1));    // copy transmission mode
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

void acc_general(int sockfd, uint16_t ack_num, struct sockaddr_in* client_addr, socklen_t client_addr_len)
{
    //build an ack struct
    ACK ack;
    ack.Opcode = htons((uint16_t(4))); //ack.opcode = 4
    ack.BlockNumber = htons(ack_num); //in case ack of WRQ -- ack_number is 0

    //we send the ack until he sent successfully
    
    int ack_size = 1; //initialize
    while(ack_size != sizeof(ack))
    {
        ack_size = sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)client_addr, client_addr_len);
		if ( ack_size < 0) // sent fail
		{ 
			perror("TTFTP_ERROR: ");
		}
    } 
    cout << "OUT:ACK, " << ack_num << endl;
}
