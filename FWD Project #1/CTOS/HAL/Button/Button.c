#include "Button.h"

/* Button Configurations Structure */
static Port_ConfigType Button_Config;

/* Global variable to hold the button state */
static uint8 button_state = BUTTON_RELEASED;
void BUTTON_Init(void)
{
	Button_Config.Pins[PORT_F_PIN_4].direction 	= PORT_PIN_IN;
	Button_Config.Pins[PORT_F_PIN_4].resistor 	= PULL_UP;
	Button_Config.Pins[PORT_F_PIN_4].pin_mode 	= PORT_PIN_MODE_DIO;
	Button_Config.Pins[PORT_F_PIN_4].port_num 	= BUTTON_PORT;
	Button_Config.Pins[PORT_F_PIN_4].pin_num  	= BUTTON_PIN_NUM;
	Button_Config.Pins[PORT_F_PIN_4].Selected  	= 1;
	
	Button_Config.Pins[PORT_F_PIN_0].direction 	= PORT_PIN_IN;
	Button_Config.Pins[PORT_F_PIN_0].resistor 	= PULL_UP;
	Button_Config.Pins[PORT_F_PIN_0].pin_mode 	= PORT_PIN_MODE_DIO;
	Button_Config.Pins[PORT_F_PIN_0].port_num 	= BUTTON2_PORT;
	Button_Config.Pins[PORT_F_PIN_0].pin_num  	= BUTTON2_PIN_NUM;
	Button_Config.Pins[PORT_F_PIN_0].Selected  	= 1;
	
	Port_Init(&Button_Config);
}
/*******************************************************************************************************************/
uint8 BUTTON_getState(Dio_ChannelType SW_ID_Index)
{
	button_state = Dio_ReadChannel(SW_ID_Index);
  return button_state;
}

/*******************************************************************************************************************/
