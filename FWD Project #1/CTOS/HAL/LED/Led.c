#include "Led.h"

/* LED Configurations Structure */
static volatile Port_ConfigType  Green_LED_Config;


/*********************************************************************************************/
void LED_Init(void)
{	
	Green_LED_Config.Pins[PORT_F_PIN_1].direction = PORT_PIN_OUT;
	Green_LED_Config.Pins[PORT_F_PIN_1].resistor = OFF;
	Green_LED_Config.Pins[PORT_F_PIN_1].pin_mode = PORT_PIN_MODE_DIO;
	Green_LED_Config.Pins[PORT_F_PIN_1].port_num = LED_PORT;
	Green_LED_Config.Pins[PORT_F_PIN_1].pin_num  = LED_PIN_NUM;
	Green_LED_Config.Pins[PORT_F_PIN_1].Selected  = 1;
	Port_Init(&Green_LED_Config);	
}
/*********************************************************************************************/
void LED_setOn(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_ON);  /* LED ON */
}

/*********************************************************************************************/
void LED_setOff(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF); /* LED OFF */
}

/*********************************************************************************************/
void LED_refreshOutput(void)
{
    Dio_LevelType state = Dio_ReadChannel(DioConf_LED1_CHANNEL_ID_INDEX);
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,state); /* re-write the same value */
}

/*********************************************************************************************/
void LED_toggle(void)
{
   Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);
}

/*********************************************************************************************/
