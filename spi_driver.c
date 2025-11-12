/*spi_driver.c*/
#include <LPC21xx.H>
#include "header.h"

void spi0_init(void){

        PINSEL0|=0x1500;
        IODIR0|=(1<<7);

        IOSET0=(1<<7);

        S0SPCR=0x20;



        S0SPCCR=15;

}


#define SPIF ((S0SPSR>>7)&1)

u8 spi0(u8 data){

        S0SPDR=data;

        while(SPIF==0);

        return S0SPDR;

}
