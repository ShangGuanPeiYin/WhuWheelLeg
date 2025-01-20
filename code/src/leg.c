#include "zf_common_headfile.h"

LegType legLeft;
LegType legRight;

void LegInit(void)
{
	memset(&legLeft, 0, sizeof(LegType));
	memset(&legRight, 0, sizeof(LegType));

	legLeft.num		= Left;
	legRight.num	= Right;

	legLeft.front	= &(Servo[Fl]);
	legLeft.behind	= &(Servo[Bl]);
	legLeft.wheel	= &(Motor[0]);

	legRight.front	= &(Servo[Fr]);
	legRight.behind = &(Servo[Br]);
	legRight.wheel	= &(Motor[1]);

	MotionInit(&(legLeft.motion));
	MotionInit(&(legRight.motion));

	legLeft.RunTime	 = &(robot.robotParam.leftTime);
	legRight.RunTime = &(robot.robotParam.rightTime);
}

/**
 * @brief 足端画曲线 默认一次
 *
 * @param leg
 */
bool LegDrawCurve(LegType* leg, float reachTime)
{
	switch (robot.pipeline.state) {
		case StatePreparing:
			leg->reachTime = reachTime;

			/* code */

			Prepared(&(robot.pipeline));
			break;

		case StateProcessing:;
			uint64_t runTime = *(leg->RunTime);
			if (runTime < leg->reachTime) {
				leg->PosSet = BezierCalculate(leg->motion.degree, leg->motion.CtrlPoint, runTime / leg->reachTime);
			} else {
				Processed(&(robot.pipeline));
			}

			AngleCalculate(leg, leg->PosSet);	 // 更新舵机角
			break;

		case StateEnd:

			/* code */

			return true;
	}
	return false;
};

/**
 * @brief 足端走直线，线性插值
 *
 * @param leg
 * @param PosTarget
 * @param reachTime
 */
