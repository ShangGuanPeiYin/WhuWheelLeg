#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief 舵机初始化
/// @param
void ServoInit(void)
{
	// PWM引脚配置
	Servo[0].pin	   = FL_CHANNEL;
	Servo[1].pin	   = FR_CHANNEL;
	Servo[2].pin	   = BL_CHANNEL;
	Servo[3].pin	   = BR_CHANNEL;

	// 初始化舵机数据
	Servo[0].joint	   = Fl;
	Servo[0].cntTime   = 0.f;
	Servo[0].reachTime = 0.f;
	Servo[0].angleSet  = 0;
	Servo[0].angleMid  = 0;
	Servo[0].angleMov  = 0;
	Servo[0].PWMSet	   = 0;

	Servo[1].joint	   = Fr;
	Servo[1].cntTime   = 0.f;
	Servo[1].reachTime = 0.f;
	Servo[1].angleSet  = 0;
	Servo[1].angleMid  = 0;
	Servo[1].angleMov  = 0;
	Servo[1].PWMSet	   = 0;

	Servo[2].joint	   = Bl;
	Servo[2].cntTime   = 0.f;
	Servo[2].reachTime = 0.f;
	Servo[2].angleSet  = 0;
	Servo[2].angleMid  = 0;
	Servo[2].angleMov  = 0;
	Servo[2].PWMSet	   = 0;

	Servo[3].joint	   = Br;
	Servo[3].cntTime   = 0.f;
	Servo[3].reachTime = 0.f;
	Servo[3].angleSet  = 0;
	Servo[3].angleMid  = 0;
	Servo[3].angleMov  = 0;
	Servo[3].PWMSet	   = 0;

	// 引脚初始化 PWM频率200Hz

	for (size_t i = 0; i < 4; i++) pwm_init(Servo[i].pin, 200, Servo[i].angleMid);
}

/// @brief 单个舵机设置角度
/// @param id 0-3
void ServoSetPosition(int id)
{
	Servo[id].angleSet = Servo[id].angleMov + Servo[id].angleMid;

	// 判断是否到位
	if (Servo[id].cntTime <= Servo[id].reachTime) {
		Servo[id].PWMSet = (Servo[id].cntTime / Servo[id].reachTime) * Servo[id].angleSet * ANGLE2PWM;	  // 线性插值
		Servo[id].cntTime
			+= 5.f;	   // 舵机频率200Hz																		// 中断频率
	} else
		Servo[id].PWMSet = Servo[id].angleSet * ANGLE2PWM;

	PEAK(Servo[id].PWMSet, (int32_t) PWM_DUTY_MAX);	   // 限幅保护
	pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	   // 设置PWM占空比
}

/// @brief 用户层。控制舵机转动。线性插值
/// @param num 哪一个舵机
/// @param reachTime 到达时间。ms
/// @param pos 移动角度
void ServoMov(JointNum num, float reachTime, float pos)
{
	u8 id				= (u8) num;
	Servo[id].cntTime	= 0.f;
	Servo[id].reachTime = reachTime;
	Servo[id].angleMov	= pos;
}

/// @brief 定时器Func函数
/// @param
void ServoFunc(void)
{
	for (size_t id = 0; id < 4; id++) { ServoSetPosition(id); }
};
