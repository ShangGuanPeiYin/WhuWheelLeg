#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "Pid.h"
#include "zf_common_typedef.h"

// 工作状态
enum StateEnum {
	StatePreparing,		// 准备中
	StateProcessing,	// 进行中
	StateEnd,			// 结束
};

// 工作状态流水线，复杂动作会用到
typedef struct _Pipeline {
	bool		   isRun;	 // 正在运行
	enum StateEnum state;
} PipelineType;

typedef struct _JumpLineType {
	Vector2f Pos[5];
	float	 reachTime[5];
	bool	 Lerp;	  // 是否用线性插值
} JumpLineType;

typedef struct _robot {
	PipelineType pipeline;

	LegType* left;
	LegType* right;

	IMUType* posture;

	ParamType	 param;
	JumpLineType jumpLine;

	PIDType rollPID, yawPID;							  // 平衡PID
	PIDType pitchSpeedPID, pitchAnglePID, pitchVecPID;	  // 速度环，角度环，角速度环 俯仰平衡PID

	float left_Torque, right_Torque;
	float speedNow, speedSet;	 // 机身速度，左右速度均值

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

void Start(PipelineType* pipeline);		   // 令该状态流水线运行开始运行
void Prepared(PipelineType* pipeline);	   // 已准备好
void Processed(PipelineType* pipeline);	   // 已进行完

void BalanceInit(void);		// PID
void BalanceYaw(void);		// 偏航角，转向环
void BalanceRoll(void);		// 横滚角平衡 TODO
void BalancePitch(void);	// 俯仰角平衡 TODO
void Balance(void);

#endif
