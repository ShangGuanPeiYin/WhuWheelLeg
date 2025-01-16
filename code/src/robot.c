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

	// TODO IMU: robot->posture = &( );
	// TODO jumpLine

	robot->robotParam.leftTime	= 0;
	robot->robotParam.rightTime = 0;

	LegInit();

	LegReset();	   // �˶�����ʼ���
};

bool RobotDrawLine(Vector2f PosTarget, float reachTime)
{
	if (LegDrawLine(&legLeft, PosTarget, reachTime) && LegDrawLine(&legRight, PosTarget, reachTime)) {
		return true;
	} else
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
		case 0:
			if (RobotDrawLine(robot.jumpLine.Pos, robot.jumpLine.reachTime))
				JumpLineState++;
			break;

		case 1:
			/* code */
			break;
		case 2:
			/* code */
			break;
		case 3:
			/* code */
			break;
		case 4:
			/* code */
			break;
		case 5:
			/* code */
			break;
		case 6:
			/* code */
			break;
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
