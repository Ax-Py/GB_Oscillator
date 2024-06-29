/* 
 * File:   I2C_commands.h
 * Author: Computer
 *
 * Created on June 28, 2024, 6:53 PM
 */

#ifndef I2C_COMMANDS_H
#define	I2C_COMMANDS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
void i2c_start(void);

void i2c_stop(void);

void i2c_write(uint8_t Data);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_COMMANDS_H */

