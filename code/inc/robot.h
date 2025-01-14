#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "zf_common_typedef.h"

// ����״̬
enum StateEnum {
	StatePreparing,		// ׼����
	StateProcessing,	// ������
	StateEnd,			// ����
};

// ����״̬��ˮ�ߣ����Ӷ������õ�
typedef struct _Pipeline {
	bool		   isRun;	 // ��������
	enum StateEnum state;
} PipelineType;

typedef struct _robot {
	PipelineType pipeline;

	LegType* left;
	LegType* right;

	IMUType* posture;

	ParamType robotParam;

} RobotType;

extern RobotType robot;

void Start(PipelineType* pipeline);		   // ���״̬��ˮ�����п�ʼ����
void Prepared(PipelineType* pipeline);	   // ��׼����
void Processed(PipelineType* pipeline);	   // �ѽ�����

void BalanceYaw(void);		// ƫ����ƽ��
void BalanceRoll(void);		// �����ƽ��
void BalancePitch(void);	// ������ƽ��

#endif
