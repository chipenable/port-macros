//***************************************************************************
//
//  Author(s)...: Pavel Bobkov  site: http://ChipEnable.Ru 
//                              skype: microsmaster
//                              email: microsmaster@rambler.ru
//                              fb: https://www.facebook.com/pasha.bobkov
//
//  Target(s)...: AVR
//
//  Compiler....: gcc, iar avr, codevision avr
//
//  Description.: bit manipulation macros, virtual port macros
//
//  Data........: 08.02.2015 
//
//***************************************************************************
#ifndef PORT_MACROS_H
#define PORT_MACROS_H

/*How to use

-----------------------------------------------------------------------------------
1) At first you need to define a virtual or real port - "alias letter, type, type" 
------------------------------------------------------------------------------------
alias - no matter

name - no matter

letter - it doesn't matter if you use virtual ports 
           for real ports you have to use real letters - A, B, C, D ...

type of the port - _VIRT, _REAL, _NONE
You can use _VIRT with real ports, but your code will not be optimal 
_NONE - exclude a port. compiler will generate empty macros

Example:
--------

#define LCD_PORT  LCD_DATA, F, _VIRT

--------------------------------------------------------------------------
2) You need to define pins of the port - "name  letter, pin, level"
--------------------------------------------------------------------------
name -  LCD_DATA_0 ... LCD_DATA_7

letter -  A, B, C or D ...

number of the pin -  0..7

active level -  _LOW, _HI, _NONE
It is needed for on/off macros
_NONE - exclude pin from your virtual port. A compiler doesn't generate code for this pin. 

Example:
--------

#define LCD_DATA_0  D, 0, _HI
#define LCD_DATA_1  D, 1, _HI
#define LCD_DATA_2  D, 2, _HI
#define LCD_DATA_3  A, 2, _HI
#define LCD_DATA_4  A, 3, _HI
#define LCD_DATA_5  A, 4, _HI
#define LCD_DATA_6  B, 4, _HI
#define LCD_DATA_7  B, 5, _HI
------------------------------------

3) Use it. 

you can write to the port

PM_WritePort(LCD_PORT, 0xff);

you can read from the port 

uint8_t data;
PM_ReadPort(LCD_PORT, data);


NOTE!!!
these macroses don't provide an atomicity of operations.
If you need it you have to do this yourself. 

__disable_interrupt();
PM_WritePort(LCD_PORT, 0xff);
__enable_interrupt();

Sorry for my English.
*/

/*______________________ bit manipulation macros _____________________________*/

#define BM_Bit(bit)                       (1<<(bit))
#define BM_SetBit(var, bit)               do{(var) |= (1<<(bit));}while(0)
#define BM_ClearBit(var, bit)             do{(var) &= ~(1<<(bit));}while(0)
#define BM_InvBit(var, bit)               do{(var) ^= (1<<(bit));}while(0)
#define BM_TestBit(var, bit)              ((var) & (1<<(bit)))
#define BM_BitIsClear(var, bit)           (((var) & (1<<(bit))) == 0)
#define BM_BitIsSet(var, bit)             (((var) & (1<<(bit))) != 0)
#define BM_SetBitVal(var, bit, val)       do{{if (((val)&1)==0) {(var) &= ~(1<<(bit))};\
                                              else {(var) |= (1<<(bit));}}while(0)

/*___________________ pin manipulation macros __________________*/

#define _PM_SetPin_NONE(id, pin)           
#define _PM_SetPin_HI(id, pin)             BM_SetBit(PORT##id, pin)
#define _PM_SetPin_LOW(id, pin)            BM_SetBit(PORT##id, pin)
#define _PM_SetPin(id, pin, lev)           _PM_SetPin##lev(id, pin) 
#define PM_SetPin(x)                       _PM_SetPin(x)

#define _PM_ClearPin_NONE(id, pin) 
#define _PM_ClearPin_HI(id, pin)           BM_ClearBit(PORT##id, pin) 
#define _PM_ClearPin_LOW(id, pin)          BM_ClearBit(PORT##id, pin) 
#define _PM_ClearPin(id, pin, lev)         _PM_ClearPin##lev(id, pin) 
#define PM_ClearPin(x)                     _PM_ClearPin(x)

