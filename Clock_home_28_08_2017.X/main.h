/* 
 * File:   main.h
 * Author: pnbao
 *
 * Created on August 28, 2017, 8:29 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
                                                                                // <editor-fold defaultstate="collapsed" desc="CONFIG">// CONFIG2
#pragma config POSCMOD = HS                                                     // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config I2C1SEL = PRI                                                    // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = ON                                                     // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON                                                    // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD                                                   // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL                                                   // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config SOSCSEL = SOSC                                                   // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG                                                     // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = OFF                                                       // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
#pragma config WDTPS = PS8192                                                   // Watchdog Timer Postscaler (1:8,192)
#pragma config FWPSA = PR128                                                    // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON                                                      // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF                                                      // Watchdog Timer Enable (Watchdog Timer is enabled)
#pragma config ICS = PGx1                                                       // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF                                                       // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                                                        // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF                                                     // JTAG Port Enable (JTAG port is disabled)
                                                                                // </editor-fold>
                                                                                //<editor-fold defaultstate="collapsed" desc="DEFINE I/O">
#define LED0 LATAbits.LATA10
#define LED1 LATAbits.LATA7
#define LED2 LATBbits.LATB8
#define LED3 LATBbits.LATB9
#define LED4 LATAbits.LATA8
#define LED5 LATAbits.LATA9
#define LED6 LATCbits.LATC6    
#define LED7 LATBbits.LATB12  
                                                                                // </editor-fold>
    
void main_init();
void delay(uint32_t x);
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

