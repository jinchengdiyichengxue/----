#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"  

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
 
void TIM1_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitSturcture;
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);
    //初始化IO口
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    //设置 TIM ARR PSC
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数模式
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
 
    //TIM1_CH1  PWM1 模式
    TIM_OCInitSturcture.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitSturcture.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitSturcture.TIM_OCPolarity = TIM_OCPolarity_High;			//输出高电平有效
    TIM_OC1Init(TIM1, &TIM_OCInitSturcture);
 
    //TIM1_CH3  PWM1 模式
    TIM_OCInitSturcture.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitSturcture.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitSturcture.TIM_OCPolarity = TIM_OCPolarity_High;		 
    TIM_OC3Init(TIM1, &TIM_OCInitSturcture);
 
 
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);					//TIM1_CH1 使能预装载寄存器
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);					 //TIM1_CH3 使能预装载寄存器
 
 
    TIM_Cmd(TIM1, ENABLE);				//使能计数器
    TIM_CtrlPWMOutputs(TIM1, ENABLE);	//主输出使能
}

void PWM_SetCompare1(int8_t CCR){
	TIM_SetCompare1(TIM1, CCR);
}

void PWM_SetCompare3(int8_t CCR){
	TIM_SetCompare3(TIM1, CCR);
}
	

