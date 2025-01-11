#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

// 舵机初始化
#define FL_CHANNEL ATOM0_CH1_P33_9	   // 前左舵机pwm引脚
#define FR_CHANNEL ATOM0_CH2_P33_11	   // 前右舵机pwm引脚
#define BL_CHANNEL ATOM0_CH4_P20_3	   // 后左舵机pwm引脚
#define BR_CHANNEL ATOM0_CH3_P14_2	   // 后右舵机pwm引脚

#define ANGLEMAX  180						   // 舵机范围，最大角度
#define ANGLE2PWM (PWM_DUTY_MAX / ANGLEMAX)	   // 单位转化。角度°，转化为PWM

// 关节序号
typedef enum { Fl, Fr, Bl, Br } JointNum;

// 舵机结构体
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM 引脚
	JointNum		 joint;

	float angleSet;	   // 设置位置 = 中值+移动值
	float angleMid;	   // 中值。相当于给了一个零点。
	float angleMov;	   // 移动值

	int32_t PWMSet;
} ServoType;

void ServoInit(void);
void ServoSetPosition(int id);
void ServoMov(JointNum num, float pos);
void ServoFunc(void);

#endif
