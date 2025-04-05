#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief 舵机初始化
/// @param
void ServoInit(void)
{
	for (size_t i = 0; i < 4; i++) { memset(&Servo[i], 0, sizeof(ServoType)); }

	// PWM引脚配置
	Servo[0].pin		= FL_CHANNEL;
	Servo[1].pin		= FR_CHANNEL;
	Servo[2].pin		= BL_CHANNEL;
	Servo[3].pin		= BR_CHANNEL;

	// 初始化舵机数据
	Servo[0].num		= Fl;
	Servo[0].angleAdj	= -270;
	Servo[0].sign		= -1;
	Servo[0].deltaAngle = +7;	 // 需要手动测量出安装误差

	Servo[1].num		= Fr;
	Servo[1].angleAdj	= -90;
	Servo[1].sign		= +1;
	Servo[1].deltaAngle = -1;

	Servo[2].num		= Bl;
	Servo[2].angleAdj	= -90;
	Servo[2].sign		= -1;
	Servo[2].deltaAngle = -2;

	Servo[3].num		= Br;
	Servo[3].angleAdj	= +90;
	Servo[3].sign		= +1;
	Servo[3].deltaAngle = -13;

	Servo[Fl].angleLeg	= 180.f;
	Servo[Fr].angleLeg	= 180.f;
	Servo[Bl].angleLeg	= 0.f;
	Servo[Br].angleLeg	= 0.f;

	// 引脚初始化 PWM频率200Hz
	for (size_t i = 0; i < 4; i++) {
		Servo[i].angleSet = 90.f;
		pwm_init(Servo[i].pin, 200, 4 * 750);
	}
	ServoFunc();
}

/// @brief 定时器Func函数
/// @param 换算关系为：
///      	PWMSet = (f/50)*( 250 + (1000 * (AngleSet + deltaAngle) / 180));
void ServoFunc(void)
{
	for (size_t id = 0; id < 4; id++)	 // 循环执行
	{
		// 解算部分
		Servo[id].angleSet = (Servo[id].angleLeg + Servo[id].angleAdj) * Servo[id].sign;

		// 驱动电机
		Limit(Servo[id].angleSet, 0, 180);															  // 限幅保护
		Servo[id].PWMSet = 4 * (250 + (1000 * (Servo[id].angleSet + Servo[id].deltaAngle) / 180));	  // PWM为200Hz，为50的4倍

		pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	  // 设置PWM占空比
	}
};
