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

	PIDType pitchSpeedPID, pitchAnglePID, pitchVecPID;	  //ƽ���ٶȻ����ǶȻ������ٶȻ� ����ƽ��PID
	PIDType YawVecPID,YawTorPID;						  //ת����ٶȻ������ػ�
	
	float left_Torque, right_Torque;
	float speedNow, speedSet;	 // �����ٶȣ������ٶȾ�ֵ

	// TODO: CameraType
	Vector2f ZeroPoint;

} RobotType;
extern int jump_flag;
extern RobotType robot;
extern float	 tiaocan[9];
extern float	 YawCtrlOut;

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
void BalancePitch(void);	// ������ƽ��
void Balance(void);

#endif
