#include "zf_common_headfile.h"

BldcType Motor[2];

double Stretch_Left = 0, Stretch_Right = 0, Stretch = 0;

// 无刷电机初始化
void BldcInit(void)
{
	Bldc_uart_init();	 // 通讯初始化
	BldcTypeInit();		 // 控制初始化
};

/// @brief 无刷电机结构体初始化
/// @param
void BldcTypeInit(void)
{
	float Kp_rpm		  = 3.5f;	 // PID参数待调整
	float Ki_rpm		  = 0.138f;
	float Kd_rpm		  = 0.f;

	Motor[0].param.direct = Left;	  // 0为左
	Motor[1].param.direct = Right;	  // 1为右

	MotorLimit limit;
	limit.maxRPM	 = 0;	 // 根据需要修改
	limit.maxCurrent = 0;	 // 不在这里限幅

	for (size_t i = 0; i < 2; i++) {
		memset(&Motor[i], 0, sizeof(BldcType));

		Motor[i].enable	   = true;
		Motor[i].begin	   = true;

		Motor[i].setZero   = false;
		Motor[i].mode	   = CURRENT;	 // 力矩模式
		Motor[i].reachTime = 0.f;

		// 增量式PID初始化
		PIDTypeInit(&Motor[i].posPID, 0.f, 0.f, 0.f, PIDINC, Motor[0].limit.maxRPM);	// 位置环还没写
		PIDTypeInit(&Motor[i].rpmPID, Kp_rpm, Ki_rpm, Kd_rpm, PIDINC, Motor[0].limit.maxCurrent);
		PIDTypeInit(&Motor[i].currentPID, 0.f, 0.f, 0.f, PIDINC, 0);	// 电流环用不到
	}

	Motor[0].param.sign = +1;
	Motor[1].param.sign = -1;
};

// 电机位置置零
void BldcSetZero(BldcType* motor)
{
	motor->setZero			= false;
	motor->valueNow.angle	= 0.f;
	motor->pulse.pulseLock	= 0;
	motor->pulse.pulseTotal = 0;
};

/// @brief  脉冲解算 脉冲 → pos
/// @param motor
void BldcCulculate(BldcType* motor)
{
	motor->pulse.Distanse  = motor->pulse.pulseRead - motor->pulse.pulseLast;	 // 计算每次的脉冲数之差，对应每次转过的角度
	motor->pulse.pulseLast = motor->pulse.pulseRead;

	if (ABS(motor->pulse.Distanse) > PULSEPERROUND / 2) {	 // 用来判断电机应该正转还是反转，修正distance
		motor->pulse.Distanse = motor->pulse.Distanse - SIG(motor->pulse.Distanse) * PULSEPERROUND;
	}

	motor->pulse.pulseTotal += motor->pulse.Distanse;	 // 累计脉冲

	motor->valueNow.angle	 = motor->pulse.pulseTotal * 360 / PULSEPERROUND;	 // 累计角度
	// motor->valueNow.speed	 = (motor->pulse.Distanse * 60) / (PULSEPERROUND * PULSETIME);	  // 速度rpm 直接协议读取，无需计算
	motor->valueLast.angle	 = motor->valueNow.angle;

	if (motor->begin) {	   // 准备锁位置
		motor->pulse.pulseLock = motor->pulse.pulseTotal;
	}
	if (motor->setZero)
		BldcSetZero(motor);
};

