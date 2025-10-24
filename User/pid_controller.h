#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// 位置式PID控制器结构体，封装所有相关参数和状态
typedef struct {
    // PID参数
    float kp;          // 比例系数
    float ki;          // 积分系数
    float kd;          // 微分系数
    
    // 误差相关变量
    float target;      // 目标值
    float current;     // 当前值
    float error0;      // 当前误差 (current_error)
    float error1;      // 上一次误差 (last_error)
    float error_sum;   // 误差积分和
    
    // 输出限幅
    float output_min;  // 输出最小值限制
    float output_max;  // 输出最大值限制
    
    // 积分限幅
    float integral_min; // 积分最小值
    float integral_max; // 积分最大值
} PID_HandleTypeDef;

// 函数声明
void PID_Init(PID_HandleTypeDef *pid, float kp, float ki, float kd);
void PID_SetTarget(PID_HandleTypeDef *pid, float target);
void PID_SetOutputLimits(PID_HandleTypeDef *pid, float min, float max);
void PID_SetIntegralLimits(PID_HandleTypeDef *pid, float min, float max);
float PID_Compute(PID_HandleTypeDef *pid, float current_value);
void PID_Reset(PID_HandleTypeDef *pid);

#endif // PID_CONTROLLER_H
