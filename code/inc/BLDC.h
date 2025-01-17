#ifndef _BRUSHLESS_H_
#define _BRUSHLESS_H_

#include "Pid.h"
#include "zf_common_typedef.h"

// 无刷电机串口初始化
#define SMALL_DRIVER_UART	  (UART_2)
#define SMALL_DRIVER_BAUDRATE (460800)
#define SMALL_DRIVER_RX		  (UART2_TX_P10_5)	  // 根据需要改一下
#define SMALL_DRIVER_TX		  (UART2_RX_P10_6)	  // 根据需要改一下

//  P10-5 6 串口
//  P21-6 7 Uart
// 暂时只有速度模式，位置模式等等再写。Value中没有位置信息

// PWM>0时
// 左电机正转 右电机反转

// 无刷电机控制
#define OUTPUT_DUTY_MAX ((uint16) (4000))	 // 占空比输出最大值
#define PULSEPERROUND	32767				 // 编码器采样最大值  32767
#define PULSETIME		9999				 // 两次读取脉冲数之间的时间，秒

typedef enum { Left, Right } LegNum;

// 电机模式
typedef enum _BldcMode {
	CURRENT,	// 力矩模式
	RPM,		// 速度模式
	POSITION	// 位置模式
} BldcMode;

// 电机值
typedef struct _Value {
	volatile float speed;	   // rpm
	volatile float angle;	   // °
	volatile int16 current;	   // 即PWM Set用到
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
	LegNum	direct;	   // 左右
	uint8_t sign;	   // 左电机正转，右电机反转。控制的时候右电机pwm*=-1，反馈数据*=-1

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
typedef struct _Bldc {
	bool	 enable;
	bool	 begin;
	bool	 setZero;
	BldcMode mode;

	ValueType	   valueLast, valueNow, valueSet;	 // 上次收到的与现在收到的
	float		   reachTime;						 // 位置模式线性插值用
	PulseType	   pulse;
	MotorParamType param;
	MotorLimit	   limit;

	PIDType posPID, rpmPID, currentPID;	   // 三环PID 对脉冲、速度、电流闭环
} BldcType;

// 无刷电机通讯数据结构体
typedef struct {
	uint8 send_data_buffer[7];		 // 发送缓冲数组 字节包为7字节
	uint8 receive_data_buffer[7];	 // 接收缓冲数组
	uint8 receive_data_count;		 // 接收计数
	uint8 sum_check_data;			 // 和校验位

	int16 receive_left_speed_data;	   // 接收到的左侧电机速度数据
	int16 receive_right_speed_data;	   // 接收到的右侧电机速度数据
} BldcDataType;

extern BldcDataType motor_value;
extern BldcType		Motor[2];

void BldcInit(void);					   // 电机初始化
void BldcTypeInit(void);				   // 电机结构体初始化
void BldcFunc(void);					   // 总结，放在定时器中
void BldcSetZero(BldcType* motor);		   // 电机位置置零
void BldcCulculate(BldcType* motor);	   // 电机解算 脉冲 → pos and rpm
void BldcSpeedMode(BldcType* motor);	   // 速度模式
void BldcPositionMode(BldcType* motor);	   // 位置模式
void BldcCurrentMode(BldcType* motor);	   // 电流模式
void BldcLockPosition(BldcType* motor);	   // 锁到当前位置
void BldcSentCurrent(void);				   // 发送电流

void Bldc_Driver_callback(void);						 // 无刷驱动 串口接收回调函数
void Bldc_SetDuty(int16 left_duty, int16 right_duty);	 // 无刷驱动 设置电机占空比
void Bldc_AskSpeed(void);								 // 无刷驱动 获取速度信息
void Bldc_uart_init(void);								 // 无刷驱动 串口通讯初始化

void BldcSetCurrent(float leftCur, float rightCur);	   // 设置函数
void BldcSetSpeed(float leftSpeed, float rightSpeed);
void BldcSetPos(float leftPos, float rightPos);	   // TODO

#endif
