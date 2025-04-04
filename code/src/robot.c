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
bool RobotJumpLine(void)
{
	static u8 JumpLineState = 0;

	switch (JumpLineState) {
		case 0:;
			robot.pipeline.state  = StatePreparing;
			robot.jumpLine.Lerp	  = false;	  // ��һ�׶��Ƿ����Բ�ֵ

			robot.jumpLine.Pos[0] = ForwardKinematics(PI, 0.f);
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
static PIDType speed_balance_zsc;

void BalanceInit(void)	  // PID
{
	// TODO��
	float Kp_1 = 0.016f;
	float Ki_1 = 0.f;
	float Kd_1 = 0.015f;//0.006f;

//    float Kp_1 = 0.f            ;
//    float Ki_1 = 0.00016f;
//    float Kd_1 = 0.f;//0.006f;

//	float Kp_2 = 30.f;	  // 62.f;
//	float Kd_2 = 36.f;	  // 20.5f;

    float Kp_2 =25.f;    // 62.f;
    float Kd_2 = -28.f;    // 20.5f;

	float Kp_3 = 9.6;	 // 15;//18
	float Ki_3 = 0.f;
	float Kd_3 = 12.3;	 //.6;

	PIDTypeInit(&robot.pitchSpeedPID, Kp_1, Ki_1, Kd_1, PIDPOS, 0);	   // ����PID����
	PIDTypeInit(&robot.pitchAnglePID, Kp_2, 0.f, Kd_2, PIDPOS, 0);	   // PD����
	PIDTypeInit(&robot.pitchVecPID, Kp_3, Ki_3, Kd_3, PIDPOS, 0);	   // PD����

	PIDTypeInit(&robot.yawPID, 180.f, 0.f, 100.f, PIDPOS, 0);
	PIDTypeInit(&robot.rollPID, 0.f, 0.f, 0.f, PIDINC, 0);

    PIDTypeInit(&speed_balance_zsc, 5.f, 0.f, 0.f, PIDPOS, 0);
};

const float RobotWidth = 155.f;	   // mm
/**
 * @brief ���ȸ�ƽ�⣩�����ƽ�� �Ӻ���ǰ��˳ʱ��Ϊ��
 *
 */
void		BalanceRoll(void)
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

float YawCtrlOut = 0;
/**
 * @brief  ת��
 *
 */
void  BalanceYaw(void)
{

	robot.right_Torque += YawCtrlOut;	 // ���ٶ�
	robot.left_Torque  -= YawCtrlOut;
}

/**
 * @brief  ���ٻ�
 *
 */
void  BalanceSpeed(void)
{
    robot.right_Torque += PIDOperation(&speed_balance_zsc, robot.speedNow, robot.speedSet);//b_speed_p*(robot.speedSet-robot.speedNow);    // ���ٶ�
    robot.left_Torque  += PIDOperation(&speed_balance_zsc, robot.speedNow, robot.speedSet);//b_speed_p*(robot.speedSet-robot.speedNow);
}

/**
 * @brief ������ƽ�� ����Ƕ�ף� �ȵ�������
 */
void BalancePitch(void)
{
	robot.speedSet =0;

	// robot->posture=&IMUdata;
	robot.speedNow = -(Motor[0].valueNow.speed + Motor[1].valueNow.speed) / 2;

	robot.posture->dataSet.pitch = PIDOperation(&robot.pitchSpeedPID, robot.speedNow, robot.speedSet);//+robot.posture->dataSet.pitch;	  // ֱ���޸�speedSet����


	//robot.posture->dataSet.pitch=LimitBoth_float(robot.posture->dataSet.pitch,-8,16);

	robot.posture->dataSet.angle.x = PIDOperation(&robot.pitchAnglePID, -IMUdata.dataOri.pitch, robot.posture->dataSet.pitch);

	robot.right_Torque			   = PIDOperation(&robot.pitchVecPID, -IMUdata.dataOri.angle.x, robot.posture->dataSet.angle.x);
	robot.left_Torque			   = robot.right_Torque;
}
float zsc_angle_error;
float Stand_P=45000;
float Stand_D=1260;
float Stand_DD=0;//9000
static float Angle_Gyro_Y_v_1=0;
void Angle_Control(void)
{

    float fP,fD,fDD;
    float MPS,MD,MDD;

    robot.speedSet =200;

    // robot->posture=&IMUdata;
    robot.speedNow = -(Motor[0].valueNow.speed + Motor[1].valueNow.speed) / 2;

    robot.posture->dataSet.pitch = PIDOperation(&robot.pitchSpeedPID, robot.speedNow, robot.speedSet);//+robot.posture->dataSet.pitch;    // ֱ���޸�speedSet����
    robot.posture->dataSet.pitch = LimitBoth_float(robot.posture->dataSet.pitch,-6,12);
//robot.posture->dataSet.pitch
    fP = Stand_P/100.0;
    fD = (Stand_D)/100.0 ;
    fDD= Stand_DD/100.0;

    //PID ����
    MPS=  (LimitBoth_float(IMUdata.dataOri.pitch+robot.speedSet*0.02,-15,15))   * fP;         //�ٶȿ��Ƽ���Ƕȿ��� P
    MD =   LimitBoth_float(IMUdata.dataOri.angle.x,-500,500) * fD;                      //�Ƕȿ���D
    MDD= (IMUdata.dataOri.angle.x - Angle_Gyro_Y_v_1) * fDD;  // �Ƕȿ���DD
    Angle_Gyro_Y_v_1=IMUdata.dataOri.angle.x;
    //�Ƕȿ��Ƶ�PID�㷨
    //MDD=LimitBoth_float(MDD,-1000,1000);
    robot.right_Torque =  (MPS+MD+MDD);
    robot.left_Torque =  robot.right_Torque+0;
    //Angle_Control_Out=Limit_Float(Angle_Control_Out,-10000,10000) ;


    zsc_angle_error=robot.posture->dataSet.pitch*5;

    Servo[Fl].angleLeg=180+zsc_angle_error;
    Servo[Fr].angleLeg=180+zsc_angle_error;
    Servo[Bl].angleLeg=zsc_angle_error;
    Servo[Br].angleLeg=zsc_angle_error;
}

/**
 * @brief ƽ�⺯��
 *
 */
void Balance(void)
{
	//BalancePitch();	   // ����ά��ƽ�������
    Angle_Control();
	//BalanceSpeed();//�����ٶ���Ҫ������
	BalanceYaw();	   // �ټ���ת����Ҫ������

//	if (StopFlag == 1) {
//		robot.right_Torque = 0;
//		robot.left_Torque  = 0;
//	}
	BldcSetCurrent(robot.left_Torque, robot.right_Torque);
}
