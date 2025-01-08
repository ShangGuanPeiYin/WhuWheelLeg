#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"

#define USESERVONUM 4

// 舵机结构体
typedef struct _Servo {
	bool enable;
	bool begin;

	float angleSet;	   // 设置位置
} ServoType;

void ServoFunc(void);

#endif
