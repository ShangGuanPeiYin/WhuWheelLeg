#ifndef _LEGCONTROL_H_
#define _LEGCONTROL_H_
#include "vector.h"
#include "zf_common_typedef.h"

// ���ȵ��˶�
typedef struct _Motion {
	float t;

	uint8_t	 degree;	  // ���������鳤�� = �� + 1
	Vector2f Ctrl[11];	  // ���������Ƶ�
} MotionType;

void MotionInit(MotionType* motion);

#endif