#ifndef TM4C123GH6PM_REGISTERS
#define TM4C123GH6PM_REGISTERS

#include "Std_Types.h"

/* GPIO Registers base addresses */
#define PORTA_BASE_ADDRESS           0x40004000
#define PORTB_BASE_ADDRESS           0x40005000
#define PORTC_BASE_ADDRESS           0x40006000
#define PORTD_BASE_ADDRESS           0x40007000
#define PORTE_BASE_ADDRESS           0x40024000
#define PORTF_BASE_ADDRESS           0x40025000


typedef struct {                               /*!< GPIO Structure                                                      */
  uint32  RESERVED[255];
  uint32  DATA;                              /*!< GPIO Data                                                             */
  uint32  DIR;                               /*!< GPIO Direction                                                        */
  uint32  IS;                                /*!< GPIO Interrupt Sense                                                  */
  uint32  IBE;                               /*!< GPIO Interrupt Both Edges                                             */
  uint32  IEV;                               /*!< GPIO Interrupt Event                                                  */
  uint32  IM;                                /*!< GPIO Interrupt Mask                                                   */
  uint32  RIS;                               /*!< GPIO Raw Interrupt Status                                             */
  uint32  MIS;                               /*!< GPIO Masked Interrupt Status                                          */
  uint32  ICR;                               /*!< GPIO Interrupt Clear                                                  */
  uint32  AFSEL;                             /*!< GPIO Alternate Function Select                                        */
  uint32  RESERVED1[55];
  uint32  DR2R;                              /*!< GPIO 2-mA Drive Select                                                */
  uint32  DR4R;                              /*!< GPIO 4-mA Drive Select                                                */
  uint32  DR8R;                              /*!< GPIO 8-mA Drive Select                                                */
  uint32  ODR;                               /*!< GPIO Open Drain Select                                                */
  uint32  PUR;                               /*!< GPIO Pull-Up Select                                                   */
  uint32  PDR;                               /*!< GPIO Pull-Down Select                                                 */
  uint32  SLR;                               /*!< GPIO Slew Rate Control Select                                         */
  uint32  DEN;                               /*!< GPIO Digital Enable                                                   */
  uint32  LOCK;                              /*!< GPIO Lock                                                             */
  uint32  CR;                                /*!< GPIO Commit                                                           */
  uint32  AMSEL;                             /*!< GPIO Analog Mode Select                                               */
  uint32  PCTL;                              /*!< GPIO Port Control                                                     */
  uint32  ADCCTL;                            /*!< GPIO ADC Control                                                      */
  uint32  DMACTL;                            /*!< GPIO DMA Control                                                      */
} GPIO_Type;
/*****************************************************************************
GPIO OFFSET ADDRESS 
*****************************************************************************/
#define GPIODATA			0x038
#define GPIODIR				0x400
#define GPIOIS				0x404
#define GPIOIBE				0x408
#define GPIOIEV				0x40C
#define GPIOIM				0x410
#define GPIORIS				0x414
#define GPIOMIS				0x418
#define GPIOICR				0x41C
#define GPIOAFSEL			0x420
#define GPIODR2R			0x500
#define GPIODR4R			0x504
#define GPIODR8R			0x508
#define GPIOODR				0x50C
#define GPIOPUR				0x510
#define GPIOPDR				0x514
#define GPIOSLR				0x518
#define GPIODEN				0x51C
#define GPIOLOCK			0x520
#define GPIOCR				0x524
#define GPIOAMSEL			0x528
#define GPIOPCTL			0x52C
#define GPIOADCCTL		0x530
#define GPIODMACTL		0x534
#define GPIOSI				0x538
#define GPIOPeriphID4	0xFD0
#define GPIOPeriphID5	0xFD4
#define GPIOPeriphID6	0xFD8
#define GPIOPeriphID7	0xFDC
#define GPIOPeriphID0	0xFE0
#define GPIOPeriphID1	0xFE4
#define GPIOPeriphID2	0xFE8
#define GPIOPeriphID3	0xFEC
#define GPIOPCellID0	0xFF0
#define GPIOPCellID1	0xFF4
#define GPIOPCellID2	0xFF8
#define GPIOPCellID3	0xFFC

