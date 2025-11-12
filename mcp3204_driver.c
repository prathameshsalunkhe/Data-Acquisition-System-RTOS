/*mcp3204*/
#include<LPC21xx.H>
#include"header.h"


u32 mcp3204_read(u8 ch_num){

        u32 result=0;

        u8 byteH=0,byteL=0;

        ch_num<<=6;
        IOCLR0=(1<<7);

        spi0(0x06);

        byteH=spi0(ch_num);

        byteL=spi0(0x00);

        IOSET0=(1<<7);



        byteH=byteH&0x0F;

        result=(byteH<<8)|byteL;
//      IOSET0=(1<<7);

        return result;

}
