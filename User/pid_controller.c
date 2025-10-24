#include "pid_controller.h"
#include <math.h>
#include <stdio.h>


/**
 * @brief 初始化PID控制器
 * @param pid: PID结构体指针
 * @param kp: 比例系数
 * @param ki: 积分系数
 * @param kd: 微分系数
 */
void PID_Init(PID_HandleTypeDef *pid, float kp, float ki, float kd) {
    if (pid == NULL) return;
    
    // 初始化参数
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    
    // 初始化状态变量
    pid->target = 0.0f;
    pid->current = 0.0f;
    pid->error0 = 0.0f;
    pid->error1 = 0.0f;
    pid->error_sum = 0.0f;
    
//    // 默认输出限制
//    pid->output_min = -__FLT_MAX__;
//    pid->output_max = __FLT_MAX__;
//    
//    // 默认积分限制
//    pid->integral_min = -__FLT_MAX__;
//    pid->integral_max = __FLT_MAX__;
}

/**
 * @brief 设置PID目标值
 * @param pid: PID结构体指针
 * @param target: 目标值
 */
void PID_SetTarget(PID_HandleTypeDef *pid, float target) {
    if (pid == NULL) return;
    pid->target = target;
}

/**
 * @brief 设置输出值限制范围
 * @param pid: PID结构体指针
 * @param min: 最小值
 * @param max: 最大值
 */
void PID_SetOutputLimits(PID_HandleTypeDef *pid, float min, float max) {
    if (pid == NULL || min >= max) return;
    pid->output_min = min;
    pid->output_max = max;
}

/**
 * @brief 设置积分值限制范围(防止积分饱和)
 * @param pid: PID结构体指针
 * @param min: 积分最小值
 * @param max: 积分最大值
 */
void PID_SetIntegralLimits(PID_HandleTypeDef *pid, float min, float max) {
    if (pid == NULL || min >= max) return;
    pid->integral_min = min;
    pid->integral_max = max;
}

/**
 * @brief 计算PID输出
 * @param pid: PID结构体指针
 * @param current_value: 当前测量值
 * @return PID计算后的输出值
 */
float PID_Compute(PID_HandleTypeDef *pid, float current_value) {
    if (pid == NULL) return 0.0f;
    
    // 更新当前值
    pid->current = current_value;
    
    // 保存上一次误差，计算当前误差 习惯用error0表示当前误差，error1表示上一次误差
    pid->error1 = pid->error0;
    pid->error0 = pid->target - current_value;
    
    // 计算比例项
    float p_term = pid->kp * pid->error0;
    
    // 计算当前误差的积分值，然后限幅
    pid->error_sum += pid->error0;
    // 积分限幅
    if (pid->error_sum > pid->integral_max) {
        pid->error_sum = pid->integral_max;
    } else if (pid->error_sum < pid->integral_min) {
        pid->error_sum = pid->integral_min;
    }
    float i_term = pid->ki * pid->error_sum;
    
    // 计算微分项
    float d_term = pid->kd * (pid->error0 - pid->error1);
    
    // 计算总输出
    float output = p_term + i_term + d_term;
    
    // 输出限幅
    if (output > pid->output_max) {
        output = pid->output_max;
    } else if (output < pid->output_min) {
        output = pid->output_min;
    }
    
    return output;
}

/**
 * @brief 重置PID控制器状态
 * @param pid: PID结构体指针
 */
void PID_Reset(PID_HandleTypeDef *pid) {
    if (pid == NULL) return;
    
    pid->error0 = 0.0f;
    pid->error1 = 0.0f;
    pid->error_sum = 0.0f;
    pid->current = 0.0f;
}
