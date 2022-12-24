#ifndef PORT_H
#define PORT_H

#include "Common_Macros.h"
#include "Std_Types.h"
#include "Port_Cfg.h"


typedef uint8 Port_PinType;
typedef uint8 Port_PinModeType;                  // 8 Modes 
   
typedef enum
{
  PORT_PIN_IN,
	PORT_PIN_OUT
}Port_PinDirection;

typedef enum
{
  OFF,
	PULL_UP,
	PULL_DOWN
}Port_InternalResistor;

typedef struct 
{
    uint8 port_num; 
    uint8 pin_num; 
    Port_PinDirection direction;
    uint8 Pin_direction_Change;    /*pin direction changeable during runtime*/
    Port_InternalResistor resistor;
    uint8 initial_value;   
    uint8 pin_mode; /*Pin mode*/
		uint8 Selected;
}Port_ConfigPins;

typedef struct
{//Structure For All PINS To Be Configured.....
	Port_ConfigPins Pins[PORT_NUMBER_OF_PORT_PINS ];      //43 Structure 
}Port_ConfigType;

void Port_Init(volatile Port_ConfigType *ConfigPtr );
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirection Direction );
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
void Port_RefreshPortDirection( void );
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
