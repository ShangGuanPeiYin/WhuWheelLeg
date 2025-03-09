#include "zf_common_headfile.h"

uint8 keyflag0 = 0, keyflag1 = 0, keyflag2 = 0, keyflag3 = 0;	 // 按键标志位
int	  sanrow = 1;
int	  Rank	 = 1;

void KeyInit(void)
{
	gpio_init(KEY_UP, GPI, 0, GPI_PULL_UP);	   // 按键初始化
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

// 定义按键返回值
typedef enum {
	KEY_NONE  = 0,	  // 无按键被按下
	KEY_LEFT  = 1,	  // 左键被按下
	KEY_DOWN  = 2,	  // 下键被按下
	KEY_UP	  = 3,	  // 上键被按下
	KEY_RIGHT = 4	  // 右键被按下
} KeyType;

// 定义按键标志位
#define KEY_FLAG_LEFT  (1 << 0)	   // 左键标志位
#define KEY_FLAG_DOWN  (1 << 1)	   // 下键标志位
#define KEY_FLAG_UP	   (1 << 2)	   // 上键标志位
#define KEY_FLAG_RIGHT (1 << 3)	   // 右键标志位

// 按键标志位变量，用于记录哪些按键已经被检测到
static uint8_t key_flags = 0;

// 延时函数，用于去抖处理
void system_delay_ms(uint32_t ms);

// 按键检测和处理函数
// 参数：
// - pin: 按键对应的GPIO引脚
// - flag: 按键的标志位
// - key_type: 按键类型
// 返回值：
// - 如果按键被按下且未被标记，则返回对应的按键类型
// - 否则返回KEY_NONE
static KeyType check_key(int pin, uint8_t flag, KeyType key_type)
{
	if (gpio_get_level(pin) == 0 && (key_flags & flag) == 0) {
		key_flags |= flag;	  // 标记该按键已被检测到
		return key_type;	  // 返回按键类型
	}
	return KEY_NONE;	// 无按键被按下
}

// OLED按键扫描函数
// 返回值：
// - 返回被按下的按键类型（KEY_LEFT, KEY_DOWN, KEY_UP, KEY_RIGHT）
// - 如果无按键被按下，返回KEY_NONE
int OLED_Key_Scan(void)
{
	// 去抖处理
	// 如果有任何按键标志位被设置，表示有按键被按下
	if (key_flags != 0) {
		system_delay_ms(200);	 // 延时200毫秒，消除按键抖动
		key_flags = 0;			 // 重置所有按键标志位
	}

	// 检测各个按键
	KeyType key = KEY_NONE;										   // 初始化按键类型为无按键被按下
	key			= check_key(KEY_LEFT, KEY_FLAG_LEFT, KEY_LEFT);	   // 检测左键
	if (key != KEY_NONE)
		return key;	   // 如果左键被按下，返回左键类型

	key = check_key(KEY_DOWN, KEY_FLAG_DOWN, KEY_DOWN);	   // 检测下键
	if (key != KEY_NONE)
		return key;	   // 如果下键被按下，返回下键类型

	key = check_key(KEY_UP, KEY_FLAG_UP, KEY_UP);	 // 检测上键
	if (key != KEY_NONE)
		return key;	   // 如果上键被按下，返回上键类型

	key = check_key(KEY_RIGHT, KEY_FLAG_RIGHT, KEY_RIGHT);	  // 检测右键
	if (key != KEY_NONE)
		return key;	   // 如果右键被按下，返回右键类型

	return KEY_NONE;	// 如果无按键被按下，返回KEY_NONE
}

#endif