/*****************************************************************************
GPIO registers (PORTA)
*****************************************************************************/
#define GPIO_PORTA_DATA_REG       (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTA_DIR_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIODIR)))
#define GPIO_PORTA_AFSEL_REG      (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOAFSEL)))
#define GPIO_PORTA_PUR_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOPUR)))
#define GPIO_PORTA_PDR_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOPDR)))
#define GPIO_PORTA_DEN_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIODEN)))
#define GPIO_PORTA_LOCK_REG       (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOLOCK)))
#define GPIO_PORTA_CR_REG         (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOCR)))
#define GPIO_PORTA_AMSEL_REG      (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOAMSEL)))
#define GPIO_PORTA_PCTL_REG       (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOPCTL)))

/* PORTA External Interrupts Registers */
#define GPIO_PORTA_IS_REG         (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOIS)))
#define GPIO_PORTA_IBE_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOIBE)))
#define GPIO_PORTA_IEV_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTA_IM_REG         (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOIEV)))
#define GPIO_PORTA_RIS_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIORIS)))
#define GPIO_PORTA_ICR_REG        (*((volatile uint32 *)(PORTA_BASE_ADDRESS + GPIOICR)))

/*****************************************************************************
GPIO registers (PORTB)
*****************************************************************************/
#define GPIO_PORTB_DATA_REG       (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTB_DIR_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIODIR)))
#define GPIO_PORTB_AFSEL_REG      (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOAFSEL)))
#define GPIO_PORTB_PUR_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOPUR)))
#define GPIO_PORTB_PDR_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOPDR)))
#define GPIO_PORTB_DEN_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIODEN)))
#define GPIO_PORTB_LOCK_REG       (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOLOCK)))
#define GPIO_PORTB_CR_REG         (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOCR)))
#define GPIO_PORTB_AMSEL_REG      (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOAMSEL)))
#define GPIO_PORTB_PCTL_REG       (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOPCTL)))

/* PORTA External Interrupts Registers */
#define GPIO_PORTB_IS_REG         (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOIS)))
#define GPIO_PORTB_IBE_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOIBE)))
#define GPIO_PORTB_IEV_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTB_IM_REG         (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOIEV)))
#define GPIO_PORTB_RIS_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIORIS)))
#define GPIO_PORTB_ICR_REG        (*((volatile uint32 *)(PORTB_BASE_ADDRESS + GPIOICR)))

/*****************************************************************************
GPIO registers (PORTC)
*****************************************************************************/
#define GPIO_PORTC_DATA_REG       (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTC_DIR_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIODIR)))
#define GPIO_PORTC_AFSEL_REG      (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOAFSEL)))
#define GPIO_PORTC_PUR_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOPUR)))
#define GPIO_PORTC_PDR_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOPDR)))
#define GPIO_PORTC_DEN_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIODEN)))
#define GPIO_PORTC_LOCK_REG       (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOLOCK)))
#define GPIO_PORTC_CR_REG         (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOCR)))
#define GPIO_PORTC_AMSEL_REG      (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOAMSEL)))
#define GPIO_PORTC_PCTL_REG       (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOPCTL)))

/* PORTC External Interrupts Registers */
#define GPIO_PORTC_IS_REG         (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOIS)))
#define GPIO_PORTC_IBE_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOIBE)))
#define GPIO_PORTC_IEV_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTC_IM_REG         (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOIEV)))
#define GPIO_PORTC_RIS_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIORIS)))
#define GPIO_PORTC_ICR_REG        (*((volatile uint32 *)(PORTC_BASE_ADDRESS + GPIOICR)))

/*****************************************************************************
GPIO registers (PORTD)
*****************************************************************************/
#define GPIO_PORTD_DATA_REG       (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTD_DIR_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIODIR)))
#define GPIO_PORTD_AFSEL_REG      (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOAFSEL)))
#define GPIO_PORTD_PUR_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOPUR)))
#define GPIO_PORTD_PDR_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOPDR)))
#define GPIO_PORTD_DEN_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIODEN)))
#define GPIO_PORTD_LOCK_REG       (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOLOCK)))
#define GPIO_PORTD_CR_REG         (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOCR)))
#define GPIO_PORTD_AMSEL_REG      (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOAMSEL)))
#define GPIO_PORTD_PCTL_REG       (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOPCTL)))

