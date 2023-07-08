/*
 * File:   main.c
 * Author: Win10
 *
 * Created on July 31, 2022, 10:44 AM
 */

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/AN3/T1G/OSC2/CLKOUT, I/O function on RA5/T1CKI/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin is alternate function, MCLR function is internally disabled)
#pragma config CP = OFF         // Code Protection bit (Program memory is not code protected)
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select (8 MHz)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>

#define _XTAL_FREQ 8000000

#define SDA_HIGH (GP5 = 1)
#define SCL_HIGH (GP0 = 1)

#define SDA_LOW (GP5 = 0)
#define SCL_LOW (GP0 = 0)

#define SDA_READ_ON (GP5 = 1)
#define SDA_READ_OFF (GP5 = 0)

uint8_t counter = 0;
uint8_t active_flag = 0;
uint8_t selection = 0;

void __interrupt() ISR(void){
    if(T0IF == 1){
        T0IF = 0;
        counter++;
    }
}

void i2c_start(){
    SDA_HIGH;
    NOP();
    SCL_HIGH;
    NOP();
    SDA_LOW;
    NOP();
    SCL_LOW;
    NOP();
}

void i2c_stop(){
    SDA_LOW;
    NOP();
    SCL_HIGH;
    NOP();
    SDA_HIGH;
    NOP();
}

void i2c_write(uint8_t Data){
    for(uint8_t Byte = 8; Byte; Byte--){
        (Data & 0x80) ? SDA_HIGH : SDA_LOW;
        Data <<= 1;
        NOP();
        SCL_HIGH;
        NOP();
        SCL_LOW;
        NOP();
    }
    SDA_HIGH;
    SCL_HIGH;
    NOP();
    SDA_READ_ON;
    SCL_LOW;
    NOP();
    SDA_READ_OFF;
    NOP();
}

void SI5351_init(){
	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0x10);
	i2c_write(0x80);
	i2c_write(0x80);
	i2c_write(0x80);
	i2c_stop();
    
	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0xB7);
	i2c_write(0xC0);
	i2c_stop();

	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0x22);
	i2c_write(0x18);
	i2c_write(0x6A);
	i2c_write(0x00);
	i2c_write(0x0B);
	i2c_write(0xEC);
	i2c_write(0x00);
	i2c_write(0x0D);
	i2c_write(0xC8);
	i2c_stop();

	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0xB1);
	i2c_write(0xA0);
	i2c_stop();
	
	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0x32);
	i2c_write(0xFF);
	i2c_write(0xFF);
	i2c_write(0x00);
	i2c_write(0x51);
	i2c_write(0x02);
	i2c_write(0xF7);
	i2c_write(0x10);
	i2c_write(0x02);
	i2c_stop();
	
	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0x11);
	i2c_write(0x6F);
	i2c_stop();
}

void SI5351_1X(){
	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0x32);
	i2c_write(0xFF);
	i2c_write(0xFF);
	i2c_write(0x00);
	i2c_write(0x51);
	i2c_write(0x02);
	i2c_write(0xF7);
	i2c_write(0x10);
	i2c_write(0x02);
	i2c_stop();
}

void SI5351_0_85X(){
	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0x32);
	i2c_write(0xFF);
	i2c_write(0xFF);
	i2c_write(0x00);
	i2c_write(0x60);
	i2c_write(0x02);
	i2c_write(0xF7);
	i2c_write(0x10);
	i2c_write(0x02);
	i2c_stop();
}

void SI5351_1_5X(){
	i2c_start();
	i2c_write(0x60 << 1);
	i2c_write(0x32);
	i2c_write(0xFF);
	i2c_write(0xFF);
	i2c_write(0x00);
	i2c_write(0x35);
	i2c_write(0x02);
	i2c_write(0xF7);
	i2c_write(0x10);
	i2c_write(0x02);
	i2c_stop();
}

void main(void) {
    ANSEL = 0; // Make all pins digital and not analog
    OPTION_REG = 0b01010111; // Enable global pull-ups, timer0 internal source, pre-scalar applied to timer0, PSx bits
    T0IF = 0;
    INTCON = 0b10100000; // Enable the global interrupt and Overflow TMR0 bit
    TRISIO = 0b011110; //Make all pins except GPIO 1,2,3 and 4 an output
    WPU = 0b011110; // Enable pull-ups on GPIO 1,2,3, and 4
    
    SI5351_init();
    
    while(1){
        if (((GPIO & 0x10) != 0x10) && ((GPIO & 0x04) != 0x04) && ((GPIO & 0x02) != 0x02)){
			if (counter == 25 && active_flag == 0){
				active_flag = 1;
                if (selection != 2){
                    selection += 1;
                }else{
                    selection = 0;
                }
                
                switch (selection){
                    case 0:
                        SI5351_1X();
                        break;
                    case 1:
                        SI5351_1_5X();
                        break;
                    case 2:
                        SI5351_0_85X();
                        break;
                }
			}
		}else{
			counter = 0;
			active_flag = 0;
		 }
    }
    return;
}
