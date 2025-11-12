/*lcd_driver*/

#include <LPC21xx.H>
#include"header.h"
void lcd_data(unsigned char data)
{
unsigned int temp;
//Higher Nibble

        IOCLR1=0xFE<<16;
        temp=(data&0xF0)<<16;
        IOSET1=temp;
        IOSET1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;

// Lower Nibble

        IOCLR1=0xFE<<16;
        temp=(data&0x0F)<<20;
        IOSET1=temp;
        IOSET1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;

}

void lcd_cmd(unsigned char cmd)
{
unsigned int temp;
// Higher Nibble

        IOCLR1=0xFE<<16;
        temp=(cmd&0xF0)<<16;
        IOSET1=temp;
        IOCLR1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;

// Lower Nibble

        IOCLR1=0xFE<<16;
        temp=(cmd&0x0F)<<20;
        IOSET1=temp;
        IOCLR1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;

}

void lcd_init()
{
        IODIR1=0xFE<<16;
        PINSEL2=0x0;
        IOCLR1=1<<19;
        lcd_cmd(0x03);
        lcd_cmd(0x02);
        lcd_cmd(0x28);
        lcd_cmd(0x0e);
        lcd_cmd(0x01);
}

void lcd_string(char *p)
{
        while(*p!=0)
        {
                lcd_data(*p);
                p++;
        }
}

void lcd_integer1(int num)
{
int a[10],i;
if(num==0)
{
lcd_data('0');
}
if(num<0)
{
lcd_data('-');
num=-num;
}
i=0;
while(num>0)
{
a[i]=num%10+48;
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
{
lcd_data(a[i]);
}
}
