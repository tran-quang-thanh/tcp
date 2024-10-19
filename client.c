#include "client.h"
#include "checksum.h"

char *buf;
long lsize, ci = 0;
struct pack_so packet;
struct ack_so ack;
int n, slen;
float time_inv = 0.0;
struct timeval sendt, recvt;

void tv_sub(struct  timeval *out, struct timeval *in);
int send_packet(int sockfd);

float str_cli(FILE *fp, int sockfd, long *len)
{
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

		int success = send_packet(sockfd);
    if (!success) {
      printf("error in transmission\n");
      exit(1);
    }

		ci += slen;
	}

	gettimeofday(&recvt, NULL);
	*len= ci;                                                         //get current time
	tv_sub(&recvt, &sendt);                                                                 // get the whole trans time
	time_inv += (recvt.tv_sec)*1000.0 + (recvt.tv_usec)/1000.0;
	return(time_inv);
}

int send_packet(int sockfd) {
  memcpy(packet.data, (buf+ci), slen);
  packet.len = slen;

  int tries = 0;
  while (tries < TIMEOUT) {
    if((n = send(sockfd, &packet, PACKLEN, 0)) == -1) {
      tries++;
      continue;
    }

    if ((n= recv(sockfd, &ack, 2, 0)) == -1) {
      tries++;
      continue;
    }

    if (ack.num != 1 || ack.status != 1) {
      tries++;
      continue;
    }

    return 1;
  }

  return 0;
}

void tv_sub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) <0) {
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}