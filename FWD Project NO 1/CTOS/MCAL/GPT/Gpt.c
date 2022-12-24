#include "Gpt.h"
#define SYSTICK_INTERRUPT_PRIORITY  3
/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */
static void (*g_SysTick_Call_Back_Ptr)(void) = NULL_PTR;

/************************************************************************************
* Service Name: SysTick_Handler
* Description: SysTick Timer ISR
************************************************************************************/
void SysTick_Handler(void)
{
    /* Check if the Timer0_setCallBack is already called */
    if(g_SysTick_Call_Back_Ptr != NULL_PTR)
    {
        (*g_SysTick_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
}
void SysTick_Init(uint32 Tick_Time)
{
    SYSTICK_CTRL_REG    = 0;                         /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = Tick_Time - 1;             /* Set the Reload value to count n miliseconds */
    SYSTICK_CURRENT_REG = 0;                         /* Clear the Current Register value */
    /* Configure the SysTick Control Register */
		SYSTICK_CTRL_REG   |= 0x04;//Choose the clock source to be System Clock (CLK_SRC = 1)
		SysTick_Start();//Enable the SysTick Timer (ENABLE = 1)
		IntEnable(FAULT_SYSTICK);//Enable SysTick Interrupt (INTEN = 1)    
		IntPrioritySet(NVIC_SYSTEM_PRI3_REG,SYSTICK_INTERRUPT_PRIORITY);/* Assign priority level 3 to the SysTick Interrupt */
}
void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG &=~((uint32)(1<<0)); /* Disable the SysTick Timer by Clear the ENABLE Bit */
}
void SysTick_Start(void)
{
    SYSTICK_CTRL_REG |= (1<<0); /* Enable the SysTick Timer by Clear the ENABLE Bit */
}
void SysTick_SetCallBack(void(*Ptr2Func)(void))
{
    g_SysTick_Call_Back_Ptr = Ptr2Func;
}
