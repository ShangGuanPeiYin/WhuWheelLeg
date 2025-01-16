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
	Servo[0].num	  = Fl;
	Servo[0].angleAdj = -270;
	Servo[0].sign	  = -1;

	Servo[1].num	  = Fr;
	Servo[1].angleAdj = -90;
	Servo[1].sign	  = +1;

	Servo[2].num	  = Bl;
	Servo[2].angleAdj = -90;
	Servo[2].sign	  = -1;

	Servo[3].num	  = Br;
	Servo[3].angleAdj = +90;
	Servo[3].sign	  = +1;

	for (size_t i = 0; i < 4; i++) {
		Servo[i].angleSet = 0;
		Servo[i].PWMSet	  = 0;
	}

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
