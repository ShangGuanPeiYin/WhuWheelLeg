/*
 * Servo.c
 * Created on: 2024年10月11日
 * Author: 刘沐
 */
#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief 舵机初始化
/// @param
void ServoInit(void)
{
	for (size_t i = 0; i < 4; i++) { memset(&Servo[i], 0, sizeof(ServoType)); }

	// PWM引脚配置
	Servo[0].pin	   = FL_CHANNEL;
	Servo[1].pin	   = FR_CHANNEL;
	Servo[2].pin	   = BL_CHANNEL;
	Servo[3].pin	   = BR_CHANNEL;

	// 初始化舵机数据
	Servo[0].num	   = Fl;
	Servo[0].angleAdj  = -270;
	Servo[0].sign	   = -1;

	Servo[1].num	   = Fr;
	Servo[1].angleAdj  = -90;
	Servo[1].sign	   = +1;

	Servo[2].num	   = Bl;
	Servo[2].angleAdj  = -90;
	Servo[2].sign	   = -1;

	Servo[3].num	   = Br;
	Servo[3].angleAdj  = +90;
	Servo[3].sign	   = +1;

	Servo[Fl].PWMmin   = 1250;
	Servo[Fl].PWMmax   = 6150;

	Servo[Fr].PWMmin   = 1500;
	Servo[Fr].PWMmax   = 6400;

	Servo[Bl].PWMmin   = 1000;
	Servo[Bl].PWMmax   = 5800;

	Servo[Br].PWMmin   = 1150;
	Servo[Br].PWMmax   = 6150;

	Servo[Fl].angleLeg = 180.f;
	Servo[Fr].angleLeg = 180.f;
	Servo[Bl].angleLeg = 0.f;
	Servo[Br].angleLeg = 0.f;

	// 引脚初始化 PWM频率250Hz
	for (size_t i = 0; i < 4; i++) pwm_init(Servo[i].pin, 250, (Servo[i].PWMmax + Servo[i].PWMmin) / 2);
}

/// @brief 定时器Func函数
/// @param
void ServoFunc(void)
{
	for (size_t id = 0; id < 4; id++)	 // 循环执行
	{
		// 解算部分
		Servo[id].angleSet = (Servo[id].angleLeg + Servo[id].angleAdj) * Servo[id].sign;

		// 驱动电机
		Servo[id].PWMSet   = Servo[id].PWMmin + Servo[id].angleSet * (Servo[id].PWMmax - Servo[id].PWMmin) / 180;
		Limit(Servo[id].PWMSet, Servo[id].PWMmin, Servo[id].PWMmax);	// 限幅保护

		pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	  // 设置PWM占空比
	}
};

float directionError = 0;
int	  direction_Kp = 120, direction_Kd = 0;	   // 舵机PD,循迹主要需要调的参数 109 405
int	  ServoControlOut = 0;					   // 舵机实际输出值

void Get_Direction_Error()
{
	// 计算误差并归一化
	directionError	= ((float) (MidLine[ControlRow] - (COL / 2))) / COL;

	directionError *= -3.0;	   // 放大和限幅范围由车实际情况调整

	// directionError= LimitBoth_float(directionError,-1.0,1.0);

	oled_show_float(60, 1, directionError, 2, 2);
}

void Direction_Control_Error(void)
{
	static float P, D, error_pre;
	/*
	 刘沐：简单写个舵机PID来位置闭环，这个舵机PID将是校内赛你们需要花最多时间进行调试的地方，加油捏
	 */
	Get_Direction_Error();
	P				= directionError;
	D				= directionError - error_pre;
	error_pre		= directionError;
	ServoControlOut = (direction_Kp * P) + (direction_Kd * D);
	if (StopFlag)
		ServoControlOut = 0;
	/*
	 刘沐：
	 下面是停车时把舵机打正，防止舵机乱晃
	 不想要可以删掉只保留 pwm_set_duty(SERVO_PWM,ServoControlOut);就行
	*/
}
