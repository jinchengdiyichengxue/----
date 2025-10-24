#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "MPU6050.h"
#include "Motor.h"
#include "Encoder.h"
#include "PWM.h"
#include "AD.h"
#include "OLED.h"
#include "Serial.h"
#include "pid_controller.h"

//定义每一个任务的计时变量
static unsigned char Count_Read;         //读取角度，和编码电机速度
static unsigned char Count_Angle;
static unsigned char Count_Speed;


                           				                                         
int main(void)
{
//    /*模块初始化*/    
    Timer_Init();
    MPU6050_Init();
    Encoder_Init();
    Motor_Init();
	Serial_Init();
	OLED_Init();
	AD_Init();
//	  OLED_Update();
    
    
    while (1)
    {
		//zhey zdhfg
	}

}
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != SET) return;
	Count_Read++;
	Count_Angle++;
	Count_Speed++;
	
	//速度环周期 : 角度环周期 : 传感器读取周期 ≈ 1 : 2 : 4
	if(Count_Read >= 5)
	{
		Count_Read = 0;
	}

	if(Count_Angle >= 10)
	{
		Count_Angle = 0;
		
		
	}
	if(Count_Speed >= 20)
	{
		Count_Speed = 0;
		
	}
		  
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
