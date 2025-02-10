#include "zf_common_headfile.h"

RobotType robot;

/**
 * @brief robot初始化
 *
 * @param robot
 */
void robotInit(RobotType* robot)
{
	memset(robot, 0, sizeof(RobotType));

	robot->left	 = &(legLeft);
	robot->right = &(legRight);

	Start(&(robot->pipeline));
	RobotJumpLineInit();

	// TODO IMU: robot->posture = &( );
	// TODO jumpLine

	robot->param.leftTime  = 0;
	robot->param.rightTime = 0;
	robot->param.PosZero   = ForwardKinematics(PI, 0);

	LegInit();
	BalanceInit();

	// LegReset();	   // 运动到初始零点
};

void RobotJumpLineInit(void)
{
	// TODO
	robot.jumpLine.Pos[0].x = 0;
	robot.jumpLine.Pos[0].y = 0;

	robot.jumpLine.Pos[1].x = 0;
	robot.jumpLine.Pos[1].y = 0;

	robot.jumpLine.Pos[2].x = 0;
	robot.jumpLine.Pos[2].y = 0;

	robot.jumpLine.Pos[3].x = 0;
	robot.jumpLine.Pos[3].y = 0;

	robot.jumpLine.Pos[4].x = 0;
	robot.jumpLine.Pos[4].y = 0;
	;
};

bool RobotDrawLine(Vector2f PosTarget, float reachTime)
{
	// return (LegDrawLine(&legLeft, PosTarget, reachTime) && LegDrawLine(&legRight, PosTarget, reachTime));

	switch (robot.pipeline.state) {
		case StatePreparing:

			robot.param.reachTime  = reachTime;
			robot.param.runTime	   = 0;

			robot.left->PosTarget  = PosTarget;
			robot.right->PosTarget = PosTarget;

			robot.left->PosSet	   = PosTarget;
			robot.right->PosSet	   = PosTarget;

			robot.left->PosStart   = ForwardKinematics(robot.left->angle1Set, robot.left->angle4Set);	 // 现在的坐标
			robot.right->PosStart  = ForwardKinematics(robot.right->angle1Set, robot.right->angle4Set);

			Prepared(&(robot.pipeline));
			break;

		case StateProcessing:

			if (robot.param.runTime < robot.param.reachTime) {
				if (robot.jumpLine.Lerp) {
					robot.left->PosSet.x
						= Lerp(robot.left->PosStart.x, robot.left->PosTarget.x, robot.param.runTime / robot.param.reachTime);
					robot.left->PosSet.y
						= Lerp(robot.left->PosStart.y, robot.left->PosTarget.y, robot.param.runTime / robot.param.reachTime);

					robot.right->PosSet.x
						= Lerp(robot.right->PosStart.x, robot.right->PosTarget.x, robot.param.runTime / robot.param.reachTime);
					robot.right->PosSet.y
						= Lerp(robot.right->PosStart.y, robot.right->PosTarget.y, robot.param.runTime / robot.param.reachTime);
				}

				AngleCalculate(robot.left, robot.left->PosSet);	   // 更新舵机角
				AngleCalculate(robot.right, robot.right->PosSet);

			} else {	// 时间到，运行结束
				Processed(&(robot.pipeline));
			}

			break;

		case StateEnd:
			return true;
	}
	return false;
};

/**
 * @brief 直线跳跃
 *
 * @return true
 * @return false
 */
bool RobotJumpLine(void)
{
	static u8 JumpLineState = 0;

	switch (JumpLineState) {
		case 0:;
			robot.pipeline.state  = StatePreparing;
			robot.jumpLine.Lerp	  = false;	  // 下一阶段是否线性插值

			robot.jumpLine.Pos[0] = ForwardKinematics(PI * (5 / 4.f), PI * (-1 / 4.f));
			robot.jumpLine.Pos[1] = ForwardKinematics(PI * 1 / 2.f, PI * 1 / 2.f);
			robot.jumpLine.Pos[2] = ForwardKinematics(PI * (5 / 4.f), PI * (-1 / 4.f));
			// robot.jumpLine.Pos[3] = 0;
			// robot.jumpLine.Pos[4] = 0;
			JumpLineState++;
			break;

		case 1:

			if (RobotDrawLine(robot.jumpLine.Pos[0], 500)) {
				robot.jumpLine.Lerp = 0;
				JumpLineState++;
				robot.pipeline.state = StatePreparing;
			}
			break;
		case 2:

			if (RobotDrawLine(robot.jumpLine.Pos[1], 800)) {
				robot.jumpLine.Lerp = 0;
				JumpLineState++;
				robot.pipeline.state = StatePreparing;
			}
			break;
		case 3:

			if (RobotDrawLine(robot.jumpLine.Pos[2], 800)) {
				JumpLineState++;
				robot.pipeline.state = StatePreparing;
			}
			break;
		case 4:
			/* code */

			JumpLineState++;
			break;
		case 5:
			/* code */

			JumpLineState++;
			break;

		default:
			/* code */

			JumpLineState = 0XFF;
			// JumpLineState = 0;
			return true;
	}

	oled_show_uint(80, 5, JumpLineState, 3);

	return false;
}

