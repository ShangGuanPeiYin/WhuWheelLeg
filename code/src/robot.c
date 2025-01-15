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

	// robot->posture = &( );

	robot->robotParam.leftTime	= 0;
	robot->robotParam.rightTime = 0;

	LegInit();
};

/************************** ��ˮ�ߺ��� ************************************** */

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
