/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#ifndef SYSTEM_PERIPHERAL_CLOCK
#define SYSTEM_PERIPHERAL_CLOCK 16000000
//#pragma message "This module requires a definition for the peripheral clock frequency.  Assuming 16MHz Fcy (32MHz Fosc).  Define value if this is not correct."
#endif

/* This defines the number of cycles per loop through the delay routine.  Spans
 * between 12-18 depending on optimization mode.*/
#define CYCLES_PER_DELAY_LOOP 12

/* Private Definitions ***********************************************/

/* Define a delay for the various time intervals required between various signal
 * transitions (E pulse, R/W setup, etc.).  This will be rounded up to 1us for 
 * the sake of easy calculation though all of these are less than that
 * typically 60-300ns. */
#define LCD_SIGNAL_TIMING         (((SYSTEM_PERIPHERAL_CLOCK/1000)*1)/1000)/CYCLES_PER_DELAY_LOOP

// Define a fast instruction execution time in terms of loop time
// typically > 40us
#define LCD_F_INSTR         (((SYSTEM_PERIPHERAL_CLOCK/1000)*40)/1000)/CYCLES_PER_DELAY_LOOP

// Define a slow instruction execution time in terms of loop time
// typically > 1.64ms
#define LCD_S_INSTR         (((SYSTEM_PERIPHERAL_CLOCK/1000)*1640)/1000)/CYCLES_PER_DELAY_LOOP

// Define the startup time for the LCD in terms of loop time
// typically > 60ms (double than 8 bit mode)
#define LCD_STARTUP         (((SYSTEM_PERIPHERAL_CLOCK/1000)*60000)/1000)/CYCLES_PER_DELAY_LOOP

#define LCD_MAX_COLUMN      16

#define LCD_SendData(data) { PMADDR = 0x0001; PMDIN1 = data; LCD_Wait(LCD_F_INSTR); }
#define LCD_SendCommand(command, delay) { PMADDR = 0x0000; PMDIN1 = command; LCD_Wait(delay); }
#define LCD_COMMAND_CLEAR_SCREEN        0x01
#define LCD_COMMAND_RETURN_HOME         0x02
#define LCD_COMMAND_ENTER_DATA_MODE     0x06
#define LCD_COMMAND_CURSOR_OFF          0x0C
#define LCD_COMMAND_CURSOR_ON           0x0F
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14
#define LCD_COMMAND_SET_MODE_4_BIT      0x28
#define LCD_COMMAND_SET_MODE_8_BIT      0x38
#define LCD_COMMAND_ROW_0_HOME          0x80
#define LCD_COMMAND_ROW_1_HOME          0xC0
#define LCD_START_UP_COMMAND_1          0x3C    
#define LCD_START_UP_COMMAND_2          0x38    
void LCD_CarriageReturn ( void ) ;
void LCD_ShiftCursorLeft ( void ) ;
void LCD_ShiftCursorRight ( void ) ;
void LCD_ShiftCursorUp ( void ) ;
void LCD_ShiftCursorDown ( void ) ;
void LCD_Wait ( uint32_t ) ;
/*********************************************************************
* Function: bool LCD_Initialize(void);
*
* Overview: Initializes the LCD screen.  Can take several hundred
*           milliseconds.
*
* PreCondition: none
*
* Input: None
*
* Output: true if successful, false otherwise
*
********************************************************************/
bool LCD_Initialize(void);

/*********************************************************************
* Function: void LCD_PutString(char* inputString, uint16_t length);
*
* Overview: Puts a string on the LCD screen.  Unsupported characters will be
*           discarded.  May block or throw away characters is LCD is not ready
*           or buffer space is not available.  Will terminate when either a
*           null terminator character (0x00) is reached or the length number
*           of characters is printed, which ever comes first.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char* - string to print
*        uint16_t - length of string to print
*
* Output: None
*
********************************************************************/
void LCD_PutString(char* inputString, uint16_t length);

/*********************************************************************
* Function: void LCD_PutChar(char);
*
* Overview: Puts a character on the LCD screen.  Unsupported characters will be
*           discarded.  May block or throw away characters is LCD is not ready
*           or buffer space is not available.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char - character to print
*
* Output: None
*
********************************************************************/
void LCD_PutChar(char);

/*********************************************************************
* Function: void LCD_ClearScreen(void);
*
* Overview: Clears the screen, if possible.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
void LCD_ClearScreen(void);

/*********************************************************************
* Function: void LCD_CursorEnable(bool enable)
*
* Overview: Enables/disables the cursor
*
* PreCondition: None
*
* Input: bool - specifies if the cursor should be on or off
*
* Output: None
*
********************************************************************/
void LCD_CursorEnable(bool enable);