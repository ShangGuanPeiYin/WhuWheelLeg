#include "zf_common_headfile.h"

RobotType robot;

/************************** 流水线函数 ************************************** */

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
