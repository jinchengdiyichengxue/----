#ifndef __MPU6050_H
#define __MPU6050_H

//存储IMU测量的原始数据  
typedef struct {        
    int16_t AX;			
    int16_t AY;
    int16_t AZ;
    int16_t GX;
    int16_t GY;
    int16_t GZ;
}Init_Data;

//存储实际物理量  
typedef struct {        
    float AX;			
    float AY;
    float AZ;
    float GX;
    float GY;
    float GZ;
}Physical_Data;

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_Init(void);
void MPU6050_GetData(Init_Data *Init_Data);    //获取6轴姿态存放在Init_Data结构体中

float Trans_Fused_data(void);
#endif
