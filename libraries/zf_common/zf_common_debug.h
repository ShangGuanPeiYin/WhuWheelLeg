#ifndef _zf_common_debug_h_
#define _zf_common_debug_h_

#include "zf_common_interrupt.h"
#include "zf_common_typedef.h"

#define DEBUG_UART_INDEX		 (UART_2)			 // ָ�� debug uart ��ʹ�õĵĴ���
#define DEBUG_UART_BAUDRATE		 (460800)			 // ָ�� debug uart ��ʹ�õĵĴ��ڲ�����
#define DEBUG_UART_TX_PIN		 (UART2_TX_P10_5)	 // ָ�� debug uart ��ʹ�õĵĴ�������
#define DEBUG_UART_RX_PIN		 (UART2_RX_P10_6)	 // ָ�� debug uart ��ʹ�õĵĴ�������
#define DEBUG_UART_USE_INTERRUPT (1)				 // �Ƿ����� debug uart �����ж�

//-------------------------------------------------------------------------------------------------------------------
// �������     ����
// ����˵��     x           �ж��Ƿ񴥷����� 0-�������� 1-����������
// ���ز���     void
// ʹ��ʾ��     zf_assert(0);
// ��ע��Ϣ     һ�����ڲ����ж� zf_assert(0) �Ͷ��Ա���
//             Ĭ������»��� Debug UART ���
//             �����ʹ�ÿ�Դ������Ļ�ӿڳ�ʼ������Ļ �������Ļ����ʾ
//-------------------------------------------------------------------------------------------------------------------
#define zf_assert(x)   (debug_assert_handler((x), __FILE__, __LINE__))	  // ���� һ�����ڲ����ж� zf_assert(0) �Ͷ��Ա���
//-------------------------------------------------------------------------------------------------------------------
// �������     Log ��Ϣ���
// ����˵��     x           �ж��Ƿ񴥷���� 0-������� 1-���������
// ����˵��     *str        ��Ҫ����� Log ��Ϣ
// ���ز���     void
// ʹ��ʾ��     zf_log(0, "Error");
// ��ע��Ϣ     ������Ϣ��� ������һЩ������߾���֮������
//             Ĭ������»��� Debug UART ���
//             �����ʹ�ÿ�Դ������Ļ�ӿڳ�ʼ������Ļ �������Ļ����ʾ
//-------------------------------------------------------------------------------------------------------------------
#define zf_log(x, str) (debug_log_handler((x), (str), __FILE__, __LINE__))	  // ������Ϣ��� ������һЩ������߾���֮������

//-------------------------------------------------------------------------------------------------------------------
// �������     CPU����ӹ�
// ���ز���     void
// ��ע��Ϣ     ������CPU����ʱ��ͨ��log��Ϣ����������û�
//-------------------------------------------------------------------------------------------------------------------
#define IFX_CFG_CPU_TRAP_BE_HOOK(x)                                                                         \
	zf_log(0, "Memory access failure or Use an uninitialized peripheral, Locate faults through debugging"); \
	assert_interrupt_config();                                                                              \
	while (1);
#define IFX_CFG_CPU_TRAP_IPE_HOOK(x)                                         \
	zf_log(0, "Accessing an null address, Locate faults through debugging"); \
	assert_interrupt_config();                                               \
	while (1);
#define IFX_CFG_CPU_TRAP_ASSERT_HOOK(x)                                \
	zf_log(0, "Cpu Assertion error, Locate faults through debugging"); \
	assert_interrupt_config();                                         \
	while (1);
#define IFX_CFG_CPU_TRAP_CME_HOOK(x)                                        \
	zf_log(0, "Context management error, Locate faults through debugging"); \
	assert_interrupt_config();                                              \
	while (1);
#define IFX_CFG_CPU_TRAP_IE_HOOK(x)                                  \
	zf_log(0, "Instruction Error, Locate faults through debugging"); \
	assert_interrupt_config();                                       \
	while (1);
#define IFX_CFG_CPU_TRAP_MME_HOOK(x)                                       \
	zf_log(0, "Memory management error, Locate faults through debugging"); \
	assert_interrupt_config();                                             \
	while (1);

typedef struct {
	uint16 type_index;

	uint16 display_x_max;
	uint16 display_y_max;

	uint8 font_x_size;
	uint8 font_y_size;

	void (*output_uart)(const char* str);
	void (*output_screen)(uint16 x, uint16 y, const char* str);
	void (*output_screen_clear)(void);
} debug_output_struct;

#if DEBUG_UART_USE_INTERRUPT		  // ������� debug uart �����ж�
#define DEBUG_RING_BUFFER_LEN (64)	  // ���廷�λ�������С Ĭ�� 64byte
void   debug_interrupr_handler(void);
uint32 debug_read_ring_buffer(uint8* buff, uint32 len);
#endif

uint32 debug_send_buffer(const uint8* buff, uint32 len);	// ���Դ��ڻ���������
void   debug_assert_enable(void);
void   debug_assert_disable(void);
void   debug_assert_handler(uint8 pass, char* file, int line);
void   debug_log_handler(uint8 pass, char* str, char* file, int line);
void   debug_output_struct_init(debug_output_struct* info);
void   debug_output_init(debug_output_struct* info);
void   debug_init(void);

#endif
