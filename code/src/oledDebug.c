#include "zf_common_headfile.h"

extern float angletemp;
extern float reachTimeTemp;

/**
 * @brief OLED��Ļ���Ժ������Դ�����е���
 *
 */
void OLedDebug(void)
{
#if 1	 // �������
	OLED_Key_Scan();

	if (keyflag1 == 1)	  // ��
	{
		angletemp -= 10.f;
	} else if (keyflag2 == 1)	 // ��
	{
		angletemp += 10.f;
	}

	oled_show_float(50, 5, angletemp, 4, 2);

#endif
};
