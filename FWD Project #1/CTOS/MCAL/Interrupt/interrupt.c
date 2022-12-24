#include "interrupt.h"

//*****************************************************************************
//
// This is a mapping between priority grouping encodings and the number of
// preemption priority bits.
//
//*****************************************************************************
static const uint32 g_pui32Priority[] =
{
    NVIC_APINT_PRIGROUP_0_8, NVIC_APINT_PRIGROUP_1_7, NVIC_APINT_PRIGROUP_2_6,
    NVIC_APINT_PRIGROUP_3_5, NVIC_APINT_PRIGROUP_4_4, NVIC_APINT_PRIGROUP_5_3,
    NVIC_APINT_PRIGROUP_6_2, NVIC_APINT_PRIGROUP_7_1
};

//*****************************************************************************
//
// This is a mapping between interrupt number and the register that contains
// the priority encoding for that interrupt.
//
//*****************************************************************************
static const uint32 g_pui32Regs[] =
{
    0, NVIC_SYS_PRI1, NVIC_SYS_PRI2, NVIC_SYS_PRI3, NVIC_PRI0, NVIC_PRI1,
    NVIC_PRI2, NVIC_PRI3, NVIC_PRI4, NVIC_PRI5, NVIC_PRI6, NVIC_PRI7,
    NVIC_PRI8, NVIC_PRI9, NVIC_PRI10, NVIC_PRI11, NVIC_PRI12, NVIC_PRI13,
    NVIC_PRI14, NVIC_PRI15, NVIC_PRI16, NVIC_PRI17, NVIC_PRI18, NVIC_PRI19,
    NVIC_PRI20, NVIC_PRI21, NVIC_PRI22, NVIC_PRI23, NVIC_PRI24, NVIC_PRI25,
    NVIC_PRI26, NVIC_PRI27, NVIC_PRI28, NVIC_PRI29, NVIC_PRI30, NVIC_PRI31,
    NVIC_PRI32, NVIC_PRI33, NVIC_PRI34
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt enable for that
// interrupt.
//
//*****************************************************************************
static const uint32 g_pui32EnRegs[] =
{
    NVIC_EN0, NVIC_EN1, NVIC_EN2, NVIC_EN3, NVIC_EN4
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt disable for that
// interrupt.
//
//*****************************************************************************
static const uint32 g_pui32Dii16Regs[] =
{
    NVIC_DIS0, NVIC_DIS1, NVIC_DIS2, NVIC_DIS3, NVIC_DIS4
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt pend for that interrupt.
//
//*****************************************************************************
static const uint32 g_pui32PendRegs[] =
{
    NVIC_PEND0, NVIC_PEND1, NVIC_PEND2, NVIC_PEND3, NVIC_PEND4
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt unpend for that
// interrupt.
//
//*****************************************************************************
static const uint32 g_pui32UnpendRegs[] =
{
    NVIC_UNPEND0, NVIC_UNPEND1, NVIC_UNPEND2, NVIC_UNPEND3, NVIC_UNPEND4
};




//*****************************************************************************
//
// The processor vector table.
//
// This contains a list of the handlers for the various interrupt sources in
// the system.  The layout of this list is defined by the hardware; assertion
// of an interrupt causes the processor to start executing directly at the
// address given in the corresponding location in this list.
//
//*****************************************************************************
//
// Set the size of the vector table to the largest number of interrupts of
// any device
//
#undef NUM_INTERRUPTS
#define NUM_INTERRUPTS                          155



uint32 IntMasterEnable(void)
{
    //
    // Enable processor interrupts.
    //
     __asm("    mrs     r0, PRIMASK\n"
          "    cpsie   i\n"
          "    bx      lr\n");// Read PRIMASK and enable interrupts.
    return(0);
}

uint32 IntMasterDisable(void)
{
    //
    // Disable processor interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsid   i\n"
          "    bx      lr\n");// Read PRIMASK and disable interrupts.
    return(0);
}

void IntPriorityGroupingSet(uint32 ui32Bits)
{
    //
    // Set the priority grouping.
    //
    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | g_pui32Priority[ui32Bits];
}

void IntPrioritySet(uint32 ui32Interrupt, uint8_t ui8Priority)
{
    uint32 ui32Temp;
    //
    // Set the interrupt priority.
    //
    ui32Temp = HWREG(g_pui32Regs[ui32Interrupt >> 2]);
    ui32Temp &= ~((uint32)(0xFF << (8 * (ui32Interrupt & 3))));
    ui32Temp |= (uint32)ui8Priority << (8 * (ui32Interrupt & 3));
    HWREG(g_pui32Regs[ui32Interrupt >> 2]) = ui32Temp;
}

void IntEnable(uint32 ui32Interrupt)
{
    //
    // Determine the interrupt to enable.
    //
    if(ui32Interrupt == FAULT_MPU)
    {
        //
        // Enable the MemManage interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_MEM;
    }
    else if(ui32Interrupt == FAULT_BUS)
    {
        //
        // Enable the bus fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_BUS;
    }
    else if(ui32Interrupt == FAULT_USAGE)
    {
        //
        // Enable the usage fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_USAGE;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        //
        // Enable the System Tick interrupt.
        //
        HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
    }
    else if(ui32Interrupt >= 16)
    {
        //
        // Enable the general interrupt.
        //
        HWREG(g_pui32EnRegs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

void IntDisable(uint32 ui32Interrupt)
{
    //
    // Determine the interrupt to disable.
    //
    if(ui32Interrupt == FAULT_MPU)
    {
        //
        // Disable the MemManage interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) &= ~((uint32)(NVIC_SYS_HND_CTRL_MEM));
    }
    else if(ui32Interrupt == FAULT_BUS)
    {
        //
        // Disable the bus fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) &= ~((uint32)(NVIC_SYS_HND_CTRL_BUS));
    }
    else if(ui32Interrupt == FAULT_USAGE)
    {
        //
        // Disable the usage fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) &= ~(uint32)(NVIC_SYS_HND_CTRL_USAGE);
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        //
        // Disable the System Tick interrupt.
        //
				CLEAR_BIT(HWREG(NVIC_ST_CTRL),NVIC_ST_CTRL_INTEN);
    }
    else if(ui32Interrupt >= 16)
    {
        //
        // Disable the general interrupt.
        //
        HWREG(g_pui32Dii16Regs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

void IntPendSet(uint32 ui32Interrupt)
{
    //
    // Determine the interrupt to pend.
    //
    if(ui32Interrupt == FAULT_NMI)
    {
        //
        // Pend the NMI interrupt.
        //
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_NMI_SET;
    }
    else if(ui32Interrupt == FAULT_PENDSV)
    {
        //
        // Pend the PendSV interrupt.
        //
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PEND_SV;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        //
        // Pend the SysTick interrupt.
        //
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PENDSTSET;
    }
    else if(ui32Interrupt >= 16)
    {
        //
        // Pend the general interrupt.
        //
        HWREG(g_pui32PendRegs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

void IntPendClear(uint32 ui32Interrupt)
{
    //
    // Determine the interrupt to unpend.
    //
    if(ui32Interrupt == FAULT_PENDSV)
    {
        //
        // Unpend the PendSV interrupt.
        //
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_UNPEND_SV;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        //
        // Unpend the SysTick interrupt.
        //
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PENDSTCLR;
    }
    else if(ui32Interrupt >= 16)
    {
        //
        // Unpend the general interrupt.
        //
        HWREG(g_pui32UnpendRegs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

void IntPriorityMaskSet(uint32 ui32PriorityMask)
{
    //
    // Set the priority mask.
    //
	__asm("    msr     BASEPRI, r0\n"); // Set the BASEPRI register
}

void IntTrigger(uint32 ui32Interrupt)
{
    //
    // Trigger this interrupt.
    //
    HWREG(NVIC_SW_TRIG) = ui32Interrupt - 16;
}
