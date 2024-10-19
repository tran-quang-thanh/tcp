// headfile for TCP program
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>

#define NEWFILE (O_WRONLY|O_CREAT|O_TRUNC)
#define MYTCP_PORT 4950
#define DATALEN 500
#define BUFSIZE 60000
#define PACKBUFFER 16
#define PACKLEN DATALEN+PACKBUFFER
#define HEADLEN 8
#define TIMEOUT 3

struct pack_so			//data packet structure
{
  uint32_t num;				// the sequence number
  uint32_t len;					// the packet length
  uint32_t count;
  uint32_t crc;     // checksum value of data
  char data[DATALEN];	//the packet data
};

struct ack_so
{
  uint8_t num;
  uint8_t status;
};
