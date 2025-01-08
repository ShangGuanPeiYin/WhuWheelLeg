#include "zf_common_headfile.h"

/********************* ģ��PID *********************** */
#if USEFUZZY
float EFF[7];	 // ����e������ֵ
float DFF[7];	 // ����de/dt������ֵ

const int rule_p[7][7] = {
	{NB, NB, NM, NM, NS, ZO, ZO}, //  kp�����
	{NB, NB, NM, NS, NS, ZO, NS},
	{NM, NM, NM, NS, ZO, NS, NS},
	{NM, NM, NS, ZO, NS, NM, NM},
	{NS, NS, ZO, NS, NS, NM, NM},
	{NS, ZO, NS, NM, NM, NM, NB},
	{ZO, ZO, NM, NM, NM, NB, NB}
};
const int rule_d[7][7] = {
	{PS, NS, NB, NB, NB, NM, PS}, //  kd�����
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
 * @brief  ȫ��PID�ṹ���ʼ��
 *
 * @param pid
 * @param param
 * @param outputThreshold 0 Ϊ���޷�
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
		= (outputThreshold != 0) ? outputThreshold : 9999999999999999.f;	// һ������ģ�float max����֪��������û������궨��

	pid->pOut	 = 0;
	pid->iOut	 = 0;
	pid->dOut	 = 0;
	pid->output	 = 0;

	pid->err[0]	 = 0;
	pid->err[1]	 = 0;
	pid->err[2]	 = 0;

	pid->kiScale = 1;
}

/// @brief  ����ʽPID��λ��PID�������㺯��
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
		// λ��ʽpid
		case PIDPOS:
			pid->err[2] = 0.5f * pid->err[0] + 0.5f * pid->err[2];	  // �˲����ۼ�Ki���

			pid->pOut	= pid->kp * pid->err[0];
			pid->iOut	= pid->ki * pid->err[2];
			pid->dOut	= pid->kd * (pid->err[0] - pid->err[1]);
			pid->output = pid->pOut + pid->kiScale * pid->iOut + pid->dOut;

			pid->err[1] = pid->err[0];
			break;

			// ����ʽpid
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

/******************************* ģ��PID TODO *************************************** */
#if USEFUZZY

/// @brief
/// @param uff_p_max
/// @param uff_d_max
/// @param UFF
/// @param Turn_FuzzyPD
void fuzzy_init(float uff_p_max, float uff_d_max, UFFType* UFF, FuzzyPidType* Turn_FuzzyPD)
{
	Turn_FuzzyPD->Kp0			= 50.0;	   // ����p�����Σ�
	Turn_FuzzyPD->Kd0			= 30.0,	   // ����d�����Σ�
		Turn_FuzzyPD->threshold = 10;	   // ��ֹ�������ұ仯���ٽ�ֵ
	Turn_FuzzyPD->maximum		= 15;	   // �������޷�
	Turn_FuzzyPD->minimum		= -15;	   // �����С�޷�
	Turn_FuzzyPD->factor		= 1.0;	   // ģ��ϵ��
	for (int i = 0; i < 7; i++)			   // ��ʼ��7��p��d��������
	{
		UFF->UFF_P[i] = uff_p_max * ((float) (i - 3) / 3);	  // ��p��Ϊ7�ȷ�
		UFF->UFF_D[i] = uff_d_max * ((float) (i - 3) / 3);	  // ��d��Ϊ7�ȷ�
	}
}