#define _PM_InvPin_NONE(id, pin)
#define _PM_InvPin_HI(id, pin)             BM_InvBit(PORT##id, pin)
#define _PM_InvPin_LOW(id, pin)            BM_InvBit(PORT##id, pin)
#define _PM_InvPin(id, pin, lev)           _PM_InvPin##lev(id, pin)
#define PM_InvPin(x)                       _PM_InvPin(x)

#define _PM_TestLevPin_NONE(id, pin) 
#define _PM_TestLevPin_HI(id, pin)        BM_BitIsSet(PIN##id, pin)
#define _PM_TestLevPin_LOW(id, pin)       BM_BitIsClear(PIN##id, pin)
#define _PM_TestLevPin(id, pin, lev)      _PM_TestLevPin##lev(id, pin)
#define PM_TestLevPin(x)                  _PM_TestLevPin(x)
 
#define _PM_TestPin_NONE(id, pin)
#define _PM_TestPin_HI(id, pin)            BM_TestBit(PIN##id, pin)
#define _PM_TestPin_LOW(id, pin)           BM_TestBit(PIN##id, pin)
#define _PM_TestPin(id, pin, lev)          _PM_TestPin##lev(id, pin)
#define PM_TestPin(x)                      _PM_TestPin(x)
 
#define _PM_PinIsSet_NONE(id, pin)
#define _PM_PinIsSet_HI(id, pin)           BM_BitIsSet(PIN##id, pin)
#define _PM_PinIsSet_LOW(id, pin)          BM_BitIsSet(PIN##id, pin)
#define _PM_PinIsSet(id, pin, lev)         _PM_PinIsSet##lev(id, pin)
#define PM_PinIsSet(x)                     _PM_PinIsSet(x)

#define _PM_PinIsClear_NONE(id, pin)
#define _PM_PinIsClear_HI(id, pin)         BM_BitIsClear(PIN##id, pin)
#define _PM_PinIsClear_LOW(id, pin)        BM_BitIsClear(PIN##id, pin) 
#define _PM_PinIsClear(id, pin, lev)       _PM_PinIsClear##lev(id, pin)
#define PM_PinIsClear(x)                   _PM_PinIsClear(x)

#define _PM_On_NONE(id, pin)
#define _PM_On_HI(id, pin)                BM_SetBit(PORT##id, pin) 
#define _PM_On_LOW(id, pin)               BM_ClearBit(PORT##id, pin) 
#define _PM_OnPin(id, pin, lev)           _PM_On##lev(id, pin)
#define PM_OnPin(x)                       _PM_OnPin(x)

#define _PM_Off_NONE(id, pin)
#define _PM_Off_HI(id, pin)               BM_ClearBit(PORT##id, pin) 
#define _PM_Off_LOW(id, pin)              BM_SetBit(PORT##id, pin)
#define _PM_OffPin(id, pin, lev)           _PM_Off##lev(id, pin)
#define PM_OffPin(x)                       _PM_OffPin(x)

#define _PM_Dir_OUT(id, pin)              BM_SetBit(DDR##id, pin)
#define _PM_Dir_IN(id, pin)               BM_ClearBit(DDR##id, pin)
#define _PM_DirPin_NONE(id, pin, dir)
#define _PM_DirPin_HI(id, pin, dir)       _PM_Dir##dir(id, pin)
#define _PM_DirPin_LOW(id, pin, dir)      _PM_Dir##dir(id, pin)       
#define _PM_DirPin(id, pin, lev, dir)     _PM_DirPin##lev(id, pin, dir)
#define PM_DirPin(x, y)                   _PM_DirPin(x, y)

#define __pin_NONE(pin)                    0
#define __pin_LOW(pin)                     (1<<(pin))
#define __pin_HI(pin)                      (1<<(pin))
#define __pin(id, pin, lev)                __pin##lev(pin)
#define _pin(x)                            __pin(x)
#define PM_Pin(x)                          __pin(x)

