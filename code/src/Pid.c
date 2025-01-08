#include "zf_common_headfile.h"

/********************* 模糊PID *********************** */
#if USEFUZZY
float EFF[7];	 // 输入e的隶属值
float DFF[7];	 // 输入de/dt的隶属值

const int rule_p[7][7] = {
	{NB, NB, NM, NM, NS, ZO, ZO}, //  kp规则表
	{NB, NB, NM, NS, NS, ZO, NS},
	{NM, NM, NM, NS, ZO, NS, NS},
	{NM, NM, NS, ZO, NS, NM, NM},
	{NS, NS, ZO, NS, NS, NM, NM},
	{NS, ZO, NS, NM, NM, NM, NB},
	{ZO, ZO, NM, NM, NM, NB, NB}
};
const int rule_d[7][7] = {
	{PS, NS, NB, NB, NB, NM, PS}, //  kd规则表
	{PS, NS, NB, NM, NM, NS, ZO},
	{ZO, NS, NM, NM, NS, NS, ZO},
	{ZO, NS, NS, NS, NS, NS, ZO},
	{ZO, ZO, ZO, ZO, ZO, ZO, ZO},
	{PB, NS, PS, PS, PS, PS, PB},
	{PB, PM, PM, PM, PS, PS, PB}
};
DMFType		  DMF;
FuzzyPidType* Turn_FuzzyPD;
#endif

/**
 * @brief  全能PID结构体初始化
 *
 * @param pid
 * @param param
 * @param outputThreshold 0 为不限幅
 * @param mode
 */
void PIDTypeInit(PIDType* pid, float kp, float ki, float kd, PIDMode mode, float outputThreshold)
{
	if (pid == NULL)
		return;

	pid->kp	  = kp;
	pid->ki	  = ki;
	pid->kd	  = kd;

	pid->mode = mode;
	pid->outputThreshold
		= (outputThreshold != 0) ? outputThreshold : 9999999999999999.f;	// 一个极大的，float max，不知道库里有没有这个宏定义

	pid->pOut	 = 0;
	pid->iOut	 = 0;
	pid->dOut	 = 0;
	pid->output	 = 0;

	pid->err[0]	 = 0;
	pid->err[1]	 = 0;
	pid->err[2]	 = 0;

	pid->kiScale = 1;
}

/// @brief  增量式PID与位置PID共用运算函数
/// @param pid
/// @param real
/// @param target
/// @return
float PIDOperation(PIDType* pid, float real, float target)
{
	if (pid == NULL)
		return 0.f;

	pid->err[0] = target - real;

	switch (pid->mode) {
		// 位置式pid
		case PIDPOS:
			pid->err[2] = 0.5f * pid->err[0] + 0.5f * pid->err[2];	  // 滤波，累计Ki输出

			pid->pOut	= pid->kp * pid->err[0];
			pid->iOut	= pid->ki * pid->err[2];
			pid->dOut	= pid->kd * (pid->err[0] - pid->err[1]);
			pid->output = pid->pOut + pid->kiScale * pid->iOut + pid->dOut;

			pid->err[1] = pid->err[0];
			break;

			// 增量式pid
		case PIDINC:
			pid->pOut	= pid->kp * (pid->err[0] - pid->err[1]);
			pid->iOut	= pid->ki * pid->err[0];
			pid->dOut	= pid->kd * (pid->err[0] - 2 * pid->err[1] + pid->err[2]);
			pid->output = pid->pOut + pid->iOut + pid->dOut;

			pid->err[2] = pid->err[1];
			pid->err[1] = pid->err[0];
			break;

		case PIDFuzzy:
			// TODO
			break;
		default:
			break;
	}

	PEAK(pid->err[0], pid->outputThreshold);
	return pid->output;
}

/******************************* 模糊PID TODO *************************************** */
#if USEFUZZY

/// @brief
/// @param uff_p_max
/// @param uff_d_max
/// @param UFF
/// @param Turn_FuzzyPD
void fuzzy_init(float uff_p_max, float uff_d_max, UFFType* UFF, FuzzyPidType* Turn_FuzzyPD)
{
	Turn_FuzzyPD->Kp0			= 50.0;	   // 基础p（调参）
	Turn_FuzzyPD->Kd0			= 30.0,	   // 基础d（调参）
		Turn_FuzzyPD->threshold = 10;	   // 防止参数剧烈变化的临界值
	Turn_FuzzyPD->maximum		= 15;	   // 输出最大限幅
	Turn_FuzzyPD->minimum		= -15;	   // 输出最小限幅
	Turn_FuzzyPD->factor		= 1.0;	   // 模糊系数
	for (int i = 0; i < 7; i++)			   // 初始化7个p和d的隶属度
	{
		UFF->UFF_P[i] = uff_p_max * ((float) (i - 3) / 3);	  // 将p化为7等份
		UFF->UFF_D[i] = uff_d_max * ((float) (i - 3) / 3);	  // 将d化为7等份
	}
}

