#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"
/*
180�ȶ��ʵ��ת����Χ��΢����180��0-180��ʵ��Ҳ����0-1w�����Ǵ�Լ1300-6200�����Ҹ������������ͬ

����������ȵ�0-180�ȽǶ�ӦPWM��Χ��
��ǰ��1250 - 3700 - 6150   ��ǰ��1500 - 3950 - 6400
���1000 - 3400 - 5800   �Һ�1150 - 3650 - 6150
��Ϊ5000�㶨

 �����ϵΪ��
 PWMSet = PWMmin + angleSet * (PWMmax - PWMmin) / 180;

*/

// �����ʼ��
#define FL_CHANNEL ATOM0_CH3_P14_2	   // ǰ����pwm����
#define FR_CHANNEL ATOM0_CH4_P20_3	   // ǰ�Ҷ��pwm����
#define BL_CHANNEL ATOM0_CH1_P33_9	   // ������pwm����
#define BR_CHANNEL ATOM0_CH2_P33_11	   // ���Ҷ��pwm����

// �ؽ����
typedef enum { Fl, Fr, Bl, Br } JointNum;

// ����ṹ��
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM ����
	JointNum		 num;

	float	angleSet;	 // �����ʵ��ת�� ��������ýǶ��� �� ��0-180�㣩
	float	angleAdj;	 // ����ĵ���ֵ
	float	angleLeg;	 // ��Leg�ϵĻ���Ƕȣ���Leg.h�ġ�1���4
	int8	sign;		 // �����ţ�������
	int32_t PWMmin, PWMmax;

	int32_t PWMSet;
} ServoType;

extern ServoType Servo[4];

void ServoInit(void);
void ServoFunc(void);

void Get_Direction_Error();

void Direction_Control_Error();

extern int ServoControlOut;
extern int direction_Kp;
extern int direction_Kd;
extern float directionError;

#endif