/**
 * @brief 信息发生错误 屏幕上输出error
 *
 */
void RobotError(void)
{
	for (;;)	// 死循环，需要重启
		for (uint16 i = 0; i < 8; i++) { oled_show_string(66, i, "Error_Error_Error"); }
};

/********************************************** 流水线函数 ********************************************************** */

void Start(PipelineType* pipeline)	  // 准备开始
{
	pipeline->state = StatePreparing;
	pipeline->isRun = false;
};

void Prepared(PipelineType* pipeline)	 // 已准备好，进入运行状态
{
	pipeline->state = StateProcessing;
};

void Processed(PipelineType* pipeline)	  // 进行完毕，进入结束状态
{
	pipeline->isRun = false;
	pipeline->state = StateEnd;
}

/********************************************** 平衡函数 ********************************************************** */

/**
 * @brief 平衡初始化
 *
 */
void BalanceInit(void)	  // PID
{
	// TODO：
	float Kp_1 = 0.f;
	float Ki_1 = 0.f;
	float Kd_1 = 0.f;

	float Kp_2 = 62.f;
	float Kd_2 = 20.5f;

	float Kp_3 = 0.f;
	float Kd_3 = 0.f;

	PIDTypeInit(&robot.pitchSpeedPID, Kp_1, Ki_1, Kd_1, PIDPOS, 0);	   // 俯仰PID类型
	PIDTypeInit(&robot.pitchAnglePID, Kp_2, 0.f, Kd_2, PIDPOS, 0);	   // PD控制
	PIDTypeInit(&robot.pitchVecPID, Kp_3, 0.f, Kd_3, PIDPOS, 0);	   // PD控制

	PIDTypeInit(&robot.yawPID, 0.f, 0.f, 0.f, PIDPOS, 0);
	PIDTypeInit(&robot.rollPID, 0.f, 0.f, 0.f, PIDINC, 0);
};

/**
 * @brief  转向环
 *
 */
void BalanceYaw(void)
{
	float turn			= PIDOperation(&robot.yawPID, robot.posture->dataOri.yaw, robot.posture->dataSet.yaw);	  // 平衡环Pwm

	robot.right_Torque += turn;
	robot.left_Torque  -= turn;
}

/**
 * @brief 俯仰角平衡 三环嵌套， 先调外两环
 */
void BalancePitch(void)
{
	robot.speedNow = (Motor[0].valueNow.speed + Motor[1].valueNow.speed) / 2;

	robot.posture->dataSet.pitch = PIDOperation(&robot.pitchSpeedPID, robot.speedNow, robot.speedSet);	  // 直接修改speedSet即可

	robot.posture->dataSet.angle.x = PIDOperation(&robot.pitchAnglePID, robot.posture->dataOri.pitch, robot.posture->dataSet.pitch);

	robot.right_Torque			   = robot.left_Torque
		= PIDOperation(&robot.pitchVecPID, robot.posture->dataOri.angle.x, robot.posture->dataSet.angle.x);

	// robot.right_Torque = robot.left_Torque
	// 	= PIDOperation(&robot.pitchAnglePID, robot.posture->dataOri.pitch, robot.posture->dataSet.pitch);
}

/**
 * @brief 平衡函数
 *
 */
void Balance(void)
{
	BalancePitch();	   // 计算维持平衡的力矩
	BalanceYaw();	   // 再计算转向需要的力矩

	BldcSetCurrent(robot.left_Torque, robot.right_Torque);
}