/// @brief
/// @param EFF
/// @param DFF
/// @param Fuzzy_PD
/// @param UFF
/// @param mode
/// @return
// float PID_FuzzyPD(float* EFF, float* DFF, FuzzyPidType* Fuzzy_PD, UFFType* UFF, uint8 mode)	   // 模糊pd
//{
//	if (mode) {
//		for (int i = 0; i < 7; i++)	   // 初始化7个p和d的隶属度
//		{
//			EFF[i] = 21 * ((float) (i - 3) / 3);	// 将误差范围21化为7等份（需自行测量替换）
//			DFF[i] = 18 * ((float) (i - 3) / 3);	// 将误差变化率范围18化为7等份（需自行测量替换）
//		}
//	} else {
//		for (int i = 0; i < 7; i++)	   // 初始化7个p和d的隶属度
//		{
//			EFF[i] = 18 * ((float) (i - 3) / 3);	// 将误差范围18化为7等份(需自行测量替换)
//			DFF[i] = 9 * ((float) (i - 3) / 3);		// 将误差变化率范围9化为7等份（需自行测量替换）
//		}
//	}
//
//	// Fuzzy_PD->err		   = Fuzzy_PD->SetValue - Fuzzy_PD->CurrentValue;	 // 0-误差
//	Fuzzy_PD->err = Err_Sum();							  // 误差
//	float EC	  = Fuzzy_PD->err - Fuzzy_PD->errlast;	  // 误差的变化率
//
//	count_DMF(Fuzzy_PD->err * Fuzzy_PD->factor, EC * EC_FACTOR, EFF, DFF, &DMF);	// 模糊化
//
//	Fuzzy_PD->Kp  = Fuzzy_PD->Kp0 + Fuzzy_Kp(&DMF, UFF);	// 反解模糊化并输出p（基础p＋模糊p）
//	Fuzzy_PD->Kd  = Fuzzy_PD->Kd0 + Fuzzy_Kd(&DMF, UFF);	// 反解模糊化并输出d（基础d＋模糊d）
//
//	Fuzzy_PD->Kp  = MAX(Fuzzy_PD->Kp, 0);	 // 保证p是正数
//	Fuzzy_PD->Kd  = MAX(Fuzzy_PD->Kd, 0);	 // 保证d是正数
//
//	// 经过一个普通的位置式pd输出
//	Fuzzy_PD->out = Fuzzy_PD->Kp * Fuzzy_PD->err + Fuzzy_PD->Kd * (Fuzzy_PD->err - Fuzzy_PD->errlast);	  // （调参）
//
//	// 相当于一个滤波了，防止噪声
//	if (ABS(Fuzzy_PD->out - Fuzzy_PD->outlast) > Fuzzy_PD->threshold) {
//		if (Fuzzy_PD->out > Fuzzy_PD->outlast)
//			Fuzzy_PD->out = Fuzzy_PD->outlast + Fuzzy_PD->threshold;
//		else
//			Fuzzy_PD->out = Fuzzy_PD->outlast - Fuzzy_PD->threshold;
//	}
//
//	// 输出限幅
//	Limit(Fuzzy_PD->out, Fuzzy_PD->minimum, Fuzzy_PD->maximum);
//
//	// 更新
//	Fuzzy_PD->errlast	  = Fuzzy_PD->err;
//	Fuzzy_PD->errlastlast = Fuzzy_PD->errlast;
//	Fuzzy_PD->outlast	  = Fuzzy_PD->out;
//
//	return Fuzzy_PD->out;
// }

