#include "functions.hpp"  

using namespace std;

void build_wrq(char * buffer, WRQ * wrq)
{
    // char tmp[3];
    memcpy(&wrq->Opcode, buffer, 2);
    // tmp[3] = '\0';
    int file_len = strlen(buffer+2);
    wrq->Opcode = ntohs(wrq->Opcode);
    strncpy(wrq->FileName, buffer + 2, file_len);
	if (strrchr(wrq->FileName,'/')) // go to lsat occurunce and extract file name from full path
		strcpy(wrq->FileName, strrchr(wrq->FileName, '/') + 1);
	strncpy(wrq->TransmissionMode, buffer + 2 + file_len + 1,
		strlen(buffer + 2 + file_len + 1));    // copy transmission mode
}
void build_data(char * buffer, DATA * data)
{
    memcpy(&data->Opcode, buffer, 2);
    memcpy(&data->BlockNumber, buffer+2, 2);
    data->Opcode = ntohs(data->Opcode);
    data->BlockNumber = ntohs(data->BlockNumber);
	memcpy(data->Data, buffer+4, 512);
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
            return;
		}
    } 
    cout << "OUT:ACK, " << ack_num << endl;
}

bool GetData(int socketfd, FILE* filefd, struct sockaddr_in* client_addr,
                             socklen_t * client_addr_len, uint16_t BlockNumber) 
{
	/* Declerations */
    const int WAIT_FOR_PACKET_TIMEOUT = 3;
    const int NUMBER_OF_FAILURES = 7;
    int timeoutExpiredCount = 0;
    fd_set recievedfds;
    int ret;
    char buffer[DATA_PACKET_SIZE];
    struct timeval timeout;
    int recvMsgSize; /* Size of received message */
    DATA data;
    int lastWriteSize = 0;

    FD_ZERO(&recievedfds); 
    FD_SET(socketfd, &recievedfds);

    do
    {
        do
        {
            do
            {
                /* Initialize the DATA  buffer */
                memset(&data, 0, sizeof(DATA));
                /* Waiting for timeout */
                timeout.tv_sec = WAIT_FOR_PACKET_TIMEOUT;
                timeout.tv_usec = 0;

                ret = select(socketfd+1, &recievedfds, NULL, NULL, &timeout);
                if (ret < 0)
                {
                    //! FATAL ERROR
                    return false;
                }
                
                if (ret > 0)// TODO: if there was something at the socket and we are here not because of a timeout
                {
                    // TODO: Read the DATA packet from the socket (at least we hope this is a DATA packet)
                    if ((recvMsgSize = recvfrom(socketfd, buffer, DATA_PACKET_SIZE, 0,(struct sockaddr *) client_addr, client_addr_len)) < 0)
                    {
                        perror("TTFTP_ERROR:");
                        //TODO EXIT?
                    }
                }

                if (ret == 0) // TODO: Time out expired while waiting for data to appear at the socket
                {
                    //TODO: Send another ACK for the last packet
                    ack_general(socketfd,BlockNumber,client_addr,*client_addr_len);
                    timeoutExpiredCount++;
                    cout << "FLOWERROR: no data has arrived until the timeout" << endl;
                }
                if (timeoutExpiredCount>= NUMBER_OF_FAILURES)
                {
                    cout << "FLOWERROR: too many timeouts!" << endl;
                    //! FATAL ERROR BAIL OUT
                    return false;
                }
                }while (recvMsgSize < 0); // TODO: Continue while some socket was ready but recvfrom somehow failed to read the data
              
                build_data(buffer, &data);
                if (data.Opcode != 3) // TODO: We got something else but DATA
                {
                    cout << "FLOWERROR: this isn't the correct packet type!" << endl;
                    //! FATAL ERROR BAIL OUT
                    return false;
                }
                if (data.BlockNumber != BlockNumber+1) // TODO: The incoming block number is not what we have expected, i.e. this is a DATA pkt but the block number
                //in DATA was wrong (not last ACK’s block number + 1)
                {
                    cout << "FLOWERROR: this isn't the correct packet!" << endl;
                    //! FATAL ERROR BAIL OUT
                    return false;                
                }
        }while (false);
        timeoutExpiredCount = 0;
        BlockNumber++; 

        cout << "IN:DATA, " << BlockNumber << ", " << recvMsgSize << endl;

        lastWriteSize = fwrite(data.Data, recvMsgSize-4, (size_t)1, filefd); // write next bulk of data
   
        if (recvMsgSize-4 != 0 && lastWriteSize != 1) // the first condition -- if we sent only a header
        {   
            //! FATAL ERROR BAIL OUT
            return false;
        }

        cout << "WRITING: " << lastWriteSize << endl;

        // TODO: send ACK packet to the client
        ack_general(socketfd,BlockNumber,client_addr,*client_addr_len);

    }  while (recvMsgSize == DATA_PACKET_SIZE); // Have blocks left to be read from client (not end of transmission)
    return true;
}