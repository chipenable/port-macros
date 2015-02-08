//***************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru   
//
//  Target(s)...: AVR
//
//  Compiler....: IAR
//
//  Description.: test project
//
//***************************************************************************

#include <ioavr.h>
#include <intrinsics.h>
#include <stdint.h>
#include "port_macros.h"

#define F_CPU 8000000UL
#define delay_ms(x)   __delay_cycles(x*(F_CPU/1000))

//define the virtual port
#define LED_PORT LED, F, _VIRT

//define the pins
#define LED_0  D, 0, _HI
#define LED_1  D, 1, _HI
#define LED_2  D, 2, _HI
#define LED_3  A, 2, _HI
#define LED_4  A, 3, _HI
#define LED_5  A, 4, _HI
#define LED_6  B, 4, _HI
#define LED_7  B, 5, _HI

//define the real port
#define LED_PORT2 LED2, C, _REAL

//define the pins
#define LED2_0  C, 0, _HI
#define LED2_1  C, 1, _HI
#define LED2_2  C, 2, _HI
#define LED2_3  C, 3, _HI
#define LED2_4  C, 4, _HI
#define LED2_5  C, 5, _HI
#define LED2_6  C, 6, _HI
#define LED2_7  C, 7, _NONE

//leds
#define ONE_LED  B, 0, _LOW
#define TWO_LED  C, 7, _HI

//single button
#define BUTTON      B, 1, _HI

int main( void )
{
  uint8_t count = 1;
  
  //cofigure the virtual port
  PM_DirPort(LED_PORT, 0xff);
  
  //cofigure the real port
  PM_DirPort(LED_PORT2, 0xff);
  
  //configure pins
  PM_DirPin(ONE_LED, _OUT);
  PM_DirPin(TWO_LED, _OUT);
  
  PM_DirPin(BUTTON, _IN);
  PM_SetPin(BUTTON);
  
  while(1){
   
    if (PM_PinIsClear(BUTTON)){
        PM_OnPin(ONE_LED);
        PM_OnPin(TWO_LED);
    }
    else{
       PM_OffPin(ONE_LED);  
       PM_OffPin(TWO_LED);
    }
    
    //running leds 
    delay_ms(100);
    PM_WritePort(LED_PORT, count);
    PM_WritePort(LED_PORT2, count);
    count = count << 1;
    if (count == 0){
       count = 1;  
    }   
  }  
  return 0;
}
