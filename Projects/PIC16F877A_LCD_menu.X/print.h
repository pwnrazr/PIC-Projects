
#ifndef _print_H
#define	_print_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>



void write(const uint8_t *buffer, char size)
{
  char n = 0;
  while (size--) {
    if (write(*buffer++)) n++;
    else break;
  }
  return n;
}

void print(const __FlashStringHelper *ifsh)
{
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  char n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    if (write(c)) n++;
    else break;
  }
  return n;
}

#endif	/* XC_HEADER_TEMPLATE_H */

