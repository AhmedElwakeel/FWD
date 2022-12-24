#ifndef __DRIVERLIB_INTERRUPT_H__
#define __DRIVERLIB_INTERRUPT_H__

#include <stdbool.h>
#include <stdint.h>
#include "hw_ints.h"
#include "hw_nvic.h"
#include "Platform_Types.h"
#include <stdint.h>
#include "tm4c123gh6pm_registers.h"
#include "Common_Macros.h"

//*****************************************************************************
//
// Macro to generate an interrupt priority mask based on the number of bits
// of priority supported by the hardware.
//
//*****************************************************************************
#define INT_PRIORITY_MASK       ((0xFF << (8 - NUM_PRIORITY_BITS)) & 0xFF)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
uint32 IntMasterEnable(void);
uint32 IntMasterDisable(void);
void IntPriorityGroupingSet(uint32 ui32Bits);
void IntPrioritySet(uint32 ui32Interrupt,uint8 ui8Priority);
void IntEnable(uint32 ui32Interrupt);
void IntDisable(uint32 ui32Interrupt);
void IntPendSet(uint32 ui32Interrupt);
void IntPendClear(uint32 ui32Interrupt);
void IntPriorityMaskSet(uint32 ui32PriorityMask);
void IntTrigger(uint32 ui32Interrupt);

#endif // __DRIVERLIB_INTERRUPT_H__
