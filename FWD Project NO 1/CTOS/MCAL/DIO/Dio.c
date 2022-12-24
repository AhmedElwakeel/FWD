#include "Dio.h"


static volatile Dio_ConfigChannel * Dio_PortChannels = NULL_PTR; //ptr to a structure (port,channel)

void Dio_Init(const volatile Dio_ConfigType * ConfigPtr)
{
		Dio_PortChannels = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */	
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)     
{
	volatile GPIO_Type * Selected_GPIO_Port = NULL_PTR; 	/* point to the required Port Registers base address */
	switch(Dio_PortChannels[ChannelId].Port_Num)
	{
			case 0:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
								 break;
			case 1:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
								 break;
			case 2:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
								 break;
			case 3:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
								 break;
			case 4:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
								 break;
			case 5:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
								 break;
	}
	if(Level == STD_HIGH)
	{
		SET_BIT(Selected_GPIO_Port->DATA,Dio_PortChannels[ChannelId].Ch_Num);
	}
	else if(Level == STD_LOW)
	{
		CLEAR_BIT(Selected_GPIO_Port->DATA,Dio_PortChannels[ChannelId].Ch_Num);
	}
}
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType output = STD_LOW;
	volatile GPIO_Type * Selected_GPIO_Port = NULL_PTR; 	/* point to the required Port Registers base address */
	switch(Dio_PortChannels[ChannelId].Port_Num)
	{
			case 0:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
								 break;
			case 1:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
								 break;
			case 2:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
								 break;
			case 3:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
								 break;
			case 4:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
								 break;
			case 5:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
								 break;
	}
	/* Read the required channel */
	if(BIT_IS_SET(Selected_GPIO_Port->DATA,Dio_PortChannels[ChannelId].Ch_Num))
	{
		output = STD_HIGH;
	}
	else
	{
		output = STD_LOW;
	}
	return output;
}
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	volatile GPIO_Type * Selected_GPIO_Port = NULL_PTR; 	/* point to the required Port Registers base address */
	Dio_LevelType output = STD_LOW;
	/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
	switch(Dio_PortChannels[ChannelId].Port_Num)
	{
			case 0:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
								 break;
			case 1:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
								 break;
			case 2:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
								 break;
			case 3:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
								 break;
			case 4:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
								 break;
			case 5:    Selected_GPIO_Port = (volatile GPIO_Type *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
								 break;
	}
	/* Read the required channel and write the required level */
	if(BIT_IS_SET(Selected_GPIO_Port->DATA,Dio_PortChannels[ChannelId].Ch_Num))
	{
		CLEAR_BIT(Selected_GPIO_Port->DATA,Dio_PortChannels[ChannelId].Ch_Num);
		output = STD_LOW;
	}
	else
	{
		SET_BIT(Selected_GPIO_Port->DATA,Dio_PortChannels[ChannelId].Ch_Num);
		output = STD_HIGH;
	}
	return output;
}
