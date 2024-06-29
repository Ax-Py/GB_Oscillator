/*
 * File:   main.c
 * Author: Computer
 *
 * Created on June 28, 2024, 6:47 PM
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
#include "I2C_commands.h"
#include "SI5351_commands.h"

#define _XTAL_FREQ 8000000

uint8_t pushbutton_counter = 0;
uint8_t selection_made_flag = 0;
uint8_t frequency_selection = 0;

void __interrupt() ISR(void){
    if(T0IF == 1){
        T0IF = 0;
        pushbutton_counter++;
    }
}

void main(void) {
    
    ANSEL = 0x00; // Make all pins digital and not analog
    OPTION_REG |= ((1 << INTEDG) | (1 << T0SE) | (1 << PS2) | (1 << PS1) | (1 << PS0)); // Enable global pull-ups, timer0 internal source, pre-scalar applied to timer0, PSx bits
    T0IF = 0; // Set interrupt flag to 0
    
    INTCON |= ((1 << GIE) | (1 << T0IE)); // Enable global and timer0 interrupts
    TRISIO |= ((1 << TRISIO4) | (1 << TRISIO3) | (1 << TRISIO2) | (1 << TRISIO1)); // Only GP5 and GP0 (SDA & SCL) are outputs
    WPU |= ((1 << WPU4) | (1 << WPU2) | (1 << WPU1)); // Internal pull-ups for button inputs
    
    SI5351_init();
    
    while(1){
        if ((GPIO & 0x16) == 0x00){
			if (pushbutton_counter == 25 && selection_made_flag == 0){
				selection_made_flag = 1;
                if (frequency_selection != 2){
                    frequency_selection += 1;
                }else{
                    frequency_selection = 0;
                }
                
                switch (frequency_selection){
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
			pushbutton_counter = 0;
			selection_made_flag = 0;
		 }
    }
    return;
}