// 位置模式
void BldcPositionMode(BldcType* motor)
{
	float setPulseTotal		 = (motor->valueSet.angle * PULSEPERROUND) / 360;

	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float) motor->pulse.pulseTotal, setPulseTotal);
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	// PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 速度模式
void BldcSpeedMode(BldcType* motor)
{
	// motor->rpmPID.kp		 = (motor->valueSet.speed - motor->valueNow.speed) * 0.03 + 3;

	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	// PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 电流模式
void BldcCurrentMode(BldcType* motor) {
	// 开环电流控制，此函数为空

	// 电流环的输出是PID的Output
	//  PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 锁位置
void BldcLockPosition(BldcType* motor)
{
	motor->valueSet.speed	 = PIDOperation(&motor->posPID, (float) motor->pulse.pulseTotal, (float) motor->pulse.pulseLock);
	motor->valueSet.current += PIDOperation(&motor->rpmPID, motor->valueNow.speed, motor->valueSet.speed);
	// PIDOperation(&motor->currentPID, motor->valueNow.current, motor->valueSet.current);	   // TODO 不知道能不能写电流环
};

// 发送电流（PWM） 双驱，两个一起
void BldcSentCurrent(void)	  //
{
	// current即PWM 开环电流
	PEAK(Motor[0].valueSet.current, (int16) OUTPUT_DUTY_MAX);
	PEAK(Motor[1].valueSet.current, (int16) OUTPUT_DUTY_MAX);

	Bldc_SetDuty(Motor[0].valueSet.current * Motor[0].param.sign, Motor[1].valueSet.current * Motor[1].param.sign);
	// Bldc_SetDuty_String(Motor[0].valueSet.current * Motor[0].param.sign, Motor[1].valueSet.current * Motor[1].param.sign);
};

/*********************************************** 通讯部分 ************************************************ */

BldcDataType motor_value;	 // 定义通讯参数结构体

/// @brief 无刷驱动 串口接收回调函数。
/// @brief 用于解析接收到的速度数据  该函数需要在对应的串口接收中断中调用
/// @param
void Bldc_Driver_callback(void)
{
	uint8 receive_data;	   // 定义临时变量

	if (uart_query_byte(BLDC_DRIVER_UART, &receive_data))	 // 接收串口数据
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
						// pos cul
						Motor[0].valueLast = Motor[0].valueNow;
						Motor[1].valueLast = Motor[1].valueNow;

						motor_value.receive_left_speed_data
							= (((int) motor_value.receive_data_buffer[2] << 8)
							   | (int) motor_value.receive_data_buffer[3]);	   // 拟合左侧电机转速数据

						motor_value.receive_right_speed_data
							= (((int) motor_value.receive_data_buffer[4] << 8)
							   | (int) motor_value.receive_data_buffer[5]);	   // 拟合右侧电机转速数据

						// pos cul
						Motor[0].valueNow.speed = motor_value.receive_left_speed_data * Motor[0].param.sign;
						Motor[1].valueNow.speed = motor_value.receive_right_speed_data * Motor[1].param.sign;
					} else if (motor_value.receive_data_buffer[1] == 0x04) {
						Motor[0].pulse.pulseRead = (((u16) motor_value.receive_data_buffer[2] << 8)
													| (u16) motor_value.receive_data_buffer[3]);	// 拟合左侧电机

						Motor[1].pulse.pulseRead = (((u16) motor_value.receive_data_buffer[4] << 8)
													| (u16) motor_value.receive_data_buffer[5]);	// 拟合右侧电机

						// 解算位置
						BldcCulculate(&Motor[0]);
						BldcCulculate(&Motor[1]);
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
/// @param left_duty 左侧电机占空比  范围 -4000 ~ 4000  负数为反转
/// @param right_duty 右侧电机占空比  范围 -4000 ~ 4000  负数为反转
void Bldc_SetDuty(int16 left_duty, int16 right_duty)
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

/// @brief 无刷驱动 设置电机占空比
/// @param left_duty 左侧电机占空比  范围 -4000 ~ 4000  负数为反转
/// @param right_duty 右侧电机占空比  范围 -4000 ~ 4000  负数为反转
void Bldc_SetDuty_String(int16 left_duty, int16 right_duty) { printf("SET-DUTY,%d,%d\n", left_duty, right_duty); }

/// @brief 无刷驱动 获取速度信息
/// @brief 仅需发送一次 驱动将周期发出速度信息(默认10ms)
/// @param
void Bldc_AskSpeed(void)
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

/// @brief 无刷驱动 获取速度信息
/// @brief 仅需发送一次 驱动将周期发出速度信息(默认10ms)
/// @param
void Bldc_AskSpeed_String(void) { printf("GET-SPEED\n"); }

/// @brief  无刷驱动通讯 参数初始化
/// @param
void BldcData_init(void)
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
void Bldc_uart_init(void)
{
	uart_init(BLDC_DRIVER_UART, BLDC_DRIVER_BAUDRATE, BLDC_DRIVER_TX, BLDC_DRIVER_RX);	  // 串口初始化
	uart_rx_interrupt(BLDC_DRIVER_UART, 1);												  // 使能串口接收中断

	BldcData_init();	   // 结构体参数初始化
	Bldc_SetDuty(0, 0);	   // 设置0占空比
						   //	Bldc_SetDuty_String(0, 0);
	Bldc_AskSpeed();	   // 获取实时速度数据
						   //	Bldc_AskSpeed_String();
};

/*********************************************** 通讯部分 ************************************************ */
// 设置函数
void BldcSetCurrent(float leftCur, float rightCur)
{
	Motor[0].mode			  = CURRENT;
	Motor[1].mode			  = CURRENT;

	Motor[0].valueSet.current = leftCur;
	Motor[1].valueSet.current = rightCur;
};

void BldcSetSpeed(float leftSpeed, float rightSpeed)
{
	Motor[0].mode			= RPM;
	Motor[1].mode			= RPM;

	Motor[0].valueSet.speed = leftSpeed;
	Motor[1].valueSet.speed = rightSpeed;
};

void BldcSetPos(float leftPos, float rightPos)
{
	Motor[0].valueSet.angle = leftPos;
	Motor[1].valueSet.angle = rightPos;
};

/// @brief Func
/// @param
void BldcFunc(void)
{
	for (size_t i = 0; i < 2; i++) {
		if (Motor[i].enable == true) {
			if (Motor[i].begin == true) {
				switch (Motor->mode) {
					case POSITION:
						BldcPositionMode(&Motor[i]);
						break;
					case RPM:
						BldcSpeedMode(&Motor[i]);
						break;
					case CURRENT:
						BldcCurrentMode(&Motor[i]);	   // 常用
						break;

					default:
						break;
				}
			} else {
				// BldcLockPosition(&Motor[i]);//TODO
			}
		}
	}

	BldcSentCurrent();
};
