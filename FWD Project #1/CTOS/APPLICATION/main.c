#include "Button.h"
#include "Led.h"
#include "Gpt.h"
#include "interrupt.h"


#define BASE_TIME 16000UL/* Timer counting time in 1 ms */
/* Global variable to indicate the the timer has a new tick */
static uint8 g_New_Time_Tick_Flag = 0;
void Init(void);
void NewTimerTick(void);
void LED_PWM_CTRL(uint16 _OnTime);

const static volatile uint16 TotalTime = 2000;
static volatile uint16 OnTime    = 500;
static volatile uint16 OffTime   = 1500;
int main(void)
{		
	Init();
	Dio_Init(&Dio_Configuration);
	BUTTON_Init();	/* Initialize Button Driver */	
	LED_Init();			/* Initialize LED Driver */		
	LED_PWM_CTRL(500);//In mmsec
	while(1)
	{
		if(BUTTON_getState(DioConf_SW1_CHANNEL_ID_INDEX) == BUTTON_PRESSED)
		{
			for(int i=0;i<100000;i++){}//debounce
			if(OnTime < TotalTime)
			{
				OnTime  += 50;
				OffTime -=50;
				LED_PWM_CTRL(OnTime);
			}				
		}
		else if(BUTTON_getState(DioConf_SW2_CHANNEL_ID_INDEX) == BUTTON_PRESSED)
		{
			for(int i=0;i<100000;i++){}//debounce
			if(OnTime > 0)
			{				
				OnTime  -= 50;
				OffTime +=50;
				LED_PWM_CTRL(OnTime);
			}
		}
		
	}
}
/*********************************************************************************************/
void NewTimerTick(void)
{
	static int Count = 0;
	
    /* Increment the time by OS_BASE_TIME */
    //g_Time_Tick_Count   += BASE_TIME;

    /* Set the flag to 1 to indicate that there is a new timer tick */
    g_New_Time_Tick_Flag = 1;
		Count++;
		if(Count >= TotalTime)
		{
			Count = 0;
			LED_setOn();
		}		
		else if(Count >= OnTime)
		{
			LED_setOff();
		}
		else
		{
			//Do Nothing.....
		}
}

/*********************************************************************************************/
void Init(void)
{
    /* 
     * Set the Call Back function to call Os_NewTimerTick
     * this function will be called every SysTick Interrupt (20ms)
     */
    SysTick_SetCallBack(NewTimerTick);
    /* Start SysTickTimer to generate interrupt every 20ms */
    SysTick_Init(BASE_TIME);
	  /* Global Interrupts Enable */
    IntMasterEnable();
}
void LED_PWM_CTRL(uint16 _OnTime)
{
	OnTime = _OnTime;
}
