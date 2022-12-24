#include "Port.h"
#include "tm4c123gh6pm_registers.h"

/************************************************************************************
* Service Name: Port_Init
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Return value: None
* Description: Function to Initializes the Port Driver module
*       
************************************************************************************/
STATIC volatile Port_ConfigPins* PortConf = NULL_PTR;
void Port_Init(volatile Port_ConfigType* ConfigPtr )
{
    volatile GPIO_Type * Selected_GPIO_Port = NULL_PTR; 	/* point to the required Port Registers base address */
    PortConf = ConfigPtr->Pins;     						/*points to the 1st address of the array of structure*/
	
		for (uint8 Pin_Index = 0; Pin_Index < PORT_NUMBER_OF_PORT_PINS ; Pin_Index++) 
		{
							if(PortConf[Pin_Index].Selected == 0)//Skip if this Pin Not Needed
							{
								continue;
							}
							/*****************************************************************************************************************/
							switch(PortConf[Pin_Index].port_num)
							{
									case  0: Selected_GPIO_Port = (volatile GPIO_Type *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
									break; 
									case  1: Selected_GPIO_Port = (volatile GPIO_Type *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
									break;
									case  2: Selected_GPIO_Port = (volatile GPIO_Type *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
									break;
									case  3: Selected_GPIO_Port = (volatile GPIO_Type *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
									break;
									case  4: Selected_GPIO_Port = (volatile GPIO_Type *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
									break;
									case  5: 
										Selected_GPIO_Port = (volatile GPIO_Type *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
										SYSCTL_RCGCGPIO_REG |= 0x20;//ENABLE CLOCK
									break;
							}    													
							/*****************************************************************************************************************/
							
							/*****************************************************************************************************************/
							/* Enable clock for PORT and allow time for clock to start*/
							if( ((PortConf[Pin_Index].port_num== 3) && (PortConf[Pin_Index].pin_num== 7)) || ((PortConf[Pin_Index].port_num == 5) && (PortConf[Pin_Index].pin_num == 0)) ) /* PD7 or PF0 */
							{
									Selected_GPIO_Port->LOCK = 0x4C4F434B; /* Unlock the GPIOCR register */   
									SET_BIT(Selected_GPIO_Port->CR , PortConf[Pin_Index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
							}						
							/*****************************************************************************************************************/
							/********************************************Direction,initial_value,resistor**************************************************/
							if(PortConf[Pin_Index].direction == PORT_PIN_OUT)
							{
								SET_BIT(Selected_GPIO_Port->DIR , PortConf[Pin_Index].pin_num);/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
								if(PortConf[Pin_Index].initial_value == STD_HIGH)
								{
										SET_BIT(Selected_GPIO_Port->DATA , PortConf[Pin_Index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
								}
								else
								{
										CLEAR_BIT(Selected_GPIO_Port->DATA , PortConf[Pin_Index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
								}
							}
							/*****************************************************************************************************************/
							else if(PortConf[Pin_Index].direction == PORT_PIN_IN)
							{
									CLEAR_BIT(Selected_GPIO_Port->DIR , PortConf[Pin_Index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
									if(PortConf[Pin_Index].resistor == PULL_UP)
									{
											SET_BIT(Selected_GPIO_Port->PUR , PortConf[Pin_Index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
									}
									else if(PortConf[Pin_Index].resistor == PULL_DOWN)
									{
											SET_BIT(Selected_GPIO_Port->PDR , PortConf[Pin_Index].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
									}
									else
									{
											CLEAR_BIT(Selected_GPIO_Port->PUR , PortConf[Pin_Index].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
											CLEAR_BIT(Selected_GPIO_Port->PDR , PortConf[Pin_Index].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
									}
							}
							else
							{
									/* Do Nothing */
							}   
							
							/*********************************************Check Mode**************************************************/
							if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_DIO)
							{								
								CLEAR_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin_Index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
								CLEAR_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
								Selected_GPIO_Port->PCTL &= ~(uint32)(0x0000000F << (PortConf[Pin_Index].pin_num * 4));     /* Clear the PMCx bits for this pin */   
								SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
							}
							/*****************************************************************************************************************/   
               
//							if(PortConf[Pin_Index].pin_mode == PORT_PIN_MODE_UART)
//							{ 
//								CLEAR_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin_Index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
//								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);        /* ENable Alternative function for this pin*/
//								SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);      /*Enable Digital*/ 
//								if(Pin_Index==20||Pin_Index==21) /*PC4 ,PC5*/
//								{
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000002 << (PortConf[Pin_Index].pin_num * 4));
//								}
//								else
//								{
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000001 << (PortConf[Pin_Index].pin_num * 4));
//								}
//							}
							/*****************************************************************************************************************/  
//							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_ADC)
//							{  
//								/*Should i enable RCGCADC and PLL ??*/
//								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);   /* ENable Alternative function for this pin*/
//								CLEAR_BIT(Selected_GPIO_Port->DIR , PortConf[Pin_Index].pin_num);   /*SEt as an input pin*/
//								CLEAR_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);   /*Disable Digital mode */      
//								SET_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin_Index].pin_num);   /*Enable analog functionality on this pin */
//							}
							/*****************************************************************************************************************/
//							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_CAN)
//							{								 
//								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);/* ENable Alternative function for this pin*/
//								if(Pin_Index==38 ||Pin_Index==41)/*PF0,PF3*/
//								{
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000003 << (PortConf[Pin_Index].pin_num * 4));
//								}
//								else
//								{
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000008 << (PortConf[Pin_Index].pin_num * 4));         
//								}
//								/*Tx(output) pin or Rx(input)*/
//							}
							/*****************************************************************************************************************/
//							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_SSI)
//							{    /*RCGCSSI register???*/
//								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);
//								SET_BIT(Selected_GPIO_Port->DEN 	, PortConf[Pin_Index].pin_num); /*set as Digital*/
//								SET_BIT(Selected_GPIO_Port->DIR 	, PortConf[Pin_Index].pin_num);           /*PULLUP */
//								if(Pin_Index==24 ||Pin_Index==25 ||Pin_Index==26 ||Pin_Index==27)/*PD0,PD1,PD2,PD3*/
//								{ 
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000001 << (PortConf[Pin_Index].pin_num * 4));  
//								}
//								else
//								{
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000002 << (PortConf[Pin_Index].pin_num * 4)); 
//								}
//							}
							/*****************************************************************************************************************/
//							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_I2C)
//							{
//							 SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);
//							 SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);
//							 SET_BIT(Selected_GPIO_Port->ODR , PortConf[Pin_Index].pin_num);  /*OPen drain select*/
//							 Selected_GPIO_Port->PCTL |= (uint32)(0x00000003 << (PortConf[Pin_Index].pin_num * 4));
//							}
						  /*****************************************************************************************************************/
//							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_PWM)
//							{  							 
//								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);
//								if(Pin_Index==12 ||Pin_Index==13 ||Pin_Index==14 ||Pin_Index==15||Pin_Index==20 ||Pin_Index==21 ||Pin_Index==24||Pin_Index==25|Pin_Index==36 ||Pin_Index==37)/*PB4--PB7 , PC4,5  ,PD0,1 ,PE4,5*/
//								{
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000004 << (PortConf[Pin_Index].pin_num * 4));
//								}
//								else
//								{
//									Selected_GPIO_Port->PCTL |= (uint32)(0x00000005<< (PortConf[Pin_Index].pin_num * 4));
//								}
//							}
							/*****************************************************************************************************************/
							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_USB)
							{
								Selected_GPIO_Port->PCTL |= (uint32)(0x00000008<< (PortConf[Pin_Index].pin_num * 4));
							}           
							/*****************************************************************************************************************/
							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_QEI) 
							{   
								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);
							  Selected_GPIO_Port->PCTL |= (uint32)(0x00000006<< (PortConf[Pin_Index].pin_num * 4));
								SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);
							}  
							/*****************************************************************************************************************/
							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_GPT) 
							{   
								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);               /* ENable Alternative function for this pin*/
								Selected_GPIO_Port->PCTL |= (uint32)(0x00000007<< (PortConf[Pin_Index].pin_num * 4));
								SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);
							} 
							/*****************************************************************************************************************/
							else if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_NMI) 
							{    
								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);
								Selected_GPIO_Port->PCTL |= (uint32)(0x00000008<< (PortConf[Pin_Index].pin_num * 4));
								SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);
							}    
							/*****************************************************************************************************************/
							if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_ANALOG_COMP) 
							{    
								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);
								if(Pin_Index==20 ||Pin_Index==21 ||Pin_Index==22 ||Pin_Index==23 )  /*PC4,5,6,7 analog pins  C1-,C1+,C0+,C0-*/
								{ 
									SET_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin_Index].pin_num);   /*Enable analog functionality on this pin */
									CLEAR_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);  /*Disable digital mode*/
								} 
								else
								{
									Selected_GPIO_Port->PCTL |= (uint32)(0x00000009<< (PortConf[Pin_Index].pin_num * 4));
									SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);
								}  
							}
							/*****************************************************************************************************************/
							if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_CORE) 
							{    
								SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin_Index].pin_num);
								Selected_GPIO_Port->PCTL |= (uint32)(0x0000000E<< (PortConf[Pin_Index].pin_num * 4));
								SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin_Index].pin_num);
							}  
							/*****************************************************************************************************************/
        }       
}  
/******************************************************************************************
* Service Name: Port_SetPinDirection
* Parameters (in): Pin >Port Pin ID number
                 : Direction > Port Pin Direction
* Return value: None
* Description: Sets the port pin direction       
******************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirection Direction)
{ 
		volatile GPIO_Type * Selected_GPIO_Port = NULL_PTR;/* point to the required Port Registers base address */	
		switch(PortConf[Pin].port_num)
		{
				case  0: Selected_GPIO_Port = (volatile GPIO_Type *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
				break; 
				case  1: Selected_GPIO_Port = (volatile GPIO_Type *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
				break;
				case  2: Selected_GPIO_Port = (volatile GPIO_Type *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
				break;
				case  3: Selected_GPIO_Port = (volatile GPIO_Type *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
				break;
				case  4: Selected_GPIO_Port = (volatile GPIO_Type *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
				break;
				case  5: Selected_GPIO_Port = (volatile GPIO_Type *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
				break;
		}    											
		if(Direction == PORT_PIN_IN)
		{
			CLEAR_BIT(Selected_GPIO_Port->DIR , PortConf[Pin].pin_num);
		}
		else if(Direction == PORT_PIN_OUT)
		{
			SET_BIT(Selected_GPIO_Port->DIR , PortConf[Pin].pin_num); 
		}
}
/**********************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Service ID[hex]:0x04
* Reentrancy: reentrant
* Parameters (in): Pin > Port Pin ID number
                 : Mode > New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
*******************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{   
		volatile GPIO_Type * Selected_GPIO_Port = NULL_PTR;/* point to the required Port Registers base address */	
		switch(PortConf[Pin].port_num)
		{
				case  0: Selected_GPIO_Port = (volatile GPIO_Type *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
				break; 
				case  1: Selected_GPIO_Port = (volatile GPIO_Type *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
				break;
				case  2: Selected_GPIO_Port = (volatile GPIO_Type *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
				break;
				case  3: Selected_GPIO_Port = (volatile GPIO_Type *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
				break;
				case  4: Selected_GPIO_Port = (volatile GPIO_Type *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
				break;
				case  5: Selected_GPIO_Port = (volatile GPIO_Type *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
				break;
		}         
		
		if(Mode == PORT_PIN_MODE_UART)
		{ 
			CLEAR_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);               /* ENable Alternative function for this pin*/
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);      /*Enable Digital*/ 
			if(Pin==20||Pin==21) /*PC4 ,PC5*/
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000002 << (PortConf[Pin].pin_num * 4));
			}
			else
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000001 << (PortConf[Pin].pin_num * 4));
			}			 
		}
    /**********************************************************************************************/    
		else if(Mode==PORT_PIN_MODE_DIO)
		{
			CLEAR_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
			CLEAR_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
			Selected_GPIO_Port->PCTL &= ~(uint32)(0x0000000F << (PortConf[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */ 
		}
    /**********************************************************************************************/ 
		else if(Mode==PORT_PIN_MODE_ADC)
		{  
			/*Should i enable RCGCADC and PLL ??*/
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);  /* ENable Alternative function for this pin*/
			CLEAR_BIT(Selected_GPIO_Port->DIR , PortConf[Pin].pin_num);  /*SEt as an input pin*/
			CLEAR_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);  /*Disable Digital mode */      
			SET_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin].pin_num);  /*Enable analog functionality on this pin */
		}
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_CAN)
		{    
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);               /* ENable Alternative function for this pin*/
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
			if(Pin==38 ||Pin==41)/*PF0,PF3*/
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000003 << (PortConf[Pin].pin_num * 4));
			}
			else
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000008 << (PortConf[Pin].pin_num * 4));         
			}
			/*Tx(output) pin or Rx(input)*/
		}
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_SSI)
		{    
			/*RCGCSSI register???*/
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num); /*set as Digital*/
			SET_BIT(Selected_GPIO_Port->DIR , PortConf[Pin].pin_num);           /*PULLUP */
			if(Pin==24 ||Pin==25 ||Pin==26 ||Pin==27)/*PD0,PD1,PD2,PD3*/
			{ 
				Selected_GPIO_Port->PCTL |= (0x00000001 << (PortConf[Pin].pin_num * 4));  
			}
			else
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000002 << (PortConf[Pin].pin_num * 4)); 
			}
		}
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_I2C)
		{
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
			SET_BIT(Selected_GPIO_Port->ODR , PortConf[Pin].pin_num);  /*OPen drain select*/
			Selected_GPIO_Port->PCTL |= (uint32)(0x00000003 << (PortConf[Pin].pin_num * 4));
		}
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_PWM)
		{  
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);
			if(Pin==12 ||Pin==13 ||Pin==14 ||Pin==15||Pin==20 ||Pin==21 ||Pin==24||Pin==25|Pin==36 ||Pin==37)/*PB4--PB7 , PC4,5  ,PD0,1 ,PE4,5*/
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000004 << (PortConf[Pin].pin_num * 4));
				SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
			}
			else
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000005<< (PortConf[Pin].pin_num * 4));
				SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
			}
		}
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_USB)
		{
			Selected_GPIO_Port->PCTL |= (uint32)(0x00000008<< (PortConf[Pin].pin_num * 4));
		}
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_QEI) 
		{   
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);
			Selected_GPIO_Port->PCTL |= (uint32)(0x00000006<< (PortConf[Pin].pin_num * 4));
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
		}
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_GPT) 
		{   
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);               /* ENable Alternative function for this pin*/
			Selected_GPIO_Port->PCTL |= (uint32)(0x00000007<< (PortConf[Pin].pin_num * 4));
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
		} 
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_NMI) 
		{    
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);
			Selected_GPIO_Port->PCTL |= (uint32)(0x00000008<< (PortConf[Pin].pin_num * 4));
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
		}  
		/**********************************************************************************************/
		else if(Mode==PORT_PIN_MODE_ANALOG_COMP) 
		{    
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);
			if(Pin==20 ||Pin==21 ||Pin==22 ||Pin==23 )  /*PC4,5,6,7 analog pins  C1-,C1+,C0+,C0-*/
			{ 
				SET_BIT(Selected_GPIO_Port->AMSEL , PortConf[Pin].pin_num);   /*Enable analog functionality on this pin */
				CLEAR_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);  /*Disable digital mode*/
			} 
			else
			{
				Selected_GPIO_Port->PCTL |= (uint32)(0x00000009 << (PortConf[Pin].pin_num * 4));
				SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
			}  
		}
		/**********************************************************************************************/
		if(Mode==PORT_PIN_MODE_CORE) 
		{    
			SET_BIT(Selected_GPIO_Port->AFSEL , PortConf[Pin].pin_num);
			Selected_GPIO_Port->PCTL |= (uint32)(0x0000000E << (PortConf[Pin].pin_num * 4));
			SET_BIT(Selected_GPIO_Port->DEN , PortConf[Pin].pin_num);
		}          
}
/*******************************************************************************************
* Service Name: Port_RefreshPortDirection
* Parameters (in): None
* Return value: None
* Description: Refreshes port direction.
*******************************************************************************************/
void Port_RefreshPortDirection( void )
{	
  volatile GPIO_Type * Selected_GPIO_Port = NULL_PTR;/* point to the required Port Registers base address */	
	uint8 Pin_Index;              /* index to configure each pin (43)*/    
	for (Pin_Index = 0; Pin_Index < PORT_NUMBER_OF_PORT_PINS ; Pin_Index++) 
	{
	 if(PortConf[Pin_Index].Pin_direction_Change == STD_OFF)     /*Check that if POrt pin is UNchangable in RunTime*/ 
	 {
					
			switch(PortConf[Pin_Index].port_num)
			{
					case  0: Selected_GPIO_Port = (volatile GPIO_Type *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
					break; 
					case  1: Selected_GPIO_Port = (volatile GPIO_Type *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
					break;
					case  2: Selected_GPIO_Port = (volatile GPIO_Type *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
					break;
					case  3: Selected_GPIO_Port = (volatile GPIO_Type *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
					break;
					case  4: Selected_GPIO_Port = (volatile GPIO_Type *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
					break;
					case  5: Selected_GPIO_Port = (volatile GPIO_Type *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
					break;
			}         
			if(BIT_IS_SET(Selected_GPIO_Port->DIR , PortConf[Pin_Index].pin_num))/*Read Pin Direction */
			{
				SET_BIT(Selected_GPIO_Port->DIR , PortConf[Pin_Index].pin_num); 
			}
			else if(BIT_IS_CLEAR(Selected_GPIO_Port->DIR , PortConf[Pin_Index].pin_num))
			{
				CLEAR_BIT(Selected_GPIO_Port->DIR , PortConf[Pin_Index].pin_num); 
			}
			else 
			{
				/* No Action Required */
			}
		}
		else if(PortConf[Pin_Index].Pin_direction_Change == STD_ON)/*If the Port pin is changable exclude it*/
		{   
		continue;
		}
	}  //End of for loop
} 
