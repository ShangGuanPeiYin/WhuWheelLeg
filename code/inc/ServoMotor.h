#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

#define ANGLEMAX  180						   // 舵机范围，最大角度
#define ANGLE2PWM (PWM_DUTY_MAX / ANGLEMAX)	   // 单位转化。角度°，转化为PWM

// 关节序号
typedef enum { Fl, Fr, Bl, Br } JointNum;

// 舵机结构体
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM 引脚
	JointNum		 joint;

	float cntTime;	  // 单位ms
	float reachTime;

	float angleSet;	   // 设置位置 = 中值+移动值
	float angleMid;	   // 中值。相当于给了一个零点。
	float angleMov;	   // 移动值

	int32_t PWMSet;
} ServoType;

void ServoInit(void);
void ServoSetPosition(int id);
void ServoMov(JointNum num, float reachTime, float pos);
void ServoFunc(void);

#endif
