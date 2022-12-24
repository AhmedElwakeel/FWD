#include "Dio_Cfg.h"
/* Post Build structure used with Dio_Init API */
const volatile Dio_ConfigType Dio_Configuration =
{
	{
		{DioConf_LED1_PORT_NUM,DioConf_LED1_CHANNEL_NUM},
		{DioConf_SW1_PORT_NUM ,DioConf_SW1_CHANNEL_NUM},	
		{DioConf_SW2_PORT_NUM ,DioConf_SW2_CHANNEL_NUM}
	}
};
