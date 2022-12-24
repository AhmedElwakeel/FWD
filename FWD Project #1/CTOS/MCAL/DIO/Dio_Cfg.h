#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "Dio.h"


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const volatile Dio_ConfigType Dio_Configuration;
/*******************************************************************************/

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_LED1_CHANNEL_ID_INDEX        (uint8)0x00
#define DioConf_SW1_CHANNEL_ID_INDEX         (uint8)0x01 
#define DioConf_SW2_CHANNEL_ID_INDEX         (uint8)0x02 

/* DIO Configured Port ID's  */
#define DioConf_LED1_PORT_NUM                (uint8)0x05 /* PORTF */
#define DioConf_SW1_PORT_NUM                 (uint8)0x05 /* PORTF */
#define DioConf_SW2_PORT_NUM                 (uint8)0x05 /* PORTF */

/* DIO Configured Channel ID's */
#define DioConf_LED1_CHANNEL_NUM             (uint8)0x01 /* PORTF.1 */
#define DioConf_SW1_CHANNEL_NUM              (uint8)0x04 /* PORTF.4 */
#define DioConf_SW2_CHANNEL_NUM              (uint8)0x00 /* PORTF.0 */

#endif /* DIO_CFG_H */
