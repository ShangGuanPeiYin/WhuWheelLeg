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

typedef struct _JumpLineType {
	Vector2f Pos[5];
	float	 reachTime[5];
} JumpLineType;

typedef struct _robot {
	PipelineType pipeline;

	LegType* left;
	LegType* right;

	IMUType* posture;

	ParamType	 robotParam;
	JumpLineType jumpLine;

	// TODO: CameraType

} RobotType;

extern RobotType robot;

void robotInit(RobotType* robot);

void robotRun(void);
void robotDrawLine(void);
void robotDrawCurve(void);
bool RobotJumpLine(void);
void RobotJumpLineInit(void);

void RobotError(void);

void Start(PipelineType* pipeline);		   // ���״̬��ˮ�����п�ʼ����
void Prepared(PipelineType* pipeline);	   // ��׼����
void Processed(PipelineType* pipeline);	   // �ѽ�����

void BalanceYaw(void);		// ƫ����ƽ��
void BalanceRoll(void);		// �����ƽ��
void BalancePitch(void);	// ������ƽ��

#endif
