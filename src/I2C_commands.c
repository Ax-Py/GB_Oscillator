#include <xc.h>
#include "I2C_commands.h"

#define SDA_HIGH (GP5 = 1)
#define SCL_HIGH (GP0 = 1)

#define SDA_LOW (GP5 = 0)
#define SCL_LOW (GP0 = 0)

#define SDA_READ_ON (GP5 = 1)
#define SDA_READ_OFF (GP5 = 0)

void i2c_start(void){
    SDA_HIGH;
    NOP();
    SCL_HIGH;
    NOP();
    SDA_LOW;
    NOP();
    SCL_LOW;
    NOP();
}

void i2c_stop(void){
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