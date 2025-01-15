#include "zf_common_headfile.h"

extern float	angletemp;
extern Vector2f point_temp;

/**
 * @brief OLED屏幕调试函数，对代码进行调试
 *
 */
void OLedDebug(void)
{
#if 0	 // 舵机测试

	OLED_Key_Scan();

	if (keyflag1 == 1)	  // 左
	{
		angletemp -= 10.f;
	} else if (keyflag2 == 1)	 // 右
	{
		angletemp += 10.f;
	}
	Limit(angletemp, 0, 180);

	Servo[Fl].angleSet = angletemp;
	Servo[Fr].angleSet = angletemp;
	Servo[Bl].angleSet = angletemp;
	Servo[Br].angleSet = angletemp;

	oled_show_float(50, 5, angletemp, 4, 2);

#endif

#if 1	 // 五连杆测试

	OLED_Key_Scan();

	if (keyflag1 == 1)	  // 上
	{
		point_temp.x -= 10.f;
	} else if (keyflag2 == 1)	 // 下
	{
		point_temp.x += 10.f;
	} else if (keyflag0 == 1)	 //
	{
		point_temp.x -= 10.f;
	} else if (keyflag3 == 1)	 //
	{
		point_temp.x += 10.f;
	}

	oled_show_float(50, 3, point_temp.x, 4, 2);
	oled_show_float(50, 4, point_temp.y, 4, 2);

#endif
};
