#include "server.h"
#include "checksum.h"

char buf[BUFSIZE];
FILE *fp;
struct pack_so packet;
struct ack_so ack;
int end = 0, n = 0;

int receive_packet(int sockfd, long lseek);

void str_ser(int sockfd)
{
	long lseek=0;
	
	printf("receiving data!\n");

	while(!end)
	{
		int success = receive_packet(sockfd, lseek);
    if (success) {
		  lseek += n;
    }
	}

	if ((fp = fopen ("myTCPreceive.txt","wt")) == NULL) {
		printf("File doesn't exit\n");
		exit(0);
	}
  
	fwrite (buf , 1 , lseek , fp);					//write data into file
	fclose(fp);
	printf("a file has been successfully received!\nthe total data received is %d bytes\n", (int)lseek);
}

int receive_packet(int sockfd, long lseek) {
  if ((n = recv(sockfd, &packet, PACKLEN, 0)) == -1) {                            //receive the packet
    printf("error when receiving\n");
    return 0;
  }

  ack.num = 1;
	ack.status = 1;

	if (send(sockfd, &ack, 2, 0) == -1) {
    printf("send error!");								//send the ack
    return 0;
	}

  if (packet.data[packet.len - 1] == '\0')									//if it is the end of the file
  {
    end = 1;
    n--;
  }
  memcpy((buf+lseek), packet.data, packet.len);
  return 1;
}