bool LegDrawLine(LegType* leg, Vector2f PosTarget, float reachTime)
{
	switch (robot.pipeline.state) {
		case StatePreparing:
			leg->reachTime	= reachTime;
			leg->PosTarget	= PosTarget;
			leg->PosStart	= ForwardKinematics(leg->angle1Set, leg->angle4Set);	// 现在的坐标

			*(leg->RunTime) = 0;	// 时间清零

			Prepared(&(robot.pipeline));

			break;

		case StateProcessing:;
			uint64_t runTime = *(leg->RunTime);
			if (runTime < leg->reachTime) {
				// Start + (target - start)*(runtime/reachtime)
				leg->PosSet.x = Lerp(leg->PosStart.x, leg->PosTarget.x, runTime / leg->reachTime);
				leg->PosSet.y = Lerp(leg->PosStart.y, leg->PosTarget.y, runTime / leg->reachTime);

				AngleCalculate(leg, leg->PosSet);	 // 更新舵机角

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
 * @brief 从Pos向下解算至 Servo.angleLeg 单个腿解算 调用此函数即可移动至目标位置
 *
 * @param leg
 */
void AngleCalculate(LegType* leg, Vector2f pos)
{
	// if (PointLimit(&pos)) {
	Vector2f angleleg = InverseKinematics(pos);	   // PosSet  ->  angle1,4
	leg->angle1Set	  = angleleg.x;
	leg->angle4Set	  = angleleg.y;

	AngleLeg2Servo(leg);

	// } else {
	// 	RobotError();
	// };
};

/**
 * @brief angle14换算到Servo
 *
 * @param leg
 */
void AngleLeg2Servo(LegType* leg)
{
	switch (leg->num) {
		case Left:
			Servo[Fl].angleLeg = leg->angle1Set * RAD2DEG;
			Servo[Bl].angleLeg = leg->angle4Set * RAD2DEG;
			break;

		case Right:
			Servo[Fr].angleLeg = leg->angle1Set * RAD2DEG;
			Servo[Br].angleLeg = leg->angle4Set * RAD2DEG;
			break;

		default:
			break;
	};
};

/**
 * @brief
 *
 * @param point 五连杆坐标限制范围，防止输入的坐标不合理，要求能够构成五边形
 * 使用： if(PointLimit(point))
 * @return true 无误
 * @return false 有误
 */
bool PointLimit(Vector2f* point)
{
	Vector2f pointA;
	Vector2f pointE;

	pointA.y = pointE.y = 0;
	pointA.x = pointE.x	 = L5 / 2;
	pointA.x			*= -1;

	float MaxLength		 = L1 + L2;
	float MminLength	 = L2 - L1;

	float length1		 = Vector2fMagnitude(Vector2fSub(*point, pointA));	  // 计算到AE的模
	float length2		 = Vector2fMagnitude(Vector2fSub(*point, pointE));

	// 要求二者同时在min-max
	float MinMag		 = MIN(length1, length2);
	float MaxMag		 = MAX(length1, length2);

	if (MinMag >= MaxLength || MaxMag <= MminLength) {
		// TODO 改变Point至合理范围内

		return false;
	} else {
		return true;
	}
};

/**
 * @brief  逆解。（x，y），求∠1和4
 *
 * @param point 输入C点坐标
 * @return Vector2f 返回弧度
 */
Vector2f InverseKinematics(Vector2f point)
{
	Vector2f angle;				// 利用二维向量储存angle1和4 对应xy
	Vector2f pointA, pointE;	// AE坐标不变

	pointA.x = -L5 / 2;
	pointA.y = 0.f;

	pointE.x = L5 / 2;
	pointE.y = 0.f;

	// 求Angle1
	float A	 = (point.x - pointA.x) * (point.x - pointA.x) + (point.y - pointA.y) * (point.y - pointA.y) + L1 * L1 - L2 * L2;
	float B	 = -2 * (point.x - pointA.x) * L1;
	float C	 = -2 * (point.y - pointA.y) * L1;

	angle.x	 = 2 * atan2f((-C + sqrtf(C * C + B * B - A * A)), (A - B));
	if (angle.x < 0)	// 限定在0-2PI
		angle.x += 2 * PI;

	// 求Angle4 镜像求解
	A		= (point.x - pointE.x) * (point.x - pointE.x) + (point.y - pointE.y) * (point.y - pointE.y) + L4 * L4 - L3 * L3;
	B		= 2 * (point.x - pointE.x) * L4;
	C		= -2 * (point.y - pointE.y) * L4;
	angle.y = 2 * atan2f((-C + sqrtf(C * C + B * B - A * A)), (A - B));	   //
	angle.y = PI - angle.y;
	while (angle.y > 2 * PI) { angle.y -= 2 * PI; }

	return angle;
};

/**
 * @brief 正解。∠1和4，求（x，y）
 *
 * @param angle1  弧度
 * @param angle4 弧度
 * @return Vector2f C点坐标
 */
Vector2f ForwardKinematics(float angle1, float angle4)
{
	// 直接计算ABDE的坐标
	Vector2f pointA, pointB, pointD, pointE;
	pointA.x	 = -L5 / 2;
	pointA.y	 = 0.f;

	pointB.x	 = -L5 / 2 + L1 * cosf(angle1);
	pointB.y	 = L1 * sinf(angle1);

	pointD.x	 = L5 / 2 + L4 * cosf(angle4);
	pointD.y	 = L4 * sinf(angle4);

	pointE.x	 = L5 / 2;
	pointE.y	 = 0.f;

	// 求解angle2
	float A		 = 2 * L2 * (pointD.x - pointB.x);
	float B		 = 2 * L2 * (pointD.y - pointB.y);
	float LBD_2	 = (pointD.y - pointB.y) * (pointD.y - pointB.y) + (pointD.x - pointB.x) * (pointD.x - pointB.x);
	float C		 = L2 * L2 - L3 * L3 + LBD_2;

	float angle2 = 2 * atan2f((B + sqrtf(A * A + B * B - C * C)), (A + C));

	// 计算C点坐标
	Vector2f pointC;
	pointC.x = -L5 / 2 + L1 * cosf(angle1) + L2 * cosf(angle2);
	pointC.y = L1 * sinf(angle1) + L2 * sinf(angle2);
	return pointC;
};

/**
 * @brief 直接归零
 *
 */
void LegReset(void)
{
	Vector2f point0 = ForwardKinematics(PI, 0);

	legLeft.PosSet	= point0;
	legRight.PosSet = point0;

	AngleCalculate(&legLeft, legLeft.PosSet);	 // 解算
	AngleCalculate(&legRight, legRight.PosSet);
	// TODO：需要线性差值 增加时间戳，不然无法判断是否到位
};
