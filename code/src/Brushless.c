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

/// @brief  ������� ���� �� pos and rpm �������Ӧ���ò�����
/// @param motor
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

	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float) motor->pulse.pulseTotal, setPulseTotal);
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
	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float) motor->pulse.pulseTotal, (float) motor->pulse.pulseLock);
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

/*********************************** �ײ���ƣ���ֲ��� ************************************************** */

BrushlessDataType motor_value;	  // ����ͨѶ�����ṹ��

/// @brief ��ˢ���� ���ڽ��ջص����������ڽ������յ����ٶ�����  �ú�����Ҫ�ڶ�Ӧ�Ĵ��ڽ����ж��е���
/// @param
void BrushlessDriver_callback(void)
{
	uint8 receive_data;	   // ������ʱ����

	if (uart_query_byte(SMALL_DRIVER_UART, &receive_data))	  // ���մ�������
	{
		if (receive_data == 0xA5
			&& motor_value.receive_data_buffer[0] != 0xA5)	  // �ж��Ƿ��յ�֡ͷ ���� ��ǰ�����������Ƿ���ȷ����֡ͷ
		{
			motor_value.receive_data_count = 0;	   // δ�յ�֡ͷ����δ��ȷ����֡ͷ�����½���
		}

		motor_value.receive_data_buffer[motor_value.receive_data_count++] = receive_data;	 // ���洮������

		if (motor_value.receive_data_count >= 7)	// �ж��Ƿ���յ�ָ������������
		{
			if (motor_value.receive_data_buffer[0] == 0xA5)	   // �ж�֡ͷ�Ƿ���ȷ
			{
				motor_value.sum_check_data = 0;	   // ���У��λ����

				for (int i = 0; i < 6; i++) {
					motor_value.sum_check_data += motor_value.receive_data_buffer[i];	 // ���¼���У��λ
				}

				if (motor_value.sum_check_data == motor_value.receive_data_buffer[6])	 // У������׼ȷ��
				{
					if (motor_value.receive_data_buffer[1] == 0x02)	   // �ж��Ƿ���ȷ���յ� �ٶ���� ������
					{
						motor_value.receive_left_speed_data
							= (((int) motor_value.receive_data_buffer[2] << 8)
							   | (int) motor_value.receive_data_buffer[3]);	   // ��������ת������

						motor_value.receive_right_speed_data
							= (((int) motor_value.receive_data_buffer[4] << 8)
							   | (int) motor_value.receive_data_buffer[5]);	   // ����Ҳ���ת������
					}

					motor_value.receive_data_count = 0;	   // �������������ֵ

					memset(motor_value.receive_data_buffer, 0, 7);	  // �������������
				} else {
					motor_value.receive_data_count = 0;	   // �������������ֵ

					memset(motor_value.receive_data_buffer, 0, 7);	  // �������������
				}
			} else {
				motor_value.receive_data_count = 0;	   // �������������ֵ

				memset(motor_value.receive_data_buffer, 0, 7);	  // �������������
			}
		}
	}
}

/// @brief ��ˢ���� ���õ��ռ�ձ�
/// @param left_duty �����ռ�ձ�  ��Χ -10000 ~ 10000  ����Ϊ��ת
/// @param right_duty �Ҳ���ռ�ձ�  ��Χ -10000 ~ 10000  ����Ϊ��ת
void small_driver_set_duty(int16 left_duty, int16 right_duty)
{
	motor_value.send_data_buffer[0] = 0xA5;									   // ����֡ͷ
	motor_value.send_data_buffer[1] = 0X01;									   // ���ù�����
	motor_value.send_data_buffer[2] = (uint8) ((left_duty & 0xFF00) >> 8);	   // ��� ���ռ�ձ� �ĸ߰�λ
	motor_value.send_data_buffer[3] = (uint8) (left_duty & 0x00FF);			   // ��� ���ռ�ձ� �ĵͰ�λ
	motor_value.send_data_buffer[4] = (uint8) ((right_duty & 0xFF00) >> 8);	   // ��� �Ҳ�ռ�ձ� �ĸ߰�λ
	motor_value.send_data_buffer[5] = (uint8) (right_duty & 0x00FF);		   // ��� �Ҳ�ռ�ձ� �ĵͰ�λ
	motor_value.send_data_buffer[6] = 0;									   // ��У�����

	for (int i = 0; i < 6; i++) {
		motor_value.send_data_buffer[6] += motor_value.send_data_buffer[i];	   // ����У��λ
	}

	uart_write_buffer(UART_3, motor_value.send_data_buffer, 7);	   // ��������ռ�ձȵ� �ֽڰ� ����
}

/// @brief ��ˢ���� ��ȡ�ٶ���Ϣ
/// @brief ���跢��һ�� ���������ڷ����ٶ���Ϣ(Ĭ��10ms)
/// @param
void Brushless_askSpeed(void)
{
	motor_value.send_data_buffer[0] = 0xA5;	   // ����֡ͷ
	motor_value.send_data_buffer[1] = 0x02;	   // ���ù�����
	motor_value.send_data_buffer[2] = 0x00;	   // ����λ���
	motor_value.send_data_buffer[3] = 0x00;	   // ����λ���
	motor_value.send_data_buffer[4] = 0x00;	   // ����λ���
	motor_value.send_data_buffer[5] = 0x00;	   // ����λ���
	motor_value.send_data_buffer[6] = 0xA7;	   // ����У��λ

	uart_write_buffer(UART_3, motor_value.send_data_buffer, 7);	   // ���ͻ�ȡת�����ݵ� �ֽڰ� ����
}

/// @brief  ��ˢ����ͨѶ ������ʼ��
/// @param
void BrushlessData_init(void)
{
	memset(motor_value.send_data_buffer, 0, 7);		  // �������������
	memset(motor_value.receive_data_buffer, 0, 7);	  // �������������
	motor_value.receive_data_count		 = 0;
	motor_value.sum_check_data			 = 0;
	motor_value.receive_right_speed_data = 0;
	motor_value.receive_left_speed_data	 = 0;
}

/// @brief ��ˢ���� ����ͨѶ��ʼ��
/// @param
void Brushless_uart_init(void)
{
	uart_init(SMALL_DRIVER_UART, SMALL_DRIVER_BAUDRATE, SMALL_DRIVER_RX, SMALL_DRIVER_TX);	  // ���ڳ�ʼ��
	uart_rx_interrupt(SMALL_DRIVER_UART, 1);												  // ʹ�ܴ��ڽ����ж�

	BrushlessData_init();			// �ṹ�������ʼ��
	small_driver_set_duty(0, 0);	// ����0ռ�ձ�
	Brushless_askSpeed();			// ��ȡʵʱ�ٶ�����
}
