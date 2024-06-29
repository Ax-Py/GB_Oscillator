/* 
 * File:   SI5351_commands.h
 * Author: Computer
 *
 * Created on June 28, 2024, 6:50 PM
 */

#ifndef SI5351_COMMANDS_H
#define	SI5351_COMMANDS_H

#ifdef	__cplusplus
extern "C" {
#endif

void SI5351_init(void);

void SI5351_1X(void);

void SI5351_0_85X(void);

void SI5351_1_5X(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SI5351_COMMANDS_H */

