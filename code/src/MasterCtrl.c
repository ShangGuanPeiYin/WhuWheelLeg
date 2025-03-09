#include "zf_common_headfile.h"

void MotionInit(MotionType* motion)
{
	memset(motion, 0, sizeof(MotionType));	  // ������
											  // TODO ���������Ƶ㸳ֵ
};

/**
 * @brief ��ʼ��boundParam
 *
 * @param boundParam
 */
void BoundCtrlInit(BoundParamType* boundParam)
{
	// TODO
	boundParam->x0		 = 20;	  // �������������ĵ� �趨
	boundParam->y0		 = 220;
	boundParam->H0		 = 100;
	boundParam->H_KICK	 = 100;	   // �ŵظ߶�  �ŵض��˶�����   ����θ߶�   ������˶�����
	boundParam->L_KICK	 = 110;
	boundParam->H_BUFF	 = 40;
	boundParam->L_BUFF	 = 110;
	boundParam->T_KICK	 = 90;	  // �ŵ���(ms)  ������(ms)123   �����(ms)
	boundParam->T_WAIT_1 = 130;
	boundParam->T_WAIT_2 = 0;
	boundParam->T_WAIT_3 = 130;
	boundParam->T_BUFF	 = 140;
	boundParam->Rotation = 0;

	BoundCtrlCal(boundParam);
};

/**
 * @brief ����CtrlPoint
 *
 * @param boundParam
 */
void BoundCtrlCal(BoundParamType* boundParam) {
	// TODO ���鷳

	/*
	float dL_KICK	  = L_KICK / 3;
	float dL_BUFF	  = L_BUFF / 3;

	BezierX_kick[0]	  = 0;
	BezierX_kick[1]	  = dL_KICK;
	BezierX_kick[2]	  = L_KICK - dL_KICK;
	BezierX_kick[3]	  = L_KICK;
	BezierY_kick[0]	  = H_KICK;
	BezierY_kick[1]	  = H_KICK * 2 / 3.f;
	BezierY_kick[2]	  = H_KICK / 3.f;
	BezierY_kick[3]	  = 0;

	BezierX_wait_1[0] = L_KICK;
	BezierX_wait_1[1] = L_KICK + dL_KICK;
	BezierX_wait_1[2] = L_KICK - dL_KICK;
	BezierX_wait_1[3] = 0;
	BezierY_wait_1[0] = 0;
	BezierY_wait_1[1] = H / 2;
	BezierY_wait_1[2] = H;
	BezierY_wait_1[3] = H;

	BezierX_wait_3[0] = 0;
	BezierX_wait_3[1] = -L_BUFF + dL_KICK;
	BezierX_wait_3[2] = -L_BUFF - dL_KICK;
	BezierX_wait_3[3] = -L_BUFF;
	BezierY_wait_3[0] = H;
	BezierY_wait_3[1] = H;
	BezierY_wait_3[2] = H - H_BUFF / 2;
	BezierY_wait_3[3] = H - H_BUFF;

	BezierX_buff[0]	  = -L_BUFF;
	BezierX_buff[1]	  = -L_BUFF + dL_BUFF;
	BezierX_buff[2]	  = -dL_BUFF;
	BezierX_buff[3]	  = 0;
	BezierY_buff[0]	  = H - H_BUFF;
	BezierY_buff[1]	  = (H_KICK + H - H_BUFF) / 6;
	BezierY_buff[2]	  = (H_KICK + H - H_BUFF) / 2;
	BezierY_buff[3]	  = H_KICK;

	for (int i = 0; i < 4; i++) {
		BezierX_kick[i]	  += x0;
		BezierY_kick[i]	   = y0 - BezierY_kick[i];
		BezierX_wait_1[i] += x0;
		BezierY_wait_1[i]  = y0 - BezierY_wait_1[i];
		BezierX_wait_3[i] += x0;
		BezierY_wait_3[i]  = y0 - BezierY_wait_3[i];
		BezierX_buff[i]	  += x0;
		BezierY_buff[i]	   = y0 - BezierY_buff[i];
	}

	*/
};
