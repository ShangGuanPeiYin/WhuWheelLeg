#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief 舵机初始化
/// @param
void ServoInit(void)
{
	// PWM引脚配置
	Servo[0].pin	  = FL_CHANNEL;
	Servo[1].pin	  = FR_CHANNEL;
	Servo[2].pin	  = BL_CHANNEL;
	Servo[3].pin	  = BR_CHANNEL;

	// 初始化舵机数据
	Servo[0].joint	  = Fl;
	Servo[0].angleSet = 0;
	Servo[0].angleAdj = 0;
	Servo[0].PWMSet	  = 0;
	Servo[0].sign	  = -1;

	Servo[1].joint	  = Fr;
	Servo[1].angleSet = 0;
	Servo[1].angleAdj = 0;
	Servo[1].PWMSet	  = 0;
	Servo[1].sign	  = -1;

	Servo[2].joint	  = Bl;
	Servo[2].angleSet = 0;
	Servo[2].angleAdj = 0;
	Servo[2].PWMSet	  = 0;
	Servo[2].sign	  = -1;

	Servo[3].joint	  = Br;
	Servo[3].angleSet = 0;
	Servo[3].angleAdj = 0;
	Servo[3].PWMSet	  = 0;
	Servo[3].sign	  = -1;

	// 引脚初始化 PWM频率250Hz

	for (size_t i = 0; i < 4; i++) pwm_init(Servo[i].pin, 250, Servo[i].angleAdj);
}

/// @brief 定时器Func函数
/// @param
void ServoFunc(void)
{
	for (size_t id = 0; id < 4; id++)	 // 循环执行
	{
		// 解算部分
		// Servo[id].angleSet = (Servo[id].angleLeg + Servo[id].angleAdj) * Servo[id].sign;

		// 驱动电机
		Servo[id].PWMSet = Servo[id].angleSet * ANGLE2PWM;
		Limit(Servo[id].PWMSet, 0, (int32_t) PWM_DUTY_MAX);	   // 限幅保护

		pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	  // 设置PWM占空比
	}
};

/* 线性差值，要移到上层
	// 判断是否到位
	if (Servo[id].cntTime <= Servo[id].reachTime) {
		Servo[id].PWMSet = (Servo[id].cntTime / Servo[id].reachTime) * Servo[id].angleSet * ANGLE2PWM;	  // 线性插值
		Servo[id].cntTime
			+= 5.f;	   // 舵机频率200Hz																		// 中断频率
	} else
		Servo[id].PWMSet = Servo[id].angleSet * ANGLE2PWM;

*/