/* PORTD External Interrupts Registers */
#define GPIO_PORTD_IS_REG         (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOIS)))
#define GPIO_PORTD_IBE_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOIBE)))
#define GPIO_PORTD_IEV_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTD_IM_REG         (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOIEV)))
#define GPIO_PORTD_RIS_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIORIS)))
#define GPIO_PORTD_ICR_REG        (*((volatile uint32 *)(PORTD_BASE_ADDRESS + GPIOICR)))

/*****************************************************************************
GPIO registers (PORTE)
*****************************************************************************/
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTE_DIR_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIODIR)))
#define GPIO_PORTE_AFSEL_REG      (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOAFSEL)))
#define GPIO_PORTE_PUR_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOPUR)))
#define GPIO_PORTE_PDR_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOPDR)))
#define GPIO_PORTE_DEN_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIODEN)))
#define GPIO_PORTE_LOCK_REG       (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOLOCK)))
#define GPIO_PORTE_CR_REG         (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOCR)))
#define GPIO_PORTE_AMSEL_REG      (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOAMSEL)))
#define GPIO_PORTE_PCTL_REG       (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOPCTL)))

/* PORTE External Interrupts Registers */
#define GPIO_PORTE_IS_REG         (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOIS)))
#define GPIO_PORTE_IBE_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOIBE)))
#define GPIO_PORTE_IEV_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTE_IM_REG         (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOIEV)))
#define GPIO_PORTE_RIS_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIORIS)))
#define GPIO_PORTE_ICR_REG        (*((volatile uint32 *)(PORTE_BASE_ADDRESS + GPIOICR)))

/*****************************************************************************
GPIO registers (PORTF)
*****************************************************************************/
#define GPIO_PORTF_DATA_REG       (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTF_DIR_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIODIR)))
#define GPIO_PORTF_AFSEL_REG      (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOAFSEL)))
#define GPIO_PORTF_PUR_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOPUR)))
#define GPIO_PORTF_PDR_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOPDR)))
#define GPIO_PORTF_DEN_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIODEN)))
#define GPIO_PORTF_LOCK_REG       (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOLOCK)))
#define GPIO_PORTF_CR_REG         (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOCR)))
#define GPIO_PORTF_AMSEL_REG      (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOAMSEL)))
#define GPIO_PORTF_PCTL_REG       (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOPCTL)))

/* PORTF External Interrupts Registers */
#define GPIO_PORTF_IS_REG         (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOIS)))
#define GPIO_PORTF_IBE_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOIBE)))
#define GPIO_PORTF_IEV_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIODATA)))
#define GPIO_PORTF_IM_REG         (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOIEV)))
#define GPIO_PORTF_RIS_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIORIS)))
#define GPIO_PORTF_ICR_REG        (*((volatile uint32 *)(PORTF_BASE_ADDRESS + GPIOICR)))


/*****************************************************************************
GPIO CLOCK GATE Registers
*****************************************************************************/
#define SYSCTL_RCGCGPIO_REG        (*((volatile uint32 *)0x400FE608))


/*****************************************************************************
Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))

/*****************************************************************************
PLL Registers
*****************************************************************************/
#define SYSCTL_RIS_REG            (*((volatile uint32 *)0x400FE050))
#define SYSCTL_RCC_REG            (*((volatile uint32 *)0x400FE060))
#define SYSCTL_RCC2_REG           (*((volatile uint32 *)0x400FE070))

