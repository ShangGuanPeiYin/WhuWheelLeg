#ifndef _BRUSHLESS_H_
#define _BRUSHLESS_H_

#include "Pid.h"
#include "zf_common_typedef.h"

#define UES_BRUSHLESS_NUM 2		  // 使用数量
#define PULSEPERROUND	  1024	  // 电机每转一圈的脉冲数
#define PULSETIME		  9999	  // 两次读取脉冲数之间的时间，秒 TODO

// 电机模式
typedef enum _BrushlessMode {
	CURRENT,	// 力矩模式
	RPM,		// 速度模式
	POSITION	// 位置模式
} BrushlessMode;

// 电机值
typedef struct _Value {
	volatile float speed;	 // rpm
	volatile float angle;	 // °
	volatile float current;
} ValueType;

// 脉冲 不知道能不能用到
typedef struct _PulseType {
	volatile int16_t pulseRead;		// 电调读取的脉冲数
	volatile int16_t pulseLast;		// 电调读取的脉冲数
	volatile int16_t Distanse;		// 当前脉冲与上次脉冲数之差
	volatile int32_t pulseTotal;	// 累计脉冲数

	volatile int32_t pulseLock;	   // 累计脉冲数
} PulseType;

// 电机参数
typedef struct {
	float reductionRatio;	 // 电机减速比  好像不需要？
	float currentLimit;		 // 电流限制
} MotorParamType;

// 电机限制
typedef struct {
	// 限制标志位
	bool isStuck;			  // 是否堵转
	bool currentLimitFlag;	  // 电流限制
	bool rpmLimitFlag;		  // 速度限制
	bool posLimitFlag;		  // 位置限制

	// 数值限制
	float maxCurrent;	 //  最大电流(PWM) rpmPID的输出限幅
	float maxRPM;		 // 速度 posPID的输出限幅
} MotorLimit;

// 电机结构体
typedef struct _Brushless {
	bool		  enable;
	bool		  begin;
	bool		  setZero;
	BrushlessMode mode;

	ValueType	   valueLast, valueNow, valueSet;
	float		   reachTime;	 // 位置模式线性插值用
	PulseType	   pulse;
	MotorParamType param;
	MotorLimit	   limit;

	PIDType posPID, rpmPID, currentPID;	   // 三环PID 对脉冲、速度、电流闭环
} BrushlessType;

extern BrushlessType Motor[UES_BRUSHLESS_NUM];

void BrushlessInit(void);							 // 电机初始化
void BrushlessFunc(void);							 // 总结，放在定时器中
void BrushlessSetZero(BrushlessType* motor);		 // 电机位置置零
void BrushlessCulculate(BrushlessType* motor);		 // 电机解算 脉冲 → pos and rpm
void BrushlessSpeedMode(BrushlessType* motor);		 // 速度模式
void BrushlessPositionMode(BrushlessType* motor);	 // 位置模式
void BrushlessCurrentMode(BrushlessType* motor);	 // 电流模式
void BrushlessLockPosition(BrushlessType* motor);	 // 锁到当前位置
void BrushlessSentCurrent(BrushlessType* motor);	 // 发送电流

#endif
