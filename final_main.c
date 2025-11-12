/* rtos_main.c */
#include <LPC21xx.h>
#include "header.h"
#include <stdio.h>
#include <RTL.h>   

int i,num=0;
int h, m, s;
int h1, f = 0;
int tout, pout, ldr;
int temp, v1out, vtg;
float vout;
char time_str[20];

// ----------------- Tasks -------------------

// Task: Read RTC and update LCD + UART
__task void task_rtc_display(void) {
    while (1) {
        // Read RTC via I2C
        h = i2c_byte_read_frame(0xD1, 0x2);
        m = i2c_byte_read_frame(0xD1, 0x1);
        s = i2c_byte_read_frame(0xD1, 0x0);

        h1 = h & 0x1F;

        // UART output
        uart0_tx((h1 / 0x10) + '0');
        uart0_tx((h1 % 0x10) + '0');
        uart0_tx(':');
        uart0_tx((m / 0x10) + '0');
        uart0_tx((m % 0x10) + '0');
        uart0_tx(':');
        uart0_tx((s / 0x10) + '0');
        uart0_tx((s % 0x10) + '0');
        uart0_tx_string("\r\n");

        // LCD output
        lcd_cmd(0x80);
        lcd_data((h1 / 0x10) + '0');
        lcd_data((h1 % 0x10) + '0');
        lcd_data(':');
        lcd_data((m / 0x10) + '0');
        lcd_data((m % 0x10) + '0');
        lcd_data(':');
        lcd_data((s / 0x10) + '0');
        lcd_data((s % 0x10) + '0');
        if ((h >> 5) & 1)
            lcd_string("PM");
        else
            lcd_string("AM");

        os_dly_wait(100);  // Delay ~1s (assuming 10ms tick)
    }
}

// Task: Read ADC (Temp and Potentiometer)
__task void task_adc(void) {
    while (1) {
        // TEMP
        tout = adc_read(1);
        vout = (tout * 3.3) / 1023;
        temp = (vout - 0.5) / 0.01;

        lcd_cmd(0xC0);
        lcd_string("T:");
        lcd_integer1(temp);
        lcd_string("'C");

        // POT
        pout = adc_read(2);
        v1out = 280 * pout / 1023;
        lcd_cmd(0xC7);
        lcd_string("S:");
        lcd_integer1(v1out);
        lcd_string("km/h");

        os_dly_wait(80);  // ~800ms
    }
}

// Task: Read LDR via MCP3204 (SPI)
__task void task_ldr(void) {
    while (1) {
        ldr = mcp3204_read(2);
        vtg = 100 - ((ldr / 4095.0) * 100);
        lcd_cmd(0x8B);
        lcd_string("L:");
        lcd_integer1(vtg);
        lcd_data('%');

        os_dly_wait(80);  // ~800ms
    }
}

// Initialization Task
__task void task_init(void) {
    // Peripheral init
    uart0_init(9600);
    i2c_init();
    lcd_init();
    adc_init();
    spi0_init();
	 
    // Set RTC time once
    sprintf(time_str,"%s", __TIME__);
   
    for ( i = 0; time_str[i]; i++)
        if (time_str[i] >= '0' && time_str[i] <= '9')
            num = num * 10 + (time_str[i] - '0');

    h = num / 10000;
    m = (num / 100) % 100;
    s = num % 100;
    if (h > 12) {
        h -= 12;
        f = 1;
    }
    h = ((h / 10) << 4) | (h % 10);
    h |= 1 << 6;
    if (f)
        h |= 1 << 5;
    m = ((m / 10) << 4) | (m % 10);
    s = ((s / 10) << 4) | (s % 10);

    i2c_byte_write_frame(0xD0, 0x0, s);
    i2c_byte_write_frame(0xD0, 0x1, m);
    i2c_byte_write_frame(0xD0, 0x2, h);

    // Create tasks
    os_tsk_create(task_rtc_display, 1);
    os_tsk_create(task_adc, 1);
    os_tsk_create(task_ldr, 1);

    // Delete init task
    os_tsk_delete(0);
		while (1) { } 
}

// Main: just start the RTOS
int main(void) {
    os_sys_init(task_init);  // Start RTOS
}
