#include "zf_common_headfile.h"

BrushlessType Motor[UES_BRUSHLESS_NUM];

// 电机初始化
void BrushlessInit(void)
{
	ValueType	   Value = {0};
	PulseType	   pulse = {0};
	MotorParamType param = {0};
	MotorLimit	   limit;
	limit.maxRPM	 = 0;	 // 根据需要修改
	limit.maxCurrent = 0;
	for (size_t i = 0; i < UES_BRUSHLESS_NUM; i++) {
		Motor[i].enable	   = false;
		Motor[i].begin	   = false;
		Motor[i].setZero   = false;
		Motor[i].mode	   = RPM;	 // 速度模式
		Motor[i].valueLast = Value;
		Motor[i].valueNow  = Value;
		Motor[i].valueSet  = Value;
		Motor[i].reachTime = 0.f;
		Motor[i].pulse	   = pulse;
		Motor[i].param	   = param;
		Motor[i].limit	   = limit;
		PIDTypeInit(&Motor[i].posPID, 0.f, 0.f, 0.f, PIDINC, Motor[0].limit.maxRPM);	// PID参数待调整
		PIDTypeInit(&Motor[i].rpmPID, 0.f, 0.f, 0.f, PIDINC, Motor[0].limit.maxCurrent);
		PIDTypeInit(&Motor[i].currentPID, 0.f, 0.f, 0.f, PIDINC, 0);
	}
};

// 电机位置置零
void BrushlessSetZero(BrushlessType* motor)
{
	motor->setZero			= false;
	motor->valueNow.angle	= 0.f;
	motor->pulse.pulseLock	= 0;
	motor->pulse.pulseTotal = 0;
};

// 脉冲解算 脉冲 → pos and rpm
void BrushlessCulculate(BrushlessType* motor)
{
	motor->pulse.Distanse = motor->pulse.pulseRead - motor->pulse.pulseLast;	// 计算每次的脉冲数之差，对应每次转过的角度
	motor->pulse.pulseLast = motor->pulse.pulseRead;

	if (ABS(motor->pulse.Distanse) > PULSEPERROUND / 2)	   // 用来判断电机应该正转还是反转，修正distance
	{
		motor->pulse.Distanse = motor->pulse.Distanse - SIG(motor->pulse.Distanse) * PULSEPERROUND;
	}
	motor->pulse.pulseTotal += motor->pulse.Distanse;										  // 累计脉冲
	motor->valueNow.angle	 = motor->pulse.pulseTotal * 360 / PULSEPERROUND;				  // 累计角度
	motor->valueNow.speed	 = (motor->pulse.Distanse * 60) / (PULSEPERROUND * PULSETIME);	  // 速度rpm
	motor->valueLast		 = motor->valueNow;

	if (motor->begin) {	   // 准备锁位置
		motor->pulse.pulseLock = motor->pulse.pulseTotal;
	}
	if (motor->setZero)
		BrushlessSetZero(motor);
};

// 位置模式
void BrushlessPositionMode(BrushlessType* motor)
{
	float setPulseTotal		 = (motor->valueSet.angle * PULSEPERROUND) / 360;

	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float)motor->pulse.pulseTotal, setPulseTotal);
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 速度模式
void BrushlessSpeedMode(BrushlessType* motor)
{
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 电流模式
void BrushlessCurrentMode(BrushlessType* motor)
{
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 锁位置
void BrushlessLockPosition(BrushlessType* motor)
{
	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float)motor->pulse.pulseTotal, (float)motor->pulse.pulseLock);
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 发送电流
void BrushlessSentCurrent(BrushlessType* motor) {
	// TODO motor->currentPID.Output
};

void BrushlessFunc(void)
{
	for (size_t i = 0; i < UES_BRUSHLESS_NUM; i++) {
		if (Motor[i].enable == true) {
			if (Motor[i].begin == true) {
				switch (Motor->mode) {
					case POSITION:
						BrushlessPositionMode(&Motor[i]);
						break;
					case RPM:
						BrushlessSpeedMode(&Motor[i]);
						break;
					case CURRENT:
						BrushlessCurrentMode(&Motor[i]);
						break;

					default:
						break;
				}
			} else {
				BrushlessLockPosition(&Motor[i]);
			}
		}

		BrushlessSentCurrent(&Motor[i]);
	}
};
