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

	robot->robotParam.leftTime	= 0;
	robot->robotParam.rightTime = 0;
	robot->robotParam.PosZero	= ForwardKinematics(PI, 0);

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
	return (LegDrawLine(&legLeft, PosTarget, reachTime) && LegDrawLine(&legRight, PosTarget, reachTime));
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
 * @brief ��Ϣ�������� ��Ļ�����error
 *
 */
void RobotError(void)
{
	for (;;)	// ��ѭ������Ҫ����
		for (uint16 i = 0; i < 8; i++) { oled_show_string(66, i, "Error_Error_Error"); }
};

/********************************************** ƽ�� ********************************************************** */

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
 * @brief ������ƽ�� TODO
 * 		  �����ϵʽ�� PitchSet = K1 * ( SpeedSet - SpeedNow )
 * 		            TorqueSet = K2 * ( PitchSet - PitchNow )
 * 		            TorqueSet ��Ť�أ���Ӧ����ĵ������������PWM
 * 		  ע�ⷽ�����⣡���� Torque�ķ���һ����PWM������
 * 		  Ŀǰ��������վ�������ұ߿��� ˳ʱ��ΪSpeed>0 ,Torque>0��
 * 				  K1��K2 ��RobotType�����	float K1, K2;
 *
 */
void BalancePitch(void)
{
	// �ȶ�ע�ͣ���д
	;
	;
}