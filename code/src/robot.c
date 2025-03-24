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

	robot->posture		   = &(IMUdata);
	// TODO jumpLine

	robot->param.leftTime  = 0;
	robot->param.rightTime = 0;
	robot->param.PosZero   = ForwardKinematics(PI, 0);
	robot->left->PosSet	   = robot->param.PosZero;
	robot->right->PosSet   = robot->param.PosZero;

	LegInit();
	BalanceInit();

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
int jump_flag =0;
bool RobotJumpLine(void)
{

	static u8 JumpLineState = 0;

	switch (JumpLineState) {
		case 0:
			robot.pipeline.state  = StatePreparing;
			robot.jumpLine.Lerp	  = true;	  // ��һ�׶��Ƿ����Բ�ֵ

			robot.jumpLine.Pos[0] = ForwardKinematics(PI, 0.f);
			robot.jumpLine.Pos[1] = ForwardKinematics(PI * 3 / 4.f, PI * 1 / 4.f);
			robot.jumpLine.Pos[2] = ForwardKinematics(PI,0.f);
			// robot.jumpLine.Pos[3] = 0;
			// robot.jumpLine.Pos[4] = 0;
			JumpLineState++;
			break;

		case 1:

			if (RobotDrawLine(robot.jumpLine.Pos[0], 50)) {
				robot.jumpLine.Lerp = 0;
				JumpLineState++;
				robot.pipeline.state = StatePreparing;
			}
			break;
		case 2:
		    jump_flag =1;
			if (RobotDrawLine(robot.jumpLine.Pos[1], 100)) {
				robot.jumpLine.Lerp = 0;
				JumpLineState++;
				robot.pipeline.state = StatePreparing;
			}
			break;
		case 3:

			if (RobotDrawLine(robot.jumpLine.Pos[2], 50)) {
				JumpLineState++;
				robot.pipeline.state = StatePreparing;

			    jump_flag =0;
			}
			break;
		case 4:
			/* code */

			JumpLineState++;
			break;
		default:
			/* code */

			JumpLineState = 0XFF;
			// JumpLineState = 0;
			return true;
	}

	// oled_show_uint(80, 5, JumpLineState, 3);

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
float tiaocan[9];

/********************************************** ƽ�⺯�� ********************************************************** */

/**
 * @brief ƽ���ʼ��
 *
 */
void BalanceInit(void)	  // PID
{
	float Kp_1 = 0.086f;
	float Ki_1 = 0.f;
	float Kd_1 = -0.04f;

	float Kp_2 = 30.f;	  // 62.f;
	float Kd_2 = 35.f;	  // 20.5f;

	float Kp_3 = 8.7;	 // 15;
	float Ki_3 = 0.f;
	float Kd_3 = 10.5;	 //.6;

	PIDTypeInit(&robot.pitchSpeedPID, Kp_1, Ki_1, Kd_1, PIDPOS, 0);	   // ����PID����
	PIDTypeInit(&robot.pitchAnglePID, Kp_2, 0.f, Kd_2, PIDPOS, 0);	   // PD����
	PIDTypeInit(&robot.pitchVecPID, Kp_3, Ki_3, Kd_3, PIDPOS, 0);	   // PD����

	PIDTypeInit(&robot.YawVecPID, 0.f, 0.f, 0.f, PIDPOS, 0);
	PIDTypeInit(&robot.YawTorPID, 0.f, 0.f, 0.f, PIDINC, 0);
};


const float RobotWidth = 155.f;	   // mm
/**
 * @brief ���ȸ�ƽ�⣩�����ƽ�� �Ӻ���ǰ��˳ʱ��Ϊ��
 *
 */
void BalanceRoll(void)
{
#if 1	 // ƽ�����һ

	static float roll_Kp   = 1.f;	 // ת��ϵ��
	float		 rollOut   = roll_Kp * 0.5f * RobotWidth * sinf(IMUdata.dataOri.roll);

	robot.right->PosSet.y += rollOut;
	robot.left->PosSet.y  -= rollOut;

	float ZeroY			   = robot.param.PosZero.y;

#else	 // ƽ����Զ�
	static float roll	   = 0.f;
	static float Roll_Kp   = 0.1f;	  // ת��ϵ��

	roll				  += Roll_Kp * (0 - IMUdata.dataOri.roll);	  // ��������һ��PID������

	float rollOut		   = 0.5f * RobotWidth * sinf(roll);	// ϵ����������
	robot.right->PosSet.y  = robot.param.PosZero.y + rollOut;
	robot.left->PosSet.y   = robot.param.PosZero.y - rollOut;	 // �����д����

#endif

	// ��������λ�ã�ȷ�������� PosZero.y
	robot.right->PosSet.y = fmax(robot.right->PosSet.y, ZeroY);
	robot.left->PosSet.y  = fmax(robot.left->PosSet.y, ZeroY);

	// ��������ڣ��򽵵�����
	if (robot.right->PosSet.y > ZeroY && robot.left->PosSet.y > ZeroY) {
		float delta			   = MIN(robot.right->PosSet.y, robot.left->PosSet.y) - ZeroY;
		robot.right->PosSet.y -= delta;
		robot.left->PosSet.y  -= delta;
	}

	AngleCalculate(robot.left, robot.left->PosSet);	   // ���¶����
	AngleCalculate(robot.right, robot.right->PosSet);
};

float YawVecOut = 0;
float YawTorOut = 0;
/**
 * @brief  ת��
 *�⻷�����Ƕ�->���ٶ�
 *�ڻ������ٶ�->����
 */
void BalanceYaw(void)
{
	float LeftSpeedNow = rpmToMmPerSec(Motor[0].valueNow.speed);
	float RightSpeedNow = rpmToMmPerSec(Motor[1].valueNow.speed);
	float RealYawVec = (LeftSpeedNow - RightSpeedNow)/RobotWidth;
	//YawVecOut = PIDOperation(&robot.YawVecPID, RealWarp, 0.f);	 			// ת����ٶ�
	
	YawTorOut = PIDOperation(&robot.YawTorPID, RealYawVec, YawTorOut);	 	// ת������
	robot.right_Torque -= YawTorOut;
	robot.left_Torque  += YawTorOut;
}

/**
 * @brief ������ƽ�� ����Ƕ��
 */
void BalancePitch(void)
{
	robot.speedSet = 0;
	// robot->posture=&IMUdata;
	robot.speedNow = -(Motor[0].valueNow.speed + Motor[1].valueNow.speed) / 2;
	robot.posture->dataSet.pitch = PIDOperation(&robot.pitchSpeedPID, robot.speedNow, robot.speedSet);	  // ֱ���޸�speedSet����
	robot.posture->dataSet.pitch = LimitBoth_float(robot.posture->dataSet.pitch, -8, 35);
	robot.posture->dataSet.angle.x = PIDOperation(&robot.pitchAnglePID, -IMUdata.dataOri.pitch, robot.posture->dataSet.pitch);
	robot.right_Torque			   = PIDOperation(&robot.pitchVecPID, -IMUdata.dataOri.angle.x, robot.posture->dataSet.angle.x);
	robot.left_Torque			   = robot.right_Torque;
}

/**
 * @brief ƽ�⺯��
 *
 */
void Balance(void)
{
	BalancePitch();	   // ����ά��ƽ�������
	BalanceYaw();	   // �ټ���ת����Ҫ������

	// if (StopFlag == 1) {
	// 	robot.right_Torque = 0;
	// 	robot.left_Torque  = 0;
	// }

	BldcSetCurrent(robot.left_Torque, robot.right_Torque);
}
