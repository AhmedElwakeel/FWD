#ifndef BUTTON_H
#define BUTTON_H

#include "interrupt.h"
#include "Std_Types.h"
#include "Dio.h"
#include "Port.h"
#include "Dio_Cfg.h"

#define BUTTON_PRESSED  STD_LOW
#define BUTTON_RELEASED STD_HIGH

#define BUTTON_PORT DioConf_SW1_PORT_NUM
#define BUTTON_PIN_NUM DioConf_SW1_CHANNEL_NUM

#define BUTTON2_PORT DioConf_SW2_PORT_NUM
#define BUTTON2_PIN_NUM DioConf_SW2_CHANNEL_NUM

void BUTTON_Init(void);
uint8 BUTTON_getState(Dio_ChannelType SW_ID_Index);

#endif /* BUTTON_H */
