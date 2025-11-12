/*i2c_driver.c*/

#include <LPC21xx.H>
#include"header.h"
//#include "header.h"


/*i2c peri initialization*/

void i2c_init(void){

       PINSEL0|=0x50;//P0.2->SCL,P0.3->SDA
//				PINSEL1 |= (3 << 6);   // P0.19 SDA1
//				PINSEL1 |= (3 << 8);   // P0.20 SCL1

        I2SCLH=I2SCLL=75;//100Kbps freq

        I2CONSET=(1<<6);//I2EN=1

}


/*Sending 1byte from M-->S*/

#define SI ((I2CONSET>>3)&1)

void i2c_byte_write_frame(u8 sa,u8 mr,u8 data){

        /*1.generate start condi*/

        I2CONSET=(1<<5);//STA=1

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        I2CONCLR=(1<<5);//STA=0



        /*2.send SA+W & check ack*/

        I2DAT=sa;//send SA+W

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        if(I2STAT==0x20){

                uart0_tx_string("Err: SA+W\r\n");

                goto exit;

        }



        /*3.send m/r addr & check ack*/

        I2DAT=mr;//send/select m/r addr

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        if(I2STAT==0x30){

                uart0_tx_string("Err: m/r address\r\n");

                goto exit;

        }



        /*4.send data & check ack*/

        I2DAT=data;//send data

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        if(I2STAT==0x30){

                uart0_tx_string("Err: data\r\n");

                goto exit;

        }



        /*5.generate stop condi*/

        exit:

        I2CONSET=(1<<4);//STO=1

        I2CONCLR=(1<<3);//*SI=0

}


/*Receving 1byte from S-->M*/

u8 i2c_byte_read_frame(u8 sa,u8 mr){

        u8 temp;

        /*1.generate start condi*/

        I2CONSET=(1<<5);//STA=1

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        I2CONCLR=(1<<5);//STA=0



        /*2.send SA+W & check ack*/

        I2DAT=sa|1;//send SA+W

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        if(I2STAT==0x20){

                uart0_tx_string("Err: SA+W\r\n");

                goto exit;

        }





        /*3.send m/r addr & check ack*/

        I2DAT=mr;//send/select m/r addr

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        if(I2STAT==0x30){

                uart0_tx_string("Err: m/r address\r\n");

                goto exit;

        }



        /*4.generate restart condi*/

        I2CONSET=(1<<5);//STA=1

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        I2CONCLR=(1<<5);//STA=0



        /*5.send SA+R & check ack*/

        I2DAT=sa;//send SA+R

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//Monitor SI

        if(I2STAT==0x48){

                uart0_tx_string("Err: SA+R\r\n");

                goto exit;

        }



        /*6.wait for receive data & noack*/

        I2CONCLR=(1<<3);//SI=0*

        while(SI==0);//waiting for data to receive

        temp=I2DAT;//Collect received data



        /*7.generate stop condi*/

        exit:

        I2CONSET=(1<<4);//STO=1

        I2CONCLR=(1<<3);//*SI=0



        /*8.return received data*/

        return temp;

}
