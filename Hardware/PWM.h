#ifndef __PWM_H
#define __PWM_H

void TIM1_PWM_Init(u16 arr, u16 psc);
void PWM_SetCompare1(int8_t CCR);
void PWM_SetCompare3(int8_t CCR);

#endif