/*****************************************************************************
NVIC Registers
*****************************************************************************/
#define NVIC_PRI0_REG             (*((volatile uint32 *)0xE000E400))
#define NVIC_PRI1_REG             (*((volatile uint32 *)0xE000E404))
#define NVIC_PRI2_REG             (*((volatile uint32 *)0xE000E408))
#define NVIC_PRI3_REG             (*((volatile uint32 *)0xE000E40C))
#define NVIC_PRI4_REG             (*((volatile uint32 *)0xE000E410))
#define NVIC_PRI5_REG             (*((volatile uint32 *)0xE000E414))
#define NVIC_PRI6_REG             (*((volatile uint32 *)0xE000E418))
#define NVIC_PRI7_REG             (*((volatile uint32 *)0xE000E41C))
#define NVIC_PRI8_REG             (*((volatile uint32 *)0xE000E420))
#define NVIC_PRI9_REG             (*((volatile uint32 *)0xE000E424))
#define NVIC_PRI10_REG            (*((volatile uint32 *)0xE000E428))
#define NVIC_PRI11_REG            (*((volatile uint32 *)0xE000E42C))
#define NVIC_PRI12_REG            (*((volatile uint32 *)0xE000E430))
#define NVIC_PRI13_REG            (*((volatile uint32 *)0xE000E434))
#define NVIC_PRI14_REG            (*((volatile uint32 *)0xE000E438))
#define NVIC_PRI15_REG            (*((volatile uint32 *)0xE000E43C))
#define NVIC_PRI16_REG            (*((volatile uint32 *)0xE000E440))
#define NVIC_PRI17_REG            (*((volatile uint32 *)0xE000E444))
#define NVIC_PRI18_REG            (*((volatile uint32 *)0xE000E448))
#define NVIC_PRI19_REG            (*((volatile uint32 *)0xE000E44C))
#define NVIC_PRI20_REG            (*((volatile uint32 *)0xE000E450))
#define NVIC_PRI21_REG            (*((volatile uint32 *)0xE000E454))
#define NVIC_PRI22_REG            (*((volatile uint32 *)0xE000E458))
#define NVIC_PRI23_REG            (*((volatile uint32 *)0xE000E45C))
#define NVIC_PRI24_REG            (*((volatile uint32 *)0xE000E460))
#define NVIC_PRI25_REG            (*((volatile uint32 *)0xE000E464))
#define NVIC_PRI26_REG            (*((volatile uint32 *)0xE000E468))
#define NVIC_PRI27_REG            (*((volatile uint32 *)0xE000E46C))
#define NVIC_PRI28_REG            (*((volatile uint32 *)0xE000E470))
#define NVIC_PRI29_REG            (*((volatile uint32 *)0xE000E474))
#define NVIC_PRI30_REG            (*((volatile uint32 *)0xE000E478))
#define NVIC_PRI31_REG            (*((volatile uint32 *)0xE000E47C))
#define NVIC_PRI32_REG            (*((volatile uint32 *)0xE000E480))
#define NVIC_PRI33_REG            (*((volatile uint32 *)0xE000E484))
#define NVIC_PRI34_REG            (*((volatile uint32 *)0xE000E488))

#define NVIC_EN0_REG              (*((volatile uint32 *)0xE000E100))
#define NVIC_EN1_REG              (*((volatile uint32 *)0xE000E104))
#define NVIC_EN2_REG              (*((volatile uint32 *)0xE000E108))
#define NVIC_EN3_REG              (*((volatile uint32 *)0xE000E10C))
#define NVIC_EN4_REG              (*((volatile uint32 *)0xE000E110))
#define NVIC_DIS0_REG             (*((volatile uint32 *)0xE000E180))
#define NVIC_DIS1_REG             (*((volatile uint32 *)0xE000E184))
#define NVIC_DIS2_REG             (*((volatile uint32 *)0xE000E188))
#define NVIC_DIS3_REG             (*((volatile uint32 *)0xE000E18C))
#define NVIC_DIS4_REG             (*((volatile uint32 *)0xE000E190))

#define NVIC_SYSTEM_PRI1_REG      (*((volatile uint32 *)0xE000ED18))
#define NVIC_SYSTEM_PRI2_REG      (*((volatile uint32 *)0xE000ED1C))
#define NVIC_SYSTEM_PRI3_REG      (*((volatile uint32 *)0xE000ED20))
#define NVIC_SYSTEM_SYSHNDCTRL    (*((volatile uint32 *)0xE000ED24))

#endif
