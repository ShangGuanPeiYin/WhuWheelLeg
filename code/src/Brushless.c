#include "zf_common_headfile.h"

BrushlessType Motor[UES_BRUSHLESS_NUM];

// �����ʼ��
void BrushlessInit(void)
{
	ValueType	   Value = {0};
	PulseType	   pulse = {0};
	MotorParamType param = {0};
	MotorLimit	   limit;
	limit.maxRPM	 = 0;	 // ������Ҫ�޸�
	limit.maxCurrent = 0;
	for (size_t i = 0; i < UES_BRUSHLESS_NUM; i++) {
		Motor[i].enable	   = false;
		Motor[i].begin	   = false;
		Motor[i].setZero   = false;
		Motor[i].mode	   = RPM;	 // �ٶ�ģʽ
		Motor[i].valueLast = Value;
		Motor[i].valueNow  = Value;
		Motor[i].valueSet  = Value;
		Motor[i].reachTime = 0.f;
		Motor[i].pulse	   = pulse;
		Motor[i].param	   = param;
		Motor[i].limit	   = limit;
		PIDTypeInit(&Motor[i].posPID, 0.f, 0.f, 0.f, PIDINC, Motor[0].limit.maxRPM);	// PID����������
		PIDTypeInit(&Motor[i].rpmPID, 0.f, 0.f, 0.f, PIDINC, Motor[0].limit.maxCurrent);
		PIDTypeInit(&Motor[i].currentPID, 0.f, 0.f, 0.f, PIDINC, 0);
	}
};

// ���λ������
void BrushlessSetZero(BrushlessType* motor)
{
	motor->setZero			= false;
	motor->valueNow.angle	= 0.f;
	motor->pulse.pulseLock	= 0;
	motor->pulse.pulseTotal = 0;
};

// ������� ���� �� pos and rpm
void BrushlessCulculate(BrushlessType* motor)
{
	motor->pulse.Distanse = motor->pulse.pulseRead - motor->pulse.pulseLast;	// ����ÿ�ε�������֮���Ӧÿ��ת���ĽǶ�
	motor->pulse.pulseLast = motor->pulse.pulseRead;

	if (ABS(motor->pulse.Distanse) > PULSEPERROUND / 2)	   // �����жϵ��Ӧ����ת���Ƿ�ת������distance
	{
		motor->pulse.Distanse = motor->pulse.Distanse - SIG(motor->pulse.Distanse) * PULSEPERROUND;
	}
	motor->pulse.pulseTotal += motor->pulse.Distanse;										  // �ۼ�����
	motor->valueNow.angle	 = motor->pulse.pulseTotal * 360 / PULSEPERROUND;				  // �ۼƽǶ�
	motor->valueNow.speed	 = (motor->pulse.Distanse * 60) / (PULSEPERROUND * PULSETIME);	  // �ٶ�rpm
	motor->valueLast		 = motor->valueNow;

	if (motor->begin) {	   // ׼����λ��
		motor->pulse.pulseLock = motor->pulse.pulseTotal;
	}
	if (motor->setZero)
		BrushlessSetZero(motor);
};

// λ��ģʽ
void BrushlessPositionMode(BrushlessType* motor)
{
	float setPulseTotal		 = (motor->valueSet.angle * PULSEPERROUND) / 360;

	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float)motor->pulse.pulseTotal, setPulseTotal);
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO ��֪���ܲ���д������
};

// �ٶ�ģʽ
void BrushlessSpeedMode(BrushlessType* motor)
{
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO ��֪���ܲ���д������
};

// ����ģʽ
void BrushlessCurrentMode(BrushlessType* motor)
{
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO ��֪���ܲ���д������
};

// ��λ��
void BrushlessLockPosition(BrushlessType* motor)
{
	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float)motor->pulse.pulseTotal, (float)motor->pulse.pulseLock);
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO ��֪���ܲ���д������
};

// ���͵���
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