/// @brief
/// @param EFF
/// @param DFF
/// @param Fuzzy_PD
/// @param UFF
/// @param mode
/// @return
// float PID_FuzzyPD(float* EFF, float* DFF, FuzzyPidType* Fuzzy_PD, UFFType* UFF, uint8 mode)	   // ģ��pd
//{
//	if (mode) {
//		for (int i = 0; i < 7; i++)	   // ��ʼ��7��p��d��������
//		{
//			EFF[i] = 21 * ((float) (i - 3) / 3);	// ����Χ21��Ϊ7�ȷݣ������в����滻��
//			DFF[i] = 18 * ((float) (i - 3) / 3);	// �����仯�ʷ�Χ18��Ϊ7�ȷݣ������в����滻��
//		}
//	} else {
//		for (int i = 0; i < 7; i++)	   // ��ʼ��7��p��d��������
//		{
//			EFF[i] = 18 * ((float) (i - 3) / 3);	// ����Χ18��Ϊ7�ȷ�(�����в����滻)
//			DFF[i] = 9 * ((float) (i - 3) / 3);		// �����仯�ʷ�Χ9��Ϊ7�ȷݣ������в����滻��
//		}
//	}
//
//	// Fuzzy_PD->err		   = Fuzzy_PD->SetValue - Fuzzy_PD->CurrentValue;	 // 0-���
//	Fuzzy_PD->err = Err_Sum();							  // ���
//	float EC	  = Fuzzy_PD->err - Fuzzy_PD->errlast;	  // ���ı仯��
//
//	count_DMF(Fuzzy_PD->err * Fuzzy_PD->factor, EC * EC_FACTOR, EFF, DFF, &DMF);	// ģ����
//
//	Fuzzy_PD->Kp  = Fuzzy_PD->Kp0 + Fuzzy_Kp(&DMF, UFF);	// ����ģ���������p������p��ģ��p��
//	Fuzzy_PD->Kd  = Fuzzy_PD->Kd0 + Fuzzy_Kd(&DMF, UFF);	// ����ģ���������d������d��ģ��d��
//
//	Fuzzy_PD->Kp  = MAX(Fuzzy_PD->Kp, 0);	 // ��֤p������
//	Fuzzy_PD->Kd  = MAX(Fuzzy_PD->Kd, 0);	 // ��֤d������
//
//	// ����һ����ͨ��λ��ʽpd���
//	Fuzzy_PD->out = Fuzzy_PD->Kp * Fuzzy_PD->err + Fuzzy_PD->Kd * (Fuzzy_PD->err - Fuzzy_PD->errlast);	  // �����Σ�
//
//	// �൱��һ���˲��ˣ���ֹ����
//	if (ABS(Fuzzy_PD->out - Fuzzy_PD->outlast) > Fuzzy_PD->threshold) {
//		if (Fuzzy_PD->out > Fuzzy_PD->outlast)
//			Fuzzy_PD->out = Fuzzy_PD->outlast + Fuzzy_PD->threshold;
//		else
//			Fuzzy_PD->out = Fuzzy_PD->outlast - Fuzzy_PD->threshold;
//	}
//
//	// ����޷�
//	Limit(Fuzzy_PD->out, Fuzzy_PD->minimum, Fuzzy_PD->maximum);
//
//	// ����
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
// static void count_DMF(float e, float ec, float* EFF, float* DFF, DMFType* DMF)	  // ģ����e
// ec����ָ��浽�ṹ��DMF���ֱ��ʹ��
//{
//	// ��e�ĸ���������
//	if (e > EFF[0] && e < EFF[6]) {
//		for (int i = 0; i < 8 - 2; i++) {
//			if (e >= EFF[i] && e <= EFF[i + 1]) {
//				DMF->EF[0] = -(e - EFF[i + 1]) / (EFF[i + 1] - EFF[i]);		  // ������
//				DMF->EF[1] = 1 + (e - EFF[i + 1]) / (EFF[i + 1] - EFF[i]);	  // ������
//				DMF->En[0] = i;												  // �������ڹ�����Ӧ����ֵ
//				DMF->En[1] = i + 1;											  // �������ڹ�����Ӧ����ֵ
//				break;
//			}
//		}
//	} else {
//		if (e <= EFF[0])	// ������Χ
//		{
//			DMF->EF[0] = 1;
//			DMF->EF[1] = 0;
//			DMF->En[0] = 0;
//			DMF->En[1] = -1;
//		} else if (e >= EFF[6])	   // ������Χ
//		{
//			DMF->EF[0] = 1;
//			DMF->EF[1] = 0;
//			DMF->En[0] = 6;
//			DMF->En[1] = -1;
//		}
//	}
//	// ��ec�ĸ���������
//	if (ec > DFF[0] && ec < DFF[6]) {
//		for (int i = 0; i < 8 - 2; i++) {
//			if (ec >= DFF[i] && ec <= DFF[i + 1]) {
//				DMF->DF[0] = -(ec - DFF[i + 1]) / (DFF[i + 1] - DFF[i]);	   // ������
//				DMF->DF[1] = 1 + (ec - DFF[i + 1]) / (DFF[i + 1] - DFF[i]);	   // ������
//				DMF->Dn[0] = i;												   // �������ڹ�����Ӧ����ֵ
//				DMF->Dn[1] = i + 1;											   // �������ڹ�����Ӧ����ֵ
//				break;
//			}
//		}
//	} else {
//		if (ec <= DFF[0])	 // ������Χ
//		{
//			DMF->DF[0] = 1;
//			DMF->DF[1] = 0;
//			DMF->Dn[0] = 0;
//			DMF->Dn[1] = -1;
//		} else if (ec >= DFF[6])	// ������Χ
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
// static float Fuzzy_Kp(DMFType* DMF, UFFType* UFF)	 // ����ģ��p����ֱ��ʹ��
//{
//	float qdetail_kp;
//
//	float KpgradSums[7] = {0, 0, 0, 0, 0, 0, 0};
//
//	for (int i = 0; i < 2; i++) {
//		if (DMF->En[i] == -1)	 //-1�����ǳ�����������
//		{
//			continue;
//		}
//		for (int j = 0; j < 2; j++) {
//			if (DMF->Dn[j] != -1) {
//				int indexKp = rule_p[DMF->En[i]][DMF->Dn[j]] + 3;	 // U�������ȣ�+3��Ϊ����������飬���������-3,��Ӧ���������0
//				KpgradSums[indexKp]
//					= KpgradSums[indexKp] + (DMF->EF[i] * DMF->DF[j]);	  // �����������u���ڸ����ȼ��������ȵ������ܺ�
//			} else														  // ͬ��ec������������-1˵���������������
//			{
//				continue;
//			}
//		}
//	}
//	for (int i = 0; i < 8 - 1; i++) {
//		qdetail_kp += UFF->UFF_P[i] * KpgradSums[i];	// �������p��Ӧ���������ܺ�
//	}
//	return qdetail_kp;	  // ���ģ��p
// }

