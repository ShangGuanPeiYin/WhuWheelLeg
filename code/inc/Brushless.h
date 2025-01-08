#ifndef _BRUSHLESS_H_
#define _BRUSHLESS_H_

#include "Pid.h"
#include "zf_common_typedef.h"

#define UES_BRUSHLESS_NUM 2		  // ʹ������
#define PULSEPERROUND	  1024	  // ���ÿתһȦ��������
#define PULSETIME		  9999	  // ���ζ�ȡ������֮���ʱ�䣬�� TODO

// ���ģʽ
typedef enum _BrushlessMode {
	CURRENT,	// ����ģʽ
	RPM,		// �ٶ�ģʽ
	POSITION	// λ��ģʽ
} BrushlessMode;

// ���ֵ
typedef struct _Value {
	volatile float speed;	 // rpm
	volatile float angle;	 // ��
	volatile float current;
} ValueType;

// ���� ��֪���ܲ����õ�
typedef struct _PulseType {
	volatile int16_t pulseRead;		// �����ȡ��������
	volatile int16_t pulseLast;		// �����ȡ��������
	volatile int16_t Distanse;		// ��ǰ�������ϴ�������֮��
	volatile int32_t pulseTotal;	// �ۼ�������

	volatile int32_t pulseLock;	   // �ۼ�������
} PulseType;

// �������
typedef struct {
	float reductionRatio;	 // ������ٱ�  ������Ҫ��
	float currentLimit;		 // ��������
} MotorParamType;

// �������
typedef struct {
	// ���Ʊ�־λ
	bool isStuck;			  // �Ƿ��ת
	bool currentLimitFlag;	  // ��������
	bool rpmLimitFlag;		  // �ٶ�����
	bool posLimitFlag;		  // λ������

	// ��ֵ����
	float maxCurrent;	 //  ������(PWM) rpmPID������޷�
	float maxRPM;		 // �ٶ� posPID������޷�
} MotorLimit;

// ����ṹ��
typedef struct _Brushless {
	bool		  enable;
	bool		  begin;
	bool		  setZero;
	BrushlessMode mode;

	ValueType	   valueLast, valueNow, valueSet;
	float		   reachTime;	 // λ��ģʽ���Բ�ֵ��
	PulseType	   pulse;
	MotorParamType param;
	MotorLimit	   limit;

	PIDType posPID, rpmPID, currentPID;	   // ����PID �����塢�ٶȡ������ջ�
} BrushlessType;

extern BrushlessType Motor[UES_BRUSHLESS_NUM];

void BrushlessInit(void);							 // �����ʼ��
void BrushlessFunc(void);							 // �ܽᣬ���ڶ�ʱ����
void BrushlessSetZero(BrushlessType* motor);		 // ���λ������
void BrushlessCulculate(BrushlessType* motor);		 // ������� ���� �� pos and rpm
void BrushlessSpeedMode(BrushlessType* motor);		 // �ٶ�ģʽ
void BrushlessPositionMode(BrushlessType* motor);	 // λ��ģʽ
void BrushlessCurrentMode(BrushlessType* motor);	 // ����ģʽ
void BrushlessLockPosition(BrushlessType* motor);	 // ������ǰλ��
void BrushlessSentCurrent(BrushlessType* motor);	 // ���͵���

#endif
