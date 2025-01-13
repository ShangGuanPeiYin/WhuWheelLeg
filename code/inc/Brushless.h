#ifndef _BRUSHLESS_H_
#define _BRUSHLESS_H_

#include "Pid.h"
#include "zf_common_typedef.h"

// ��ˢ������ڳ�ʼ��
#define SMALL_DRIVER_UART	  (UART_2)
#define SMALL_DRIVER_BAUDRATE (460800)
#define SMALL_DRIVER_RX		  (UART2_TX_P10_5)
#define SMALL_DRIVER_TX		  (UART2_RX_P10_6)

//  P10-5 6 ����
//  P21-6 7 Uart
// ��ʱֻ���ٶ�ģʽ��λ��ģʽ�ȵ���д��Value��û��λ����Ϣ

// ��ˢ�������
#define OUTPUT_DUTY_MAX ((uint16) (4000))	 // ռ�ձ�������ֵ
#define PULSEPERROUND	32767				 // �������������ֵ  32767
#define PULSETIME		9999				 // ���ζ�ȡ������֮���ʱ�䣬��

typedef enum { Left, Right } Direction;

// ���ģʽ
typedef enum _BrushlessMode {
	CURRENT,	// ����ģʽ
	RPM,		// �ٶ�ģʽ
	POSITION	// λ��ģʽ
} BrushlessMode;

// ���ֵ
typedef struct _Value {
	volatile float speed;	   // rpm
	volatile float angle;	   // ��
	volatile float current;	   // ��PWM Set�õ�
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
	Direction direct;	 // ����

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

	ValueType	   valueLast, valueNow, valueSet;	 // �ϴ��յ����������յ���
	float		   reachTime;						 // λ��ģʽ���Բ�ֵ��
	PulseType	   pulse;
	MotorParamType param;
	MotorLimit	   limit;

	PIDType posPID, rpmPID, currentPID;	   // ����PID �����塢�ٶȡ������ջ�
} BrushlessType;

// ��ˢ���ͨѶ���ݽṹ��
typedef struct {
	uint8 send_data_buffer[7];		 // ���ͻ������� �ֽڰ�Ϊ7�ֽ�
	uint8 receive_data_buffer[7];	 // ���ջ�������
	uint8 receive_data_count;		 // ���ռ���
	uint8 sum_check_data;			 // ��У��λ

	int16 receive_left_speed_data;	   // ���յ���������ٶ�����
	int16 receive_right_speed_data;	   // ���յ����Ҳ����ٶ�����
} BrushlessDataType;

extern BrushlessDataType motor_value;
extern BrushlessType	 Motor[2];

void BrushlessInit(void);							 // �����ʼ��
void BrushlessTypeInit(void);						 // ����ṹ���ʼ��
void BrushlessFunc(void);							 // �ܽᣬ���ڶ�ʱ����
void BrushlessSetZero(BrushlessType* motor);		 // ���λ������
void BrushlessCulculate(BrushlessType* motor);		 // ������� ���� �� pos and rpm
void BrushlessSpeedMode(BrushlessType* motor);		 // �ٶ�ģʽ
void BrushlessPositionMode(BrushlessType* motor);	 // λ��ģʽ
void BrushlessCurrentMode(BrushlessType* motor);	 // ����ģʽ
void BrushlessLockPosition(BrushlessType* motor);	 // ������ǰλ��
void BrushlessSentCurrent(void);					 // ���͵���

void BrushlessDriver_callback(void);						  // ��ˢ���� ���ڽ��ջص�����
void Brushless_SetDuty(int16 left_duty, int16 right_duty);	  // ��ˢ���� ���õ��ռ�ձ�
void Brushless_AskSpeed(void);								  // ��ˢ���� ��ȡ�ٶ���Ϣ
void Brushless_uart_init(void);								  // ��ˢ���� ����ͨѶ��ʼ��

#endif
