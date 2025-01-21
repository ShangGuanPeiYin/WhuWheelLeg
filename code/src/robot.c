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
			robot.jumpLine.Pos[2] = ForwardKinematics(PI, PI * 0);
			// robot.jumpLine.Pos[3] = 0;
			// robot.jumpLine.Pos[4] = 0;
			JumpLineState++;
			break;

		case 1:

			if (RobotDrawLine(robot.jumpLine.Pos[0], 500)) {
				robot.jumpLine.Lerp = true;
				JumpLineState++;
				robot.pipeline.state = StatePreparing;
			}
			break;
		case 2:

			if (RobotDrawLine(robot.jumpLine.Pos[1], 300)) {
				robot.jumpLine.Lerp = true;
				JumpLineState++;
				robot.pipeline.state = StatePreparing;
			}
			break;
		case 3:

			if (RobotDrawLine(robot.jumpLine.Pos[2], 300)) {
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
	PIDTypeInit(&robot.pitchPID, 0.f, 0.f, 0.f, PIDINC, 0);
	PIDTypeInit(&robot.rollPID, 0.f, 0.f, 0.f, PIDINC, 0);
	PIDTypeInit(&robot.yawPID, 0.f, 0.f, 0.f, PIDINC, 0);
};

/**
 * @brief 俯仰角平衡 TODO
 * 		  解算关系式： PitchSet = K1 * ( SpeedSet - SpeedNow )
 * 		            TorqueSet = K2 * ( PitchSet - PitchNow )
 * 		            TorqueSet 即扭矩，对应电机的电流，即电机的PWM
 * 		  注意方向问题！！！
 * 		  目前方向：轮腿站立，从右边看： 顺时针为Speed>0 ,Torque>0。
 * 				  K1和K2 用RobotType里面的	float K1, K2;
 *       机体解算时所用到的角度力矩方向都是顺时针为正（从右侧看,右为轮腿前），
 *
 */
void BalancePitch(void)
{
	// 先读注释，再写
}

/********************************************** 平衡函数TEST ********************************************************** */

/**
 * @brief 平衡环
 *
 * @param Angle
 * @param Gyro
 * @return float
 */
float Balance(float Angle, float Gyro)
{
	int	  Balance_KP = 0, Balance_KD = 0;
	float Angle_bias, Gyro_bias;	// 角度偏差 角速度偏差
	float balance;					// 平衡环Pwm

	Angle_bias = 14 /*经验值，重心位置*/ - Angle;	 // 求出平衡的角度中值和机械相关
	Gyro_bias  = 0 - Gyro;

	Balance_KP = 5000;
	Balance_KD = 1200;
	balance	   = (-Balance_KP / 100 * Angle_bias - Gyro_bias * Balance_KD / 100);	 // 计算平衡控制的电机PWM PD 控制
	return balance;
}

/**
 * @brief 速度环
 *
 * @param encoder_left
 * @param encoder_right
 * @return float
 */
float Velocity(int encoder_left, int encoder_right)
{
	int Velocity_KP = 0, Velocity_KI = 0;

	static float velocity = 0, Encoder_Least = 0, Encoder_bias = 0;
	static float Encoder_Integral = 0;

	Encoder_Least = 0 - (encoder_left + encoder_right);	   // 获取最新速度偏差=目标速度（此处为零）-测量速度（左右编码器之和）
	Encoder_bias	 *= 0.8;							   // 一阶低通滤波器
	Encoder_bias	 += Encoder_Least * 0.2;	// 一阶低通滤波器
	Encoder_Integral += Encoder_bias;			// 积分出位移 积分时间：10ms

	PEAK(Encoder_Integral, 10000);	  // 积分限幅

	velocity = (Encoder_bias * Velocity_KP / 100 + Encoder_Integral * Velocity_KI / 100);	 // 速度PI控制
	return velocity;
}

/**
 * @brief 转向环
 *
 * @param Angle
 * @param Gyro
 * @return float
 */
float Turn(float Angle, float Gyro)
{
	int	  Turn_KP = 0, Turn_KD = 0;
	float Angle_bias, Gyro_bias;	// 角度偏差 角速度偏差
	float turn;						// 平衡环Pwm
	Angle_bias = 0 - Angle;			// 求出平衡的角度中值和机械相关
	Gyro_bias  = 0 - Gyro;
	turn	   = (-Turn_KP / 100 * Angle_bias - Gyro_bias * Turn_KD / 100);	   // 计算平衡控制的电机PWM PD 控制

	return turn;	// 转向环 PWM 右转为正，左转为负
}