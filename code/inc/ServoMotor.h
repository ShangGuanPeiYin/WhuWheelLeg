#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

// �����ʼ��
#define FL_CHANNEL ATOM0_CH1_P33_9	   // ǰ����pwm����
#define FR_CHANNEL ATOM0_CH2_P33_11	   // ǰ�Ҷ��pwm����
#define BL_CHANNEL ATOM0_CH4_P20_3	   // ������pwm����
#define BR_CHANNEL ATOM0_CH3_P14_2	   // ���Ҷ��pwm����

#define ANGLEMAX  180						   // �����Χ�����Ƕ�
#define ANGLE2PWM (PWM_DUTY_MAX / ANGLEMAX)	   // ��λת�����Ƕȡ㣬ת��ΪPWM

// �ؽ����
typedef enum { Fl, Fr, Bl, Br } JointNum;

// ����ṹ��
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM ����
	JointNum		 joint;

	float angleSet;	   // ����λ�� = ��ֵ+�ƶ�ֵ
	float angleMid;	   // ��ֵ���൱�ڸ���һ����㡣
	float angleMov;	   // �ƶ�ֵ

	int32_t PWMSet;
} ServoType;

void ServoInit(void);
void ServoSetPosition(int id);
void ServoMov(JointNum num, float pos);
void ServoFunc(void);

#endif
