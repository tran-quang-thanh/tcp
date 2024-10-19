#include "client.h"
#include "checksum.h"

void tv_sub(struct  timeval *out, struct timeval *in);

float str_cli(FILE *fp, int sockfd, long *len)
{
	char *buf;
	long lsize, ci;
	char sends[DATALEN];
	struct ack_so ack;
	int n, slen;
	float time_inv = 0.0;
	struct timeval sendt, recvt;
	ci = 0;

	fseek(fp, 0, SEEK_END);
	lsize = ftell(fp);
	rewind(fp);
	printf("The file length is %d bytes\n", (int)lsize);
	printf("the packet length is %d bytes\n",DATALEN);

	buf = (char *) malloc(lsize);
	if (buf == NULL) exit(2);

  // copy the file into the buffer.
	fread (buf, 1, lsize, fp);

	buf[lsize] ='\0';									//append the end byte
	gettimeofday(&sendt, NULL);							//get the current time

	while (ci <= lsize) {
		if ((lsize+1-ci) <= DATALEN) {
			slen = lsize+1-ci;
    } else { 
			slen = DATALEN;
    }
		memcpy(sends, (buf+ci), slen);
		n = send(sockfd, &sends, slen, 0);
		if(n == -1) {
			printf("send error!");								//send the data
			exit(1);
		}
		ci += slen;
	}

	if ((n= recv(sockfd, &ack, 2, 0))==-1) {                                   //receive the ack
		printf("error when receiving\n");
		exit(1);
	}

	if (ack.num != 1|| ack.len != 0) {
		printf("error in transmission\n");
  }

	gettimeofday(&recvt, NULL);
	*len= ci;                                                         //get current time
	tv_sub(&recvt, &sendt);                                                                 // get the whole trans time
	time_inv += (recvt.tv_sec)*1000.0 + (recvt.tv_usec)/1000.0;
	return(time_inv);
}

void tv_sub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) <0) {
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}