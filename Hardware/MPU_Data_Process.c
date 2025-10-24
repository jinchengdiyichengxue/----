#include "stm32f10x.h"  // Device header
#include "MPU6050.h"
#include <math.h>

#define Sensitivity_A 8192.0   //加速度计灵敏度 
#define Sensitivity_G 32.8	 //陀螺仪计灵敏度

Init_Data  			init_data ={0};            			 //MPU6050的原始数据
Physical_Data 		physical_data ={0};					 //转换为实际物理量

/*
* 调用此函数，1.原始数据读进去放在Init_Data
*          2.原始数据转化为实际的物理量，放在Physical_Data结构体中
*          3.融合数据，放在Pass_for_PID
*/
float Trans_Fused_data(void)
{
	MPU6050_GetData(&init_data);
	
	// 对于量程 ±4g，灵敏度 8192 LSB/g
	physical_data.AX = init_data.AX / Sensitivity_A;
	physical_data.AY = init_data.AY / Sensitivity_A; 
	physical_data.AZ = init_data.AZ / Sensitivity_A;
	
	// 对于量程 ±1000 °/s，灵敏度 32.8 LSB/(°/s)
	physical_data.GX = init_data.GX / Sensitivity_G;
	physical_data.GY = init_data.GY / Sensitivity_G;
	physical_data.GZ = init_data.GZ / Sensitivity_G;
	
	
	// 使用atan2函数，更加稳定可靠，不融合陀螺仪数据
	float pitch_acc  = atan2(physical_data.AX, sqrt(physical_data.AY * physical_data.AY + physical_data.AZ * physical_data.AZ)) * 57.3; 
	
	//使用互补滤波算法进行数据融合
	
	// 初始化变量
	float angle = 0.0; 			 // 初始角度
	float alpha = 0.98;     	// 滤波系数（更信任陀螺仪）
	float dt = 0.01;

    // 1. 陀螺仪积分角度（短期响应）历史积分
    angle += physical_data.GY * dt;

    // 2. 与加速度计角度融合（长期稳定）
    float Pitch_fused = alpha * angle + (1 - alpha) * Pitch_fused;
	
	return Pitch_fused;
}

