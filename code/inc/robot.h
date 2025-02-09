#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "Pid.h"
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
	bool	 Lerp;	  // �Ƿ������Բ�ֵ
} JumpLineType;

typedef struct _robot {
	PipelineType pipeline;

	LegType* left;
	LegType* right;

	IMUType* posture;

	ParamType	 param;
	JumpLineType jumpLine;

	PIDType rollPID, yawPID;							  // ƽ��PID
	PIDType pitchSpeedPID, pitchAnglePID, pitchVecPID;	  // �ٶȻ����ǶȻ������ٶȻ� ����ƽ��PID

	float left_Torque, right_Torque;
	float speedNow, speedSet;	 // �����ٶȣ������ٶȾ�ֵ

	// TODO: CameraType

} RobotType;

extern RobotType robot;

void robotInit(RobotType* robot);

void robotRun(void);
bool RobotDrawLine(Vector2f PosTarget, float reachTime);
void robotDrawCurve(void);
bool RobotJumpLine(void);
void RobotJumpLineInit(void);

void RobotError(void);

void Start(PipelineType* pipeline);		   // ���״̬��ˮ�����п�ʼ����
void Prepared(PipelineType* pipeline);	   // ��׼����
void Processed(PipelineType* pipeline);	   // �ѽ�����

void BalanceInit(void);		// PID
void BalanceYaw(void);		// ƫ���ǣ�ת��
void BalanceRoll(void);		// �����ƽ�� TODO
void BalancePitch(void);	// ������ƽ�� TODO
void Balance(void);

#endif
