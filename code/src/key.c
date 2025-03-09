#include "zf_common_headfile.h"

uint8 keyflag0 = 0, keyflag1 = 0, keyflag2 = 0, keyflag3 = 0;	 // ������־λ
int	  sanrow = 1;
int	  Rank	 = 1;

void KeyInit(void)
{
	gpio_init(KEY_UP, GPI, 0, GPI_PULL_UP);	   // ������ʼ��
	gpio_init(KEY_DOWN, GPI, 0, GPI_PULL_UP);
	gpio_init(KEY_LEFT, GPI, 0, GPI_PULL_UP);
	gpio_init(KEY_RIGHT, GPI, 0, GPI_PULL_UP);
}

/// @brief
/// @param
/// @return
int OLED_Key_Scan(void)
{
	if (keyflag0 == 1 || keyflag1 == 1 || keyflag2 == 1 || keyflag3 == 1) {
		system_delay_ms(200);
		keyflag0 = 0;
		keyflag1 = 0;
		keyflag2 = 0;
		keyflag3 = 0;
	}

	if (gpio_get_level(KEY_LEFT) == 0 && keyflag0 == 0) {
		keyflag0 = 1;
		return 1;
	}

	if (gpio_get_level(KEY_DOWN) == 0 && keyflag1 == 0) {
		keyflag1 = 1;
		return 2;
	}

	if (gpio_get_level(KEY_UP) == 0 && keyflag2 == 0) {
		keyflag2 = 1;
		return 3;
	}

	if (gpio_get_level(KEY_RIGHT) == 0 && keyflag3 == 0) {
		keyflag3 = 1;
		return 4;
	}
	return 0;
}

// TODO: TOTEST
#if 0

// ���尴������ֵ
typedef enum {
	KEY_NONE  = 0,	  // �ް���������
	KEY_LEFT  = 1,	  // ���������
	KEY_DOWN  = 2,	  // �¼�������
	KEY_UP	  = 3,	  // �ϼ�������
	KEY_RIGHT = 4	  // �Ҽ�������
} KeyType;

// ���尴����־λ
#define KEY_FLAG_LEFT  (1 << 0)	   // �����־λ
#define KEY_FLAG_DOWN  (1 << 1)	   // �¼���־λ
#define KEY_FLAG_UP	   (1 << 2)	   // �ϼ���־λ
#define KEY_FLAG_RIGHT (1 << 3)	   // �Ҽ���־λ

// ������־λ���������ڼ�¼��Щ�����Ѿ�����⵽
static uint8_t key_flags = 0;

// ��ʱ����������ȥ������
void system_delay_ms(uint32_t ms);

// �������ʹ�����
// ������
// - pin: ������Ӧ��GPIO����
// - flag: �����ı�־λ
// - key_type: ��������
// ����ֵ��
// - ���������������δ����ǣ��򷵻ض�Ӧ�İ�������
// - ���򷵻�KEY_NONE
static KeyType check_key(int pin, uint8_t flag, KeyType key_type)
{
	if (gpio_get_level(pin) == 0 && (key_flags & flag) == 0) {
		key_flags |= flag;	  // ��Ǹð����ѱ���⵽
		return key_type;	  // ���ذ�������
	}
	return KEY_NONE;	// �ް���������
}

// OLED����ɨ�躯��
// ����ֵ��
// - ���ر����µİ������ͣ�KEY_LEFT, KEY_DOWN, KEY_UP, KEY_RIGHT��
// - ����ް��������£�����KEY_NONE
int OLED_Key_Scan(void)
{
	// ȥ������
	// ������κΰ�����־λ�����ã���ʾ�а���������
	if (key_flags != 0) {
		system_delay_ms(200);	 // ��ʱ200���룬������������
		key_flags = 0;			 // �������а�����־λ
	}

	// ����������
	KeyType key = KEY_NONE;										   // ��ʼ����������Ϊ�ް���������
	key			= check_key(KEY_LEFT, KEY_FLAG_LEFT, KEY_LEFT);	   // ������
	if (key != KEY_NONE)
		return key;	   // �����������£������������

	key = check_key(KEY_DOWN, KEY_FLAG_DOWN, KEY_DOWN);	   // ����¼�
	if (key != KEY_NONE)
		return key;	   // ����¼������£������¼�����

	key = check_key(KEY_UP, KEY_FLAG_UP, KEY_UP);	 // ����ϼ�
	if (key != KEY_NONE)
		return key;	   // ����ϼ������£������ϼ�����

	key = check_key(KEY_RIGHT, KEY_FLAG_RIGHT, KEY_RIGHT);	  // ����Ҽ�
	if (key != KEY_NONE)
		return key;	   // ����Ҽ������£������Ҽ�����

	return KEY_NONE;	// ����ް��������£�����KEY_NONE
}

#endif