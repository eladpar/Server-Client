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


void ack_general(int sockfd, uint16_t ack_num, struct sockaddr_in* client_addr, socklen_t client_addr_len)
{
    //build an ack struct
    ACK ack;
    ack.Opcode = htons((uint16_t(4))); //ack.opcode = 4
    ack.BlockNumber = htons(ack_num); //in case ack of WRQ -- ack_number is 0

    //we send the ack until he sent successfully
    
    int ack_size = 1; //initialize
    int real_size = sizeof(ack);
    while(ack_size != real_size)
    {
        ack_size = sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)client_addr, client_addr_len);
		if ( ack_size < 0) // sent fail
		{ 
			perror("TTFTP_ERROR: ");
            //!CHECK END
		}
    } 
    cout << "OUT:ACK, " << ack_num << endl;
}

bool GetData(int socketfd, FILE* filefd, struct sockaddr_in* client_addr, socklen_t client_addr_len) 
{
	/* Declerations */
    const int WAIT_FOR_PACKET_TIMEOUT = 3;
    const int NUMBER_OF_FAILURES = 7;
    int timeoutExpiredCount = 0;
    fd_set recievedfds;
    int ret;
    struct timeval timeout;

    do
    {
        do
        {
            do
            {
                /* Waiting for timeout */
                timeout.tv_sec = WAIT_FOR_PACKET_TIMEOUT;
                timeout.tv_usec = 0;

                ret = select(socketfd+1, &recievedfds, NULL, NULL, &timeout);
                if (ret < 0)
                {
                    //! FATAL ERROR
                }
                
                if (ret > 0)// TODO: if there was something at the socket and we are here not because of a timeout
                {
                    // TODO: Read the DATA packet from the socket (at least we hope this is a DATA packet)
                }
                if (ret == 0) // TODO: Time out expired while waiting for data to appear at the socket
                {
                    //TODO: Send another ACK for the last packet
                    timeoutExpiredCount++;
                }
                if (timeoutExpiredCount>= NUMBER_OF_FAILURES)
                {
                    // FATAL ERROR BAIL OUT
                }
                }while (...) // TODO: Continue while some socket was ready but recvfrom somehow failed to read the data
                if (...) // TODO: We got something else but DATA
                {
                    // FATAL ERROR BAIL OUT
                }
                if (...) // TODO: The incoming block number is not what we have expected, i.e. this is a DATA pkt but the block number
                //in DATA was wrong (not last ACK’s block number + 1)
                {
                    // FATAL ERROR BAIL OUT
                }
        }while (FALSE);
        timeoutExpiredCount = 0;
        lastWriteSize = fwrite(...); // write next bulk of data
        // TODO: send ACK packet to the client
    }  while (...); // Have blocks left to be read from client (not end of transmission)
}