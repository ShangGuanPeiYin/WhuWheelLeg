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

/// @brief  脉冲解算 脉冲 → pos and rpm 这个函数应该用不到了
/// @param motor
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

	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float) motor->pulse.pulseTotal, setPulseTotal);
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
	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float) motor->pulse.pulseTotal, (float) motor->pulse.pulseLock);
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

/*********************************** 底层控制，移植逐飞 ************************************************** */

BrushlessDataType motor_value;	  // 定义通讯参数结构体

/// @brief 无刷驱动 串口接收回调函数。用于解析接收到的速度数据  该函数需要在对应的串口接收中断中调用
/// @param
void BrushlessDriver_callback(void)
{
	uint8 receive_data;	   // 定义临时变量

	if (uart_query_byte(SMALL_DRIVER_UART, &receive_data))	  // 接收串口数据
	{
		if (receive_data == 0xA5
			&& motor_value.receive_data_buffer[0] != 0xA5)	  // 判断是否收到帧头 并且 当前接收内容中是否正确包含帧头
		{
			motor_value.receive_data_count = 0;	   // 未收到帧头或者未正确包含帧头则重新接收
		}

		motor_value.receive_data_buffer[motor_value.receive_data_count++] = receive_data;	 // 保存串口数据

		if (motor_value.receive_data_count >= 7)	// 判断是否接收到指定数量的数据
		{
			if (motor_value.receive_data_buffer[0] == 0xA5)	   // 判断帧头是否正确
			{
				motor_value.sum_check_data = 0;	   // 清除校验位数据

				for (int i = 0; i < 6; i++) {
					motor_value.sum_check_data += motor_value.receive_data_buffer[i];	 // 重新计算校验位
				}

				if (motor_value.sum_check_data == motor_value.receive_data_buffer[6])	 // 校验数据准确性
				{
					if (motor_value.receive_data_buffer[1] == 0x02)	   // 判断是否正确接收到 速度输出 功能字
					{
						motor_value.receive_left_speed_data
							= (((int) motor_value.receive_data_buffer[2] << 8)
							   | (int) motor_value.receive_data_buffer[3]);	   // 拟合左侧电机转速数据

						motor_value.receive_right_speed_data
							= (((int) motor_value.receive_data_buffer[4] << 8)
							   | (int) motor_value.receive_data_buffer[5]);	   // 拟合右侧电机转速数据
					}

					motor_value.receive_data_count = 0;	   // 清除缓冲区计数值

					memset(motor_value.receive_data_buffer, 0, 7);	  // 清除缓冲区数据
				} else {
					motor_value.receive_data_count = 0;	   // 清除缓冲区计数值

					memset(motor_value.receive_data_buffer, 0, 7);	  // 清除缓冲区数据
				}
			} else {
				motor_value.receive_data_count = 0;	   // 清除缓冲区计数值

				memset(motor_value.receive_data_buffer, 0, 7);	  // 清除缓冲区数据
			}
		}
	}
}

/// @brief 无刷驱动 设置电机占空比
/// @param left_duty 左侧电机占空比  范围 -10000 ~ 10000  负数为反转
/// @param right_duty 右侧电机占空比  范围 -10000 ~ 10000  负数为反转
void small_driver_set_duty(int16 left_duty, int16 right_duty)
{
	motor_value.send_data_buffer[0] = 0xA5;									   // 配置帧头
	motor_value.send_data_buffer[1] = 0X01;									   // 配置功能字
	motor_value.send_data_buffer[2] = (uint8) ((left_duty & 0xFF00) >> 8);	   // 拆分 左侧占空比 的高八位
	motor_value.send_data_buffer[3] = (uint8) (left_duty & 0x00FF);			   // 拆分 左侧占空比 的低八位
	motor_value.send_data_buffer[4] = (uint8) ((right_duty & 0xFF00) >> 8);	   // 拆分 右侧占空比 的高八位
	motor_value.send_data_buffer[5] = (uint8) (right_duty & 0x00FF);		   // 拆分 右侧占空比 的低八位
	motor_value.send_data_buffer[6] = 0;									   // 和校验清除

	for (int i = 0; i < 6; i++) {
		motor_value.send_data_buffer[6] += motor_value.send_data_buffer[i];	   // 计算校验位
	}

	uart_write_buffer(UART_3, motor_value.send_data_buffer, 7);	   // 发送设置占空比的 字节包 数据
}

/// @brief 无刷驱动 获取速度信息
/// @brief 仅需发送一次 驱动将周期发出速度信息(默认10ms)
/// @param
void Brushless_askSpeed(void)
{
	motor_value.send_data_buffer[0] = 0xA5;	   // 配置帧头
	motor_value.send_data_buffer[1] = 0x02;	   // 配置功能字
	motor_value.send_data_buffer[2] = 0x00;	   // 数据位清空
	motor_value.send_data_buffer[3] = 0x00;	   // 数据位清空
	motor_value.send_data_buffer[4] = 0x00;	   // 数据位清空
	motor_value.send_data_buffer[5] = 0x00;	   // 数据位清空
	motor_value.send_data_buffer[6] = 0xA7;	   // 配置校验位

	uart_write_buffer(UART_3, motor_value.send_data_buffer, 7);	   // 发送获取转速数据的 字节包 数据
}

/// @brief  无刷驱动通讯 参数初始化
/// @param
void BrushlessData_init(void)
{
	memset(motor_value.send_data_buffer, 0, 7);		  // 清除缓冲区数据
	memset(motor_value.receive_data_buffer, 0, 7);	  // 清除缓冲区数据
	motor_value.receive_data_count		 = 0;
	motor_value.sum_check_data			 = 0;
	motor_value.receive_right_speed_data = 0;
	motor_value.receive_left_speed_data	 = 0;
}

/// @brief 无刷驱动 串口通讯初始化
/// @param
void Brushless_uart_init(void)
{
	uart_init(SMALL_DRIVER_UART, SMALL_DRIVER_BAUDRATE, SMALL_DRIVER_RX, SMALL_DRIVER_TX);	  // 串口初始化
	uart_rx_interrupt(SMALL_DRIVER_UART, 1);												  // 使能串口接收中断

	BrushlessData_init();			// 结构体参数初始化
	small_driver_set_duty(0, 0);	// 设置0占空比
	Brushless_askSpeed();			// 获取实时速度数据
}
