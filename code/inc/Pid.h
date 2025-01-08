#ifndef _PID_H
#define _PID_H

#include "zf_common_typedef.h"

/*********************** 模糊PID **************** */
#define USEFUZZY 1

#define PB		  3		// 正大
#define PM		  2		// 正中
#define PS		  1		// 正小
#define ZO		  0		// 中
#define NS		  -1	// 负小
#define NM		  -2	// 负中
#define NB		  -3	// 负大
#define EC_FACTOR 1		// 误差变化率的因子

typedef enum _PIDMode {
	PIDPOS,
	PIDINC,
	PIDFuzzy	// 模糊PID
} PIDMode;

// 全能PID
typedef struct _PID {
	PIDMode mode;

	volatile float kp;
	volatile float ki;
	volatile float kd;

	volatile float pOut;
	volatile float iOut;
	volatile float dOut;

	volatile float err[3];

	float outputThreshold;	  // 误差限幅

	volatile float output;

	float kiScale;	  // Ki的缩放因子或调整系数
} PIDType;

/****** 模糊PID使用结构体 */
typedef struct _DMFType {
	int EF[2];
	int En[2];
	int DF[2];
	int Dn[2];
} DMFType;

typedef struct _UFFType {
	float UFF_P[7];
	float UFF_I[7];
	float UFF_D[7];
} UFFType;

typedef struct _FuzzyPidType {
	float Kp0;
	float Ki0;
	float Kd0;

	float Kp;
	float Ki;
	float Kd;

	float threshold;

	float maximum;
	float minimum;

	float factor;

	float err;
	float errlast;
	float errlastlast;
	float out;
	float outlast;

} FuzzyPidType;

extern PIDType* ServoPID;
extern PIDType* SpeedPID;
extern PIDType* DifSpeedPID;

void  PIDTypeInit(PIDType* pid, float kp, float ki, float kd, PIDMode mode, float outputThreshold);
float PIDOperation(PIDType* pid, float real, float target);

void		 fuzzy_init(float uff_p_max, float uff_d_max, UFFType* UFF, FuzzyPidType* Turn_FuzzyPD);
// float PID_FuzzyPD(float* EFF, float* DFF, FuzzyPidType* Fuzzy_PD, UFFType* UFF, uint8 mode);
static void	 count_DMF(float e, float ec, float* EFF, float* DFF, DMFType* DMF);
static float Fuzzy_Kp(DMFType* DMF, UFFType* UFF);
static float Fuzzy_Kd(DMFType* DMF, UFFType* UFF);
#endif
