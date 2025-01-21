#include "zf_common_headfile.h"

RobotType robot;

/**
 * @brief robot��ʼ��
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

	// LegReset();	   // �˶�����ʼ���
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

			robot.left->PosStart   = ForwardKinematics(robot.left->angle1Set, robot.left->angle4Set);	 // ���ڵ�����
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

				AngleCalculate(robot.left, robot.left->PosSet);	   // ���¶����
				AngleCalculate(robot.right, robot.right->PosSet);

			} else {	// ʱ�䵽�����н���
				Processed(&(robot.pipeline));
			}

			break;

		case StateEnd:
			return true;
	}
	return false;
};

/**
 * @brief ֱ����Ծ
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
			robot.jumpLine.Lerp	  = false;	  // ��һ�׶��Ƿ����Բ�ֵ

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
 * @brief ��Ϣ�������� ��Ļ�����error
 *
 */
void RobotError(void)
{
	for (;;)	// ��ѭ������Ҫ����
		for (uint16 i = 0; i < 8; i++) { oled_show_string(66, i, "Error_Error_Error"); }
};

/********************************************** ��ˮ�ߺ��� ********************************************************** */

void Start(PipelineType* pipeline)	  // ׼����ʼ
{
	pipeline->state = StatePreparing;
	pipeline->isRun = false;
};

void Prepared(PipelineType* pipeline)	 // ��׼���ã���������״̬
{
	pipeline->state = StateProcessing;
};

void Processed(PipelineType* pipeline)	  // ������ϣ��������״̬
{
	pipeline->isRun = false;
	pipeline->state = StateEnd;
}

/********************************************** ƽ�⺯�� ********************************************************** */

/**
 * @brief ƽ���ʼ��
 *
 */
void BalanceInit(void)	  // PID
{
	// TODO��
	PIDTypeInit(&robot.pitchPID, 0.f, 0.f, 0.f, PIDINC, 0);
	PIDTypeInit(&robot.rollPID, 0.f, 0.f, 0.f, PIDINC, 0);
	PIDTypeInit(&robot.yawPID, 0.f, 0.f, 0.f, PIDINC, 0);
};

/**
 * @brief ������ƽ�� TODO
 * 		  �����ϵʽ�� PitchSet = K1 * ( SpeedSet - SpeedNow )
 * 		            TorqueSet = K2 * ( PitchSet - PitchNow )
 * 		            TorqueSet ��Ť�أ���Ӧ����ĵ������������PWM
 * 		  ע�ⷽ�����⣡����
 * 		  Ŀǰ��������վ�������ұ߿��� ˳ʱ��ΪSpeed>0 ,Torque>0��
 * 				  K1��K2 ��RobotType�����	float K1, K2;
 *       �������ʱ���õ��ĽǶ����ط�����˳ʱ��Ϊ�������Ҳ࿴,��Ϊ����ǰ����
 *
 */
void BalancePitch(void)
{
	// �ȶ�ע�ͣ���д
}

/********************************************** ƽ�⺯��TEST ********************************************************** */

/**
 * @brief ƽ�⻷
 *
 * @param Angle
 * @param Gyro
 * @return float
 */
float Balance(float Angle, float Gyro)
{
	int	  Balance_KP = 0, Balance_KD = 0;
	float Angle_bias, Gyro_bias;	// �Ƕ�ƫ�� ���ٶ�ƫ��
	float balance;					// ƽ�⻷Pwm

	Angle_bias = 14 /*����ֵ������λ��*/ - Angle;	 // ���ƽ��ĽǶ���ֵ�ͻ�е���
	Gyro_bias  = 0 - Gyro;

	Balance_KP = 5000;
	Balance_KD = 1200;
	balance	   = (-Balance_KP / 100 * Angle_bias - Gyro_bias * Balance_KD / 100);	 // ����ƽ����Ƶĵ��PWM PD ����
	return balance;
}

/**
 * @brief �ٶȻ�
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

	Encoder_Least = 0 - (encoder_left + encoder_right);	   // ��ȡ�����ٶ�ƫ��=Ŀ���ٶȣ��˴�Ϊ�㣩-�����ٶȣ����ұ�����֮�ͣ�
	Encoder_bias	 *= 0.8;							   // һ�׵�ͨ�˲���
	Encoder_bias	 += Encoder_Least * 0.2;	// һ�׵�ͨ�˲���
	Encoder_Integral += Encoder_bias;			// ���ֳ�λ�� ����ʱ�䣺10ms

	PEAK(Encoder_Integral, 10000);	  // �����޷�

	velocity = (Encoder_bias * Velocity_KP / 100 + Encoder_Integral * Velocity_KI / 100);	 // �ٶ�PI����
	return velocity;
}

/**
 * @brief ת��
 *
 * @param Angle
 * @param Gyro
 * @return float
 */
float Turn(float Angle, float Gyro)
{
	int	  Turn_KP = 0, Turn_KD = 0;
	float Angle_bias, Gyro_bias;	// �Ƕ�ƫ�� ���ٶ�ƫ��
	float turn;						// ƽ�⻷Pwm
	Angle_bias = 0 - Angle;			// ���ƽ��ĽǶ���ֵ�ͻ�е���
	Gyro_bias  = 0 - Gyro;
	turn	   = (-Turn_KP / 100 * Angle_bias - Gyro_bias * Turn_KD / 100);	   // ����ƽ����Ƶĵ��PWM PD ����

	return turn;	// ת�� PWM ��תΪ������תΪ��
}