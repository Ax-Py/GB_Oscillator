#include "I2C_commands.h"
#include "SI5351_commands.h"

void SI5351_init(void){
    // Setup the main PLL, this should not change since needing to re-lock causes the output to shutoff briefly
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
	
    // Set output divider to output 4.194MHz on channel 1
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

void SI5351_1X(void){
    // Set output divider to output 4.194MHz on channel 1
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

void SI5351_0_85X(void){
    // Set output divider to output 3.5649MHz on channel 1
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

void SI5351_1_5X(void){
    // Set output divider to output 6.291MHz on channel 1
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
