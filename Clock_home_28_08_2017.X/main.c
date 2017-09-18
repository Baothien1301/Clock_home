/* 
 * File:   main.c
 * Author: pnbao
 *
 * Created on August 28, 2017, 8:28 PM
 */

#include "main.h"
#include "lcd.h"
#include "rtcc.h"
#include "print_lcd.h"
uint32_t Time, Tick_Time1;
static RTCC_DATETIME time;
int main() 
{
    ClrWdt();
    main_init();
    LCD_Initialize();
    LCD_CursorEnable (true);
    delay(500000);
    LCD_ClearScreen();
    time.bcdFormat = false;
    RTCC_BuildTimeGet( &time );
    RTCC_Initialize( &time );
    while(1)
    {
        if(Time>=1000)
        {
            RTCC_TimeGet( &time );
            LCD_ClearScreen();
            printf( "%02d-%02d-%02d  %02d:%02d",
                    time.day, time.month, time.year,
                    time.hour,time.minute);
            LED1=!LED1;
            Time=0;
        }
    }
}
void main_init()
{
                                                                                //<editor-fold defaultstate="collapsed" desc="Init OSC">
    CLKDIVbits.DOZE=0;                                                          //FRC=8MHz
    CLKDIVbits.RCDIV=0;                                                         //FOSC=F_CPU=FRC*4/1=32MHz
                                                                                //</editor-fold>
                                                                                //<editor-fold defaultstate="collapsed" desc="Init I/O">
    
    TRISA=0; TRISB=0; TRISC=0;
                                                                                //</editor-fold>
                                                                                // <editor-fold defaultstate="collapsed" desc="Init timer">
    T1CONbits.TON=1;                                                            //Enable Timer1
    T1CONbits.TCKPS=2;                                                          //CLK_T1=FOSC/2/64
    PR1=250;                                                                    //Timer1 compare 250
                                                                                // </editor-fold>
                                                                                // <editor-fold defaultstate="collapsed" desc="Init interrupt">
    IEC0bits.T1IE=1;                                                            //Enable timer1 interrupt 
    IPC0bits.T1IP=3;                                                            //Timer1 interrupt priority is 3
                                                                                // </editor-fold>
}
void delay(uint32_t x) 
{
    while(x--);
}
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
    TMR1=0;Time++;
    IFS0bits.T1IF = 0;
}