#define __pinLev_NONE(pin)                 0
#define __pinLev_LOW(pin)                  0
#define __pinLev_HI(pin)                   (1<<(pin))
#define __pinLev(id, pin, lev)             __pinLev##lev(pin)
#define _pinLev(x)                         __pinLev(x)
#define PM_PinLev(x)                       __pinLev(x)



/*________port macros. these macros are not related with  pin's active levels _______*/

/*_________________________________ write to a port ____________________________________*/

#define __PM_WritePin_HI(id, pin, value, num)          do{if (BM_TestBit(value, num)){BM_SetBit(PORT##id, pin);}  \
                                                          else {BM_ClearBit(PORT##id, pin);};                     \
                                                       }while(0)  

#define __PM_WritePin_LOW(id, pin, value, num)         do{if (BM_TestBit(value, num)){BM_SetBit(PORT##id, pin);}  \
                                                          else {BM_ClearBit(PORT##id, pin);};                     \
                                                       }while(0)  

#define __PM_WritePin_NONE(id, pin, value, num)
#define _PM_WritePin(id, pin, lev, value, num)         __PM_WritePin##lev(id, pin, value, num)
#define PM_WritePin(port, value, num)                  _PM_WritePin(port, value, num)
                                                                                                           
#define _PM_WritePort_VIRT(port, id, value)            do{ PM_WritePin(port##_##0, value, 0);\
                                                           PM_WritePin(port##_##1, value, 1);\
                                                           PM_WritePin(port##_##2, value, 2);\
                                                           PM_WritePin(port##_##3, value, 3);\
                                                           PM_WritePin(port##_##4, value, 4);\
                                                           PM_WritePin(port##_##5, value, 5);\
                                                           PM_WritePin(port##_##6, value, 6);\
                                                           PM_WritePin(port##_##7, value, 7);\
                                                       }while(0)

#define _PM_WritePort_REAL(port, id, value)            do{  uint8_t mask = _pin(port##_##7)|_pin(port##_##6)|_pin(port##_##5)|_pin(port##_##4)|_pin(port##_##3)|_pin(port##_##2)|_pin(port##_##1)|_pin(port##_##0); \
                                                                   PORT##id = (PORT##id & (~mask))|(value & mask); \
                                                         }while(0)

#define _PM_WritePort_NONE(port, id, value) 

#define _PM_WritePort(port, id, atr, value)            _PM_WritePort##atr(port, id, value)
#define PM_WritePort(port, value)                      _PM_WritePort(port, value) 


/*___________________________ set port direction  _______________________________*/

#define __PM_SetDir_HI(id, pin, value, num)        do{if (BM_TestBit(value, num)){BM_SetBit(DDR##id, pin);}  \
                                                      else {BM_ClearBit(DDR##id, pin);};                     \
                                                   }while(0)  

#define __PM_SetDir_LOW(id, pin, value, num)       do{if (BM_TestBit(value, num)){BM_SetBit(DDR##id, pin);}  \
                                                      else {BM_ClearBit(DDR##id, pin);};                     \
                                                   }while(0)  

#define __PM_SetDir_NONE(id, pin, value, num)
#define _PM_SetDir(id, pin, lev, value, num)       __PM_SetDir##lev(id, pin, value, num) 
#define PM_SetDir(port, value, num)                _PM_SetDir(port, value, num)

#define _PM_DirPort_VIRT(port, id, value)          do{ PM_SetDir(port##_##0, value, 0);\
                                                       PM_SetDir(port##_##1, value, 1);\
                                                       PM_SetDir(port##_##2, value, 2);\
                                                       PM_SetDir(port##_##3, value, 3);\
                                                       PM_SetDir(port##_##4, value, 4);\
                                                       PM_SetDir(port##_##5, value, 5);\
                                                       PM_SetDir(port##_##6, value, 6);\
                                                       PM_SetDir(port##_##7, value, 7);\
                                                   }while(0)

#define _PM_DirPort_REAL(port, id, value)         do{uint8_t mask = _pin(port##_##7)|_pin(port##_##6)|_pin(port##_##5)|_pin(port##_##4)|_pin(port##_##3)|_pin(port##_##2)|_pin(port##_##1)|_pin(port##_##0);\
                                                             DDR##id = (DDR##id & (~mask))|(value & mask); \
                                                   }while(0);

#define _PM_DirPort_NONE(port, id, value) 

#define _PM_DirPort(port, id, atr, value)         _PM_DirPort##atr(port, id, value)
#define PM_DirPort(port, value)                   _PM_DirPort(port, value) 

/*_____________________________ read a port ____________________________________________*/

#define __PM_ReadBit_HI(id, pin, var, num)         do{ if (BM_TestBit(PIN##id, pin)){BM_SetBit(var, num);}  \
                                                       else {BM_ClearBit(var, num);}                        \
                                                   }while(0)

#define __PM_ReadBit_LOW(id, pin, var, num)        do{ if (BM_TestBit(PIN##id, pin)){BM_SetBit(var, num);}  \
                                                       else {BM_ClearBit(var, num);}                        \
                                                   }while(0)
#define __PM_ReadBit_NONE(id, pin, var, num) 
#define _PM_ReadBit(id, pin, lev, var, num)        __PM_ReadBit##lev(id, pin, var, num)
#define PM_ReadBit(port, var, num)                 _PM_ReadBit(port, var, num)

#define _PM_ReadPort_VIRT(port, id, var)           do{ PM_ReadBit(port##_##0, var, 0);\
                                                       PM_ReadBit(port##_##1, var, 1);\
                                                       PM_ReadBit(port##_##2, var, 2);\
                                                       PM_ReadBit(port##_##3, var, 3);\
                                                       PM_ReadBit(port##_##4, var, 4);\
                                                       PM_ReadBit(port##_##5, var, 5);\
                                                       PM_ReadBit(port##_##6, var, 6);\
                                                       PM_ReadBit(port##_##7, var, 7);\
                                                   }while(0)

#define _PM_ReadPort_REAL(port, id, var)           do{uint8_t mask = _pin(port##_##7)|_pin(port##_##6)|_pin(port##_##5)|_pin(port##_##4)|_pin(port##_##3)|_pin(port##_##2)|_pin(port##_##1)|_pin(port##_##0);\
                                                              var = (PIN##id & mask); \
                                                   }while(0);               

#define _PM_ReadPort_NONE(port, id, var) 

#define _PM_ReadPort(port, id, atr, var)           _PM_ReadPort##atr(port, id, var) 
#define PM_ReadPort(port, var)                     _PM_ReadPort(port, var) 

/*________________________ set bits _______________________________*/

#define __PM_SetPinPort_HI(id, pin, value, num)        do{if (BM_BitIsSet(value, num)){BM_SetBit(PORT##id, pin);}  \
                                                       }while(0)  

#define __PM_SetPinPort_LOW(id, pin, value, num)         do{if (BM_BitIsSet(value, num)){BM_SetBit(PORT##id, pin);}  \
                                                       }while(0)  

#define __PM_SetPinPort_NONE(id, pin, value, num)
#define _PM_SetPinPort(id, pin, lev, value, num)       __PM_SetPinPort##lev(id, pin, value, num)
#define PM_SetPinPort(port, value, num)                _PM_SetPinPort(port, value, num)

#define _PM_SetBitsPort_VIRT(port, id, value)          do{ PM_SetPinPort(port##_##0, value, 0);\
                                                           PM_SetPinPort(port##_##1, value, 1);\
                                                           PM_SetPinPort(port##_##2, value, 2);\
                                                           PM_SetPinPort(port##_##3, value, 3);\
                                                           PM_SetPinPort(port##_##4, value, 4);\
                                                           PM_SetPinPort(port##_##5, value, 5);\
                                                           PM_SetPinPort(port##_##6, value, 6);\
                                                           PM_SetPinPort(port##_##7, value, 7);\
                                                       }while(0)

#define _PM_SetBitsPort_REAL(port, id, v)              do{PORT##id |= (((v)&_pin(port##_##7))|((v)&_pin(port##_##6))|((v)&_pin(port##_##5))|((v)&_pin(port##_##4))|((v)&_pin(port##_##3))|((v)&_pin(port##_##2))|((v)&_pin(port##_##1))|((v)&_pin(port##_##0)));\
                                                       }while(0);  
#define _PM_SetBitsPort_NONE(port, id, value) 

#define _PM_SetBitsPort(port, id, atr, value)            _PM_SetBitsPort##atr(port, id, value)
#define PM_SetBitsPort(port, value)                      _PM_SetBitsPort(port, value) 

/*__________________________ clear bits _____________________________________*/

#define __PM_ClearPinPort_HI(id, pin, value, num)        do{if (BM_BitIsClear(value, num)){BM_ClearBit(PORT##id, pin);}  \
                                                         }while(0)  

#define __PM_ClearPinPort_LOW(id, pin, value, num)       do{if (BM_BitIsClear(value, num)){BM_ClearBit(PORT##id, pin);}  \
                                                         }while(0)  

#define __PM_ClearPinPort_NONE(id, pin, value, num)
#define _PM_ClearPinPort(id, pin, lev, value, num)       __PM_ClearPinPort##lev(id, pin, value, num)
#define PM_ClearPinPort(port, value, num)                _PM_ClearPinPort(port, value, num)

#define _PM_ClearBitsPort_VIRT(port, id, value)          do{ PM_ClearPinPort(port##_##0, value, 0);\
                                                            PM_ClearPinPort(port##_##1, value, 1);\
                                                            PM_ClearPinPort(port##_##2, value, 2);\
                                                            PM_ClearPinPort(port##_##3, value, 3);\
                                                            PM_ClearPinPort(port##_##4, value, 4);\
                                                            PM_ClearPinPort(port##_##5, value, 5);\
                                                            PM_ClearPinPort(port##_##6, value, 6);\
                                                            PM_ClearPinPort(port##_##7, value, 7);\
                                                         }while(0)

#define _PM_ClearBitsPort_REAL(port, id, v)              do{PORT##id &= ~(((v)&_pin(port##_##7))|((v)&_pin(port##_##6))|((v)&_pin(port##_##5))|((v)&_pin(port##_##4))|((v)&_pin(port##_##3))|((v)&_pin(port##_##2))|((v)&_pin(port##_##1))|((v)&_pin(port##_##0)));\
                                                         }while(0);

#define _PM_ClearBitsPort_NONE(port, id, value) 

#define _PM_ClearBitsPort(port, id, atr, value)          _PM_ClearBitsPort##atr(port, id, value)
#define PM_ClearBitsPort(port, value)                    _PM_ClearBitsPort(port, value) 

/*_______________port macros. these macros are related with  pin's active levels___________ */

/*_________________________   OFF a port               ____________________________________*/
                                                                                                   
#define _PM_OffPort_VIRT(port, id)                      do{ PM_OffPin(port##_##0);\
                                                           PM_OffPin(port##_##1);\
                                                           PM_OffPin(port##_##2);\
                                                           PM_OffPin(port##_##3);\
                                                           PM_OffPin(port##_##4);\
                                                           PM_OffPin(port##_##5);\
                                                           PM_OffPin(port##_##6);\
                                                           PM_OffPin(port##_##7);\
                                                       }while(0)

#define _PM_OffPort_REAL(port, id)                    do{  uint8_t value = _pinLev(port##_##7)|_pinLev(port##_##6)|_pinLev(port##_##5)|_pinLev(port##_##4)|_pinLev(port##_##3)|_pinLev(port##_##2)|_pinLev(port##_##1)|_pinLev(port##_##0); \
                                                           uint8_t mask = _pin(port##_##7)|_pin(port##_##6)|_pin(port##_##5)|_pin(port##_##4)|_pin(port##_##3)|_pin(port##_##2)|_pin(port##_##1)|_pin(port##_##0); \
                                                                   PORT##id = (PORT##id & (~mask))|(~value & mask); \
                                                         }while(0)

#define _PM_OffPort_NONE(port, id) 

#define _PM_OffPort(port, id, atr)                     _PM_OffPort##atr(port, id)
#define PM_OffPort(port)                               _PM_OffPort(port) 

/*_________________________ ON a port ____________________________________*/
                                                                                                   
#define _PM_OnPort_VIRT(port, id)                     do{ PM_OnPin(port##_##0);\
                                                           PM_OnPin(port##_##1);\
                                                           PM_OnPin(port##_##2);\
                                                           PM_OnPin(port##_##3);\
                                                           PM_OnPin(port##_##4);\
                                                           PM_OnPin(port##_##5);\
                                                           PM_OnPin(port##_##6);\
                                                           PM_OnPin(port##_##7);\
                                                       }while(0)


#define _PM_OnPort_REAL(port, id)                    do{  uint8_t value = _pinLev(port##_##7)|_pinLev(port##_##6)|_pinLev(port##_##5)|_pinLev(port##_##4)|_pinLev(port##_##3)|_pinLev(port##_##2)|_pinLev(port##_##1)|_pinLev(port##_##0); \
                                                          uint8_t mask = _pin(port##_##7)|_pin(port##_##6)|_pin(port##_##5)|_pin(port##_##4)|_pin(port##_##3)|_pin(port##_##2)|_pin(port##_##1)|_pin(port##_##0); \
                                                                  PORT##id = (PORT##id & (~mask))|(value & mask); \
                                                      }while(0)

#define _PM_OnPort_NONE(port, id) 

#define _PM_OnPort(port, id, atr)                    _PM_OnPort##atr(port, id)
#define PM_OnPort(port)                              _PM_OnPort(port) 

/*________________________ set a bit to a port _______________________________*/


#define __plm_NONE(pin)                 0
#define __plm_LOW(pin)                 (1<<(pin))
#define __plm_HI(pin)                   0
#define __plm(id, pin, lev)             __plm##lev(pin)
#define _plm(x)                         __plm(x)

#define __phm_NONE(pin)                 0
#define __phm_LOW(pin)                  0
#define __phm_HI(pin)                   (1<<(pin))
#define __phm(id, pin, lev)             __phm##lev(pin)
#define _phm(x)                         __phm(x)

#define __PM_SetLevPinPort_HI(id, pin, value, num)     do{if (BM_BitIsSet(value, num)){BM_SetBit(PORT##id, pin);}  \
                                                       }while(0)  

#define __PM_SetLevPinPort_LOW(id, pin, value, num)    do{if (BM_BitIsSet(value, num)){BM_ClearBit(PORT##id, pin);}  \
                                                       }while(0)  

#define __PM_SetLevPinPort_NONE(id, pin, value, num)
#define _PM_SetLevPinPort(id, pin, lev, value, num)    __PM_SetLevPinPort##lev(id, pin, value, num)
#define PM_SetLevPinPort(port, value, num)             _PM_SetLevPinPort(port, value, num)

#define _PM_SetLevBitsPort_VIRT(port, id, value)          do{ PM_SetLevPinPort(port##_##0, value, 0);\
                                                           PM_SetLevPinPort(port##_##1, value, 1);\
                                                           PM_SetLevPinPort(port##_##2, value, 2);\
                                                           PM_SetLevPinPort(port##_##3, value, 3);\
                                                           PM_SetLevPinPort(port##_##4, value, 4);\
                                                           PM_SetLevPinPort(port##_##5, value, 5);\
                                                           PM_SetLevPinPort(port##_##6, value, 6);\
                                                           PM_SetLevPinPort(port##_##7, value, 7);\
                                                       }while(0)

#define _PM_SetLevBitsPort_REAL(port, id, v)            do{ uint8_t hmask = _phm(port##_##7)|_phm(port##_##6)|_phm(port##_##5)|_phm(port##_##4)|_phm(port##_##3)|_phm(port##_##2)|_phm(port##_##1)|_phm(port##_##0); \
                                                            uint8_t lmask = _plm(port##_##7)|_plm(port##_##6)|_plm(port##_##5)|_plm(port##_##4)|_plm(port##_##3)|_plm(port##_##2)|_plm(port##_##1)|_plm(port##_##0); \
                                                              PORT##id |= (v & hmask); \
                                                              PORT##id &= ~(v & lmask); \
                                                         }while(0);

#define _PM_SetLevBitsPort_NONE(port, id, v) 

#define _PM_SetLevBitsPort(port, id, atr, v)          _PM_SetLevBitsPort##atr(port, id, v)
#define PM_SetLevBitsPort(port, v)                    _PM_SetLevBitsPort(port, v)

#endif //PORT_MACROS_H