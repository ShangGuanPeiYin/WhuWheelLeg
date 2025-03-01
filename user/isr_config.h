#ifndef _isr_config_h
#define _isr_config_h

//======================================================特别注意====================================================
// 中断优先级不能设置为相同值，所有中断优先级都必须设置为不一样的值
//======================================================特别注意====================================================

// ISR_PRIORITY：    TC264具有255个中断优先级可以设置 1-255，0优先级表示不开启中断，255为最高优先级
// INT_SERVICE：     宏定义决定中断由谁处理，也称为服务提供者（在TC264中，中断被叫做服务），可设置范围IfxSrc_Tos_cpu0
// IfxSrc_Tos_cpu1 IfxSrc_Tos_dma  不可设置为其他值 如果INT_SERVICE设置为IfxSrc_Tos_dma的话，ISR_PRIORITY的可设置范围则是0-47。

//================================================PIT中断参数相关定义===============================================
#define CCU6_0_CH0_INT_SERVICE \
	IfxSrc_Tos_cpu0	   // 定义CCU6_0 PIT通道0中断服务类型，即中断是由谁响应处理 IfxSrc_Tos_cpu0 IfxSrc_Tos_cpu1 IfxSrc_Tos_dma
					   // 不可设置为其他值
#define CCU6_0_CH0_ISR_PRIORITY 30	  // 定义CCU6_0 PIT通道0中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

#define CCU6_0_CH1_INT_SERVICE	IfxSrc_Tos_cpu0
#define CCU6_0_CH1_ISR_PRIORITY 31

#define CCU6_1_CH0_INT_SERVICE	IfxSrc_Tos_cpu0
#define CCU6_1_CH0_ISR_PRIORITY 32

#define CCU6_1_CH1_INT_SERVICE	IfxSrc_Tos_cpu0
#define CCU6_1_CH1_ISR_PRIORITY 33

//================================================GPIO中断参数相关定义===============================================
// 通道0与通道4是公用一个中断函数 在中断内部通过标志位判断是谁触发的中断
#define EXTI_CH0_CH4_INT_SERVICE \
	IfxSrc_Tos_cpu0	   // 定义ERU通道0和通道4中断服务类型，即中断是由谁响应处理 IfxSrc_Tos_cpu0 IfxSrc_Tos_cpu1 IfxSrc_Tos_dma
					   // 不可设置为其他值
#define EXTI_CH0_CH4_INT_PRIO 40	// 定义ERU通道0和通道4中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

// 通道1与通道5是公用一个中断函数 在中断内部通过标志位 判断是谁触发的中断
#define EXTI_CH1_CH5_INT_SERVICE IfxSrc_Tos_cpu0	// 定义ERU通道1和通道5中断服务类型，同上
#define EXTI_CH1_CH5_INT_PRIO	 41					// 定义ERU通道1和通道5中断优先级 同上

// 通道2与通道6是公用一个中断函数 在中断内部通过标志位 判断是谁触发的中断
#define EXTI_CH2_CH6_INT_SERVICE IfxSrc_Tos_dma	   // 定义ERU通道2和通道6中断服务类型，同上
#define EXTI_CH2_CH6_INT_PRIO	 5				   // 定义ERU通道2和通道6中断优先级 可设置范围为0-47

// 通道3与通道7是公用一个中断函数 在中断内部通过标志位 判断是谁触发的中断
#define EXTI_CH3_CH7_INT_SERVICE IfxSrc_Tos_cpu0	// 定义ERU通道3和通道7中断服务类型，同上
#define EXTI_CH3_CH7_INT_PRIO	 43					// 定义ERU通道3和通道7中断优先级 同上

//===================================================DMA中断参数相关定义===============================================
#define DMA_INT_SERVICE \
	IfxSrc_Tos_cpu0	   // ERU触发DMA中断服务类型，即中断是由谁响应处理 IfxSrc_Tos_cpu0 IfxSrc_Tos_cpu1 IfxSrc_Tos_dma
					   // 不可设置为其他值
#define DMA_INT_PRIO 60	   // ERU触发DMA中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

//===================================================串口中断参数相关定义===============================================
#define UART0_INT_SERVICE \
	IfxSrc_Tos_cpu0	   // 定义串口0中断服务类型，即中断是由谁响应处理 IfxSrc_Tos_cpu0 IfxSrc_Tos_cpu1 IfxSrc_Tos_dma
					   // 不可设置为其他值
#define UART0_TX_INT_PRIO 11	// 定义串口0发送中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样
#define UART0_RX_INT_PRIO 10	// 定义串口0接收中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样
#define UART0_ER_INT_PRIO 12	// 定义串口0错误中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

#define UART1_INT_SERVICE IfxSrc_Tos_cpu0
#define UART1_TX_INT_PRIO 13
#define UART1_RX_INT_PRIO 14
#define UART1_ER_INT_PRIO 15

#define UART2_INT_SERVICE IfxSrc_Tos_cpu0
#define UART2_TX_INT_PRIO 16
#define UART2_RX_INT_PRIO 17
#define UART2_ER_INT_PRIO 18

#define UART3_INT_SERVICE IfxSrc_Tos_cpu0
#define UART3_TX_INT_PRIO 19
#define UART3_RX_INT_PRIO 20
#define UART3_ER_INT_PRIO 21

#endif
