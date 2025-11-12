/*header*/
#include<lpc21xx.h>
#include<stdio.h>
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;

///////delay header.h//////////////
extern void delay_sec(u32 sec);
extern void delay_ms(u32 ms);
////// lcd header.h ///////////////
extern void lcd_data(unsigned char data);
extern void lcd_cmd(u8 cmd);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_integer1(int  );
extern void lcd_float(float );
/////// adc header.h /////////////
extern u32 adc_read( u8 ch_num);
extern void adc_init(void);
////// MCP3204 header.h //////////
extern u32 mcp3204_read(u8 ch_num);
////// I2C header.h //////////////
extern void i2c_init(void);
extern void i2c_byte_write_frame(u8 sa,u8 mr,u8 data);
extern u8 i2c_byte_read_frame(u8 sa,u8 mr);
////// SPI header.h //////////////
extern void spi0_init(void);
extern u8 spi0(u8 data);
/////// UART0 header.h////////
extern void uart0_init(u32 baud);
extern void uart0_tx(u8 data);
extern void uart0_tx_string(char *ptr);
extern void uart0_rx_string(unsigned char *p,int len);


extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void delay_sec(unsigned int sec);
extern void delay_ms(unsigned int ms);
extern void lcd_integer1(int num);
extern void lcd_float(float f);
extern void lcd_cgram(void);


typedef unsigned int  u32;
typedef unsigned char u8;

/* ADC functions */
void adc_init(void);
u32  adc_read(u8);

void uart0_tx_string(char *);

/* LCD functions */
void lcd_init(void);
void lcd_cmd(u8);
void lcd_data(u8);
void lcd_str(char *);




