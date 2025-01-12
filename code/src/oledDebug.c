#include "zf_common_headfile.h"

extern float angletemp;
extern float reachTimeTemp;

/**
 * @brief OLED屏幕调试函数，对代码进行调试
 *
 */
void OLedDebug(void)
{
#if 1	 // 舵机测试
	OLED_Key_Scan();

	if (keyflag1 == 1)	  // 左
	{
		angletemp -= 10.f;
	} else if (keyflag2 == 1)	 // 右
	{
		angletemp += 10.f;
	}

	oled_show_float(50, 5, angletemp, 4, 2);

#endif
};
