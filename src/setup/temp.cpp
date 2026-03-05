#include <Arduino.h>
#include "temp.h"
#include "macros.h"
#include "SPI.h"



unsigned short int temp_transmit() {

 
 unsigned char msb;
 unsigned char lsb;
 
  CLRBIT(SPCR, CPOL);
  CLRBIT(PORTB, PB0);
  ZROBIT(SPDR);

  while(!(SPSR &(1<<SPIF))); 
    msb = SPDR;

  ZROBIT(SPDR);
  while(!(SPSR &(1<<SPIF))); 
    lsb = SPDR;

  SETBIT(PORTB, PB0);
 
  return (((msb << 8) | lsb) >> 3);

}

void temp_convert(char *buf) {

 unsigned short int raw_temp = temp_transmit() * 25;
 unsigned short int total = raw_temp / 100;
 unsigned short int frac = raw_temp % 100;

 sprintf(buf, "%02d.%02d C", total, frac);

}