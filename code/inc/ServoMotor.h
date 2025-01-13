#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

// 舵机初始化
#define FL_CHANNEL ATOM0_CH3_P14_2	   // 前左舵机pwm引脚
#define FR_CHANNEL ATOM0_CH4_P20_3	   // 前右舵机pwm引脚
#define BL_CHANNEL ATOM0_CH1_P33_9	   // 后左舵机pwm引脚
#define BR_CHANNEL ATOM0_CH2_P33_11	   // 后右舵机pwm引脚

#define ANGLEMAX  180						   // 舵机范围，最大角度
#define ANGLE2PWM (PWM_DUTY_MAX / ANGLEMAX)	   // 单位转化。角度°，转化为PWM

// 关节序号
typedef enum { Fl, Fr, Bl, Br } JointNum;

// 舵机结构体
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM 引脚
	JointNum		 num;

	float angleSet;	   // 舵机的实际转角 舵机均采用角度制 °
	float angleAdj;	   // 解算的调整值
	float angleLeg;	   // 在Leg上的换算角度，即Leg.h的∠1与∠4
	u8	  sign;		   // 正负号，结算用

	int32_t PWMSet;
} ServoType;

extern ServoType Servo[4];

void ServoInit(void);
void ServoFunc(void);

#endif
