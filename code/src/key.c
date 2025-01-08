#include "zf_common_headfile.h"

uint8 keyflag0 = 0, keyflag1 = 0, keyflag2 = 0, keyflag3 = 0;	 // 按键标志位
int	  sanrow = 1;
int	  Rank	 = 1;

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
