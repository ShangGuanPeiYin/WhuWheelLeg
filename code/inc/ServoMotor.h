#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

#define ANGLEMAX  180						   // �����Χ�����Ƕ�
#define ANGLE2PWM (PWM_DUTY_MAX / ANGLEMAX)	   // ��λת�����Ƕȡ㣬ת��ΪPWM

// �ؽ����
typedef enum { Fl, Fr, Bl, Br } JointNum;

// ����ṹ��
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM ����
	JointNum		 joint;

	float cntTime;	  // ��λms
	float reachTime;

	float angleSet;	   // ����λ�� = ��ֵ+�ƶ�ֵ
	float angleMid;	   // ��ֵ���൱�ڸ���һ����㡣
	float angleMov;	   // �ƶ�ֵ

	int32_t PWMSet;
} ServoType;

void ServoInit(void);
void ServoSetPosition(int id);
void ServoMov(JointNum num, float reachTime, float pos);
void ServoFunc(void);

#endif
