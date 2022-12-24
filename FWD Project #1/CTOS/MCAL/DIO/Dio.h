#ifndef DIO_H
#define DIO_H

#include "Common_Macros.h"
#include "tm4c123gh6pm_registers.h"
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef uint8 Dio_ChannelType;/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8 Dio_PortType;/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_LevelType;/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_PortLevelType;/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef struct/* Structure for Dio_ChannelGroup */
{
  uint8 mask;/* Mask which defines the positions of the channel group */
  uint8 offset;  /* Position of the group from LSB */
  Dio_PortType PortIndex;  /* This shall be the port ID which the Channel group is defined. */
} Dio_ChannelGroupType;
typedef struct
{
	Dio_PortType Port_Num;	/* Member contains the ID of the Port that this channel belongs to */
	Dio_ChannelType Ch_Num;	/* Member contains the ID of the Channel*/
}Dio_ConfigChannel;
#define DIO_CONFIGURED_CHANNELS              3   /*LED,SW1,SW2*//* Number of the configured Dio Channels */
typedef struct/* Data Structure required for initializing the Dio Driver */
{
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNELS];
} Dio_ConfigType;
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);/* Function for DIO read Channel API */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);/* Function for DIO write Channel API */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);/* Function for DIO read Port API */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);/* Function for DIO write Port API */
void Dio_Init(const volatile Dio_ConfigType * ConfigPtr);/* Function for DIO Initialization API */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

#endif /* DIO_H */
