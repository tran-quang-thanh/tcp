#include "checksum.h"
#include <math.h>

uint32_t reverse(uint32_t x);

uint32_t crc32(char* message) {
  int i, j;
  uint32_t byte, crc;

  i = 0;
  crc = 0xFFFFFFFF;
  while (message[i] != 0) {
    byte = message[i];            // Get next byte.
    byte = reverse(byte);         // 32-bit reversal.
    for (j = 0; j <= 7; j++) {    // Do eight times.
      if ((int)(crc ^ byte) < 0) {
        crc = (crc << 1) ^ 0x04C11DB7;
      } else {
        crc = crc << 1;
      }
      byte = byte << 1;          // Ready next msg bit.
    }
    i = i + 1;
  }
  return reverse(~crc);
}

uint32_t reverse(uint32_t x) {
   x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
   x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
   x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
   x = (x << 24) | ((x & 0xFF00) << 8) |
       ((x >> 8) & 0xFF00) | (x >> 24);
   return x;
}