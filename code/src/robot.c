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

	robot->robotParam.leftTime	= 0;
	robot->robotParam.rightTime = 0;
	robot->robotParam.PosZero	= ForwardKinematics(PI, 0);

	LegInit();

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
	return (LegDrawLine(&legLeft, PosTarget, reachTime) && LegDrawLine(&legRight, PosTarget, reachTime));
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

			Vector2f PosTarget0 = ForwardKinematics(PI, PI * 0);
			if (RobotDrawLine(PosTarget0, 800))
				JumpLineState++;
			break;

		case 1:;
			Vector2f PosTarget1 = ForwardKinematics(PI * 1 / 2, PI * 1 / 2);
			if (RobotDrawLine(PosTarget1, 800))
				JumpLineState++;
			break;
		case 2:;
			Vector2f PosTarget2 = ForwardKinematics(PI, PI * 0);
			if (RobotDrawLine(PosTarget2, 800))
				JumpLineState++;
			break;
		case 3:
			//			if (RobotDrawLine(robot.jumpLine.Pos[3], 100))
			JumpLineState++;
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
			return true;
	}
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

/********************************************** 平衡 ********************************************************** */

/**
 * @brief 平衡初始化
 *
 */
void BalanceInit(void)	  // PID
{
	// TODO：
	PIDTypeInit(&robot.pitchPID, 0.f, 0.f, 0.f, PIDINC, 0);
	PIDTypeInit(&robot.rollPID, 0.f, 0.f, 0.f, PIDINC, 0);
	PIDTypeInit(&robot.yawPID, 0.f, 0.f, 0.f, PIDINC, 0);
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
 * @brief 俯仰角平衡 TODO
 * 		  解算关系式： PitchSet = K1 * ( SpeedSet - SpeedNow )
 * 		            TorqueSet = K2 * ( PitchSet - PitchNow )
 * 		            TorqueSet 即扭矩，对应电机的电流，即电机的PWM
 * 		  注意方向问题！！！ Torque的方向不一定是PWM的正向
 * 		  目前方向：轮腿站立，从右边看： 顺时针为Speed>0 ,Torque>0。
 * 				  K1和K2 用RobotType里面的	float K1, K2;
 *
 */
void BalancePitch(void)
{
	// 先读注释，再写
	;
	;
}