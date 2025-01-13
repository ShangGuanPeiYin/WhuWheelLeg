#ifndef CODE_KEY_H_
#define CODE_KEY_H_
#include "zf_common_typedef.h"

#define KEY_UP	  P22_1	   // P22_2
#define KEY_DOWN  P22_2
#define KEY_LEFT  P22_3	   // P22_3
#define KEY_RIGHT P22_0

#define KEY_U gpio_get_level(KEY_UP)
#define KEY_D gpio_get_level(KEY_DOWN)
#define KEY_L gpio_get_level(KEY_LEFT)
#define KEY_R gpio_get_level(KEY_RIGHT)

extern uint8 keyflag0, keyflag1, keyflag2, keyflag3;
extern int	 sanrow;
extern int	 Rank;

int	 OLED_Key_Scan(void);
void KeyInit();

#endif /* CODE_KEY_H_ */