/// @brief
/// @param e
/// @param ec
/// @param EFF
/// @param DFF
/// @param DMF
// static void count_DMF(float e, float ec, float* EFF, float* DFF, DMFType* DMF)	  // 模糊化e
// ec，用指针存到结构体DMF里，可直接使用
//{
//	// 求e的各个隶属度
//	if (e > EFF[0] && e < EFF[6]) {
//		for (int i = 0; i < 8 - 2; i++) {
//			if (e >= EFF[i] && e <= EFF[i + 1]) {
//				DMF->EF[0] = -(e - EFF[i + 1]) / (EFF[i + 1] - EFF[i]);		  // 隶属度
//				DMF->EF[1] = 1 + (e - EFF[i + 1]) / (EFF[i + 1] - EFF[i]);	  // 隶属度
//				DMF->En[0] = i;												  // 隶属度在规则表对应的数值
//				DMF->En[1] = i + 1;											  // 隶属度在规则表对应的数值
//				break;
//			}
//		}
//	} else {
//		if (e <= EFF[0])	// 超出范围
//		{
//			DMF->EF[0] = 1;
//			DMF->EF[1] = 0;
//			DMF->En[0] = 0;
//			DMF->En[1] = -1;
//		} else if (e >= EFF[6])	   // 超出范围
//		{
//			DMF->EF[0] = 1;
//			DMF->EF[1] = 0;
//			DMF->En[0] = 6;
//			DMF->En[1] = -1;
//		}
//	}
//	// 求ec的各个隶属度
//	if (ec > DFF[0] && ec < DFF[6]) {
//		for (int i = 0; i < 8 - 2; i++) {
//			if (ec >= DFF[i] && ec <= DFF[i + 1]) {
//				DMF->DF[0] = -(ec - DFF[i + 1]) / (DFF[i + 1] - DFF[i]);	   // 隶属度
//				DMF->DF[1] = 1 + (ec - DFF[i + 1]) / (DFF[i + 1] - DFF[i]);	   // 隶属度
//				DMF->Dn[0] = i;												   // 隶属度在规则表对应的数值
//				DMF->Dn[1] = i + 1;											   // 隶属度在规则表对应的数值
//				break;
//			}
//		}
//	} else {
//		if (ec <= DFF[0])	 // 超出范围
//		{
//			DMF->DF[0] = 1;
//			DMF->DF[1] = 0;
//			DMF->Dn[0] = 0;
//			DMF->Dn[1] = -1;
//		} else if (ec >= DFF[6])	// 超出范围
//		{
//			DMF->DF[0] = 1;
//			DMF->DF[1] = 0;
//			DMF->Dn[0] = 6;
//			DMF->Dn[1] = -1;
//		}
//	}
// }

/// @brief
/// @param DMF
/// @param UFF
/// @return
// static float Fuzzy_Kp(DMFType* DMF, UFFType* UFF)	 // 反解模糊p，可直接使用
//{
//	float qdetail_kp;
//
//	float KpgradSums[7] = {0, 0, 0, 0, 0, 0, 0};
//
//	for (int i = 0; i < 2; i++) {
//		if (DMF->En[i] == -1)	 //-1属于是超出规则表格了
//		{
//			continue;
//		}
//		for (int j = 0; j < 2; j++) {
//			if (DMF->Dn[j] != -1) {
//				int indexKp = rule_p[DMF->En[i]][DMF->Dn[j]] + 3;	 // U的隶属度，+3是为了下面的数组，规则表中是-3,对应下面数组的0
//				KpgradSums[indexKp]
//					= KpgradSums[indexKp] + (DMF->EF[i] * DMF->DF[j]);	  // 这个数组存的是u对于各个等级的隶属度的期望总和
//			} else														  // 同样ec规则索引等于-1说明这个索引不存在
//			{
//				continue;
//			}
//		}
//	}
//	for (int i = 0; i < 8 - 1; i++) {
//		qdetail_kp += UFF->UFF_P[i] * KpgradSums[i];	// 输出各个p对应的隶属度总和
//	}
//	return qdetail_kp;	  // 输出模糊p
// }

/// @brief
/// @param DMF
/// @param UFF
/// @return
// static float Fuzzy_Kd(DMFType* DMF, UFFType* UFF)	 // 反解模糊d，可直接使用
//{
//	float qdetail_kd;
//	float KdgradSums[7] = {0, 0, 0, 0, 0, 0, 0};
//	for (int i = 0; i < 2; i++) {
//		if (DMF->En[i] == -1)	 //-1属于是超出规则表格了
//		{
//			continue;
//		}
//		for (int j = 0; j < 2; j++) {
//			if (DMF->Dn[j] != -1) {
//				int indexKd = rule_d[DMF->En[i]][DMF->Dn[j]] + 3;
//				KdgradSums[indexKd]
//					= KdgradSums[indexKd] + (DMF->EF[i] * DMF->DF[j]);	  // 这个数组存的是u对于各个等级的隶属度的概率总和
//			} else														  // 同样ec规则索引等于-1说明这个索引不存在
//			{
//				continue;
//			}
//		}
//	}
//	for (int i = 0; i < 8 - 1; i++) {
//		qdetail_kd += UFF->UFF_D[i] * KdgradSums[i];	// 输出各个d对应的隶属度总和
//	}
//	return qdetail_kd;	  // 输出模糊d
// }

// float Turn_UFF_kp_max = -60.0f;											   // 模糊控制最大值p参数（调参）
// float Turn_UFF_kd_max = 0.0f;											   // 模糊控制最大值d参数（调参）
// fuzzy_init(Turn_UFF_kp_max, Turn_UFF_kd_max, &Turn_UFF, &Turn_FuzzyPD);	   // 模糊控制参数初始化
// out_d = PID_FuzzyPD(-Point, EFF, DFF, &Turn_FuzzyPD, &Turn_UFF, 0);		   // 模糊pid（Point为赛道中线偏差）
// ServoMotorctrl(90 + out_d);												   // 舵机控制

#endif
