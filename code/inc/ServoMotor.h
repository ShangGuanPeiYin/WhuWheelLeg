#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"

#define USESERVONUM 4

// ����ṹ��
typedef struct _Servo {
	bool enable;
	bool begin;

	float angleSet;	   // ����λ��
} ServoType;

void ServoFunc(void);

#endif
