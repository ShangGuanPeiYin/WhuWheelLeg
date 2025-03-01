#include "zf_common_headfile.h"
//���㿪��
float InvSqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return 1.0/x;
}

int abs_int(int x)
{
  return x=x>0?x:-x;
}

float abs_float(float x)
{
  return x=x>0?x:-x;
}

//���������Ĵ�ֵ
int GetMax(int x1,int x2)
{
  if(x1>x2)
    return x1;
  else
    return x2;
}
//����������Сֵ
int GetMin(int x1,int x2)
{
  if(x1>x2)
    return x2;
  else
    return x1;
}
//�����ֹ���Ƿ���������Χ
int  AssertEndRow(int endrow,int min,int max)
{
  if(endrow>=min&&endrow<=max)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
//�ж�����֮��ľ����Ƿ���һ����Χ
int AssertLength(int x1,int y1,int x2,int y2,int min,int max,float *length)
{
  float coordinate1[1][2],coordinate2[1][2];
  float distance=0;
  Real_Location(x1,y1,coordinate1);
  Real_Location(x2,y2,coordinate2);
  distance=GetDistance(coordinate1,coordinate2);
  *length=distance;
  if(distance>min&&distance<max)
    return 1;
  else
    return 0;
}

//��ȡ�����ص�֮��ľ���
float GetLength(int x1,int y1,int x2,int y2)
{
  float coordinate1[1][2],coordinate2[1][2];
  float distance=0;
  Real_Location(x1,y1,coordinate1);
  Real_Location(x2,y2,coordinate2);
  distance=GetDistance(coordinate1,coordinate2);
  return distance;
}

float LimitMax(float a,float max)
{
  return a>max?max:a;
}

float LimitMin(float a,float min)
{
  return a<min?min:a;
}

float LimitBothSides(float a,float min,float max)
{
  if(a>=max) return max;
  else if(a<=min) return min;
  else return a;
}
/************************************************************************/
/*
*��������void Draw_a_Line(int Start_Row,int End_Row,int line[ROW])
*�������ܣ�ͨ����֪���黭��ĳһ����
*�βΣ�Start_Row����ʼ�� End_Row����ֹ��  line[ROW]����������
*����ֵ����
*��ע����
*/
/************************************************************************/
void Draw_a_Line(int Start_Row,int End_Row,int line[ROW])
{
  uint8 i = 0;
  
  for(i = (uint8)Start_Row;i<=End_Row;i++)
  {
    videoData[i][line[i]] = 0;
    if(line[i]-1>=0) videoData[i][line[i]-1] = 0;
  }
}
