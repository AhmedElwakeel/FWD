#ifndef GPT_H
#define GPT_H
#include "tm4c123gh6pm_registers.h"
#include "Std_Types.h"
#include "interrupt.h"
void SysTick_Init(uint32 Tick_Time);
void SysTick_Start(void);
void SysTick_Stop(void);
void SysTick_SetCallBack(void (*Ptr2Func)(void));
void SysTick_Handler(void);
#endif /* GPT_H */