/// @brief
/// @param DMF
/// @param UFF
/// @return
// static float Fuzzy_Kd(DMFType* DMF, UFFType* UFF)	 // ����ģ��d����ֱ��ʹ��
//{
//	float qdetail_kd;
//	float KdgradSums[7] = {0, 0, 0, 0, 0, 0, 0};
//	for (int i = 0; i < 2; i++) {
//		if (DMF->En[i] == -1)	 //-1�����ǳ�����������
//		{
//			continue;
//		}
//		for (int j = 0; j < 2; j++) {
//			if (DMF->Dn[j] != -1) {
//				int indexKd = rule_d[DMF->En[i]][DMF->Dn[j]] + 3;
//				KdgradSums[indexKd]
//					= KdgradSums[indexKd] + (DMF->EF[i] * DMF->DF[j]);	  // �����������u���ڸ����ȼ��������ȵĸ����ܺ�
//			} else														  // ͬ��ec������������-1˵���������������
//			{
//				continue;
//			}
//		}
//	}
//	for (int i = 0; i < 8 - 1; i++) {
//		qdetail_kd += UFF->UFF_D[i] * KdgradSums[i];	// �������d��Ӧ���������ܺ�
//	}
//	return qdetail_kd;	  // ���ģ��d
// }

// float Turn_UFF_kp_max = -60.0f;											   // ģ���������ֵp���������Σ�
// float Turn_UFF_kd_max = 0.0f;											   // ģ���������ֵd���������Σ�
// fuzzy_init(Turn_UFF_kp_max, Turn_UFF_kd_max, &Turn_UFF, &Turn_FuzzyPD);	   // ģ�����Ʋ�����ʼ��
// out_d = PID_FuzzyPD(-Point, EFF, DFF, &Turn_FuzzyPD, &Turn_UFF, 0);		   // ģ��pid��PointΪ��������ƫ�
// ServoMotorctrl(90 + out_d);												   // �������

#endif
