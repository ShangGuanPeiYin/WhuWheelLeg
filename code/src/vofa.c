#include "Vofa.h"
#include <string.h>
#include <stdio.h>
uint8_t RxBuffer[1]={0};//���ڽ��ջ���
uint8_t DataBuff[200]={0};//ָ������
uint8_t data_Start_Num = 0; // ��¼����λ��ʼ�ĵط�
uint8_t data_End_Num = 0; // ��¼����λ�����ĵط�
uint8_t data_Num = 0; // ��¼����λ��
uint32_t read_length=0;
float f2=0;
float data_return = 0; // �����õ�������
uint8_t data_flag=0;
uint8_t FH_flag = 0; // ��ʼ��֡ͷ��־
/************************************************
*�ļ�˵����          ����vofa+��λ�����������ͼ����պ�����JustFloat��������ͼƬ��
*ʱ    �䣺            2021.11.26
*��    ע��            δ�����������ԣ����ܻ���bug��ע������ã��������޸�
                                ��λ�����ص�ַhttps://www.vofa.plus/
***************************************************/
JustFloat UploadDataJF;
/*************************************************
*   ��������: VOFA+���ͺ�����������ʾ����
*   ʹ�÷���:   VOFAplusUpload_JustFloat(&UploadDataJF);
*   ��ע    : UploadDataJF��ȫ�ֱ�����ֱ�Ӹ�ֵ���ͼ��ɣ�
*                 �磺UploadDataJF.CH_Data[0] = 1;
**************************************************/
void VOFAplusUpload_JustFloat(JustFloat* sendbuffer)
{
    uint8 Tail[4] = { 0x00, 0x00, 0x80, 0x7f };
    VofaSendStr((uint8*)sendbuffer->CH_Data, sizeof(float) * JFCH_COUNT);
    VofaSendStr(Tail, sizeof(Tail));
}
/*************************************************
*   ��������: VOFA+���ͺ�������������Ҫ���͵�����
*   ʹ�÷���: Vofasend;
**************************************************/
void vofa_send(void)//vofa���η�������
{

    UploadDataJF.CH_Data[0] = Motor[0].valueNow.speed;
    UploadDataJF.CH_Data[1] = Motor[1].valueNow.speed;
    UploadDataJF.CH_Data[2] = IMUdata.dataOri.pitch;
    UploadDataJF.CH_Data[3] = IMUdata.dataOri.angle.x;
//    UploadDataJF.CH_Data[4] = 0;
//    UploadDataJF.CH_Data[5] = Pitch;
//    UploadDataJF.CH_Data[6] = encoder_r;
//    UploadDataJF.CH_Data[7] = encoder_l;
//    UploadDataJF.CH_Data[8] = encoder1;
//    UploadDataJF.CH_Data[9] = encoder2;
    VOFAplusUpload_JustFloat(&UploadDataJF);
}

void vofa_receive(void)
{
    read_length = wireless_uart_read_buffer(DataBuff, sizeof(DataBuff));
    for (uint8_t i = 0; i < read_length; i++) {
            if (DataBuff[i] == 0x21 && FH_flag == 0) {//!
                FH_flag = 1; // ֡ͷ
            } else if (FH_flag == 1 && DataBuff[i] == 0x2B) {//+
                FH_flag = 2;
            } else if (FH_flag == 2) {

                FH_flag = 3;
                data_flag=i+1;
                USART_PID_Adjust(1); // ���ݽ����Ͳ�����ֵ����
            } else if (FH_flag == 3 && DataBuff[i] == 0x23) {//ASCII #
                FH_flag = 0;
                i = 0; // ��������
                data_flag=0;
            }
        }
    memset(DataBuff, 0, sizeof(DataBuff));  // ��ջ�������

}

float Get_Data(void)
{
    float Data=0.0;
     uint8_t dot_Flag=0;//С�����־λ��������С������С����ǰ 0ΪС����ǰ��1ΪС�����
     uint8_t dot_after_num=1;//С�����ĵڼ�λ
     int8_t minus_Flag=1;// ���ű�־λ -1Ϊ�Ǹ��� 1Ϊ����
     for(;data_flag<read_length;data_flag++)
     {

       if(DataBuff[data_flag]==0x2D)//�����һλΪ����
       {
         minus_Flag=-1;
         continue;//��������ѭ��
       }
       if(dot_Flag==0)
       {
         if(DataBuff[data_flag]==0x2E)//���ʶ��С���㣬��dot_Flag��1
         {
           dot_Flag=1;
         }
         else//��û����С����ǰ������
         {
           Data = Data*10 + DataBuff[data_flag]-48;
         }
       }
       else//����С����������
       {
         Data = Data + Pow_invert(DataBuff[data_flag]-48,dot_after_num);
         dot_after_num++;
       }
     }
     return Data*minus_Flag;//�����������ݷ��س��� ������ϸ��ű�־λ
}

/****************************************************
 * С��λ����
 * �����ڲ�����
 ****************************************************/
float Pow_invert(uint8_t X,uint8_t n)//x����n��10
{
  float result=X;
    while(n--)
    {
        result/=10;
    }
    return result;
}

void USART_PID_Adjust(uint8_t Motor_n)
{
    float data_Get = Get_Data(); // ��Ž��յ�������
    if(0)//������
        {
            if(DataBuff[1]=='+' && DataBuff[2]=='1') // ���ٶȻ�P
                pid_init.pid_roll_speed.kp = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='2') // ���ٶȻ�I
                pid_init.pid_roll_speed.ki = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='3') // ���ٶȻ�D
                pid_init.pid_roll_speed.kd = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='4') // �ǶȻ�P
                pid_init.pid_roll.kp = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='5') // �ǶȻ�I
                pid_init.pid_roll.ki = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='6') // �ǶȻ�D
                pid_init.pid_roll.kd = data_Get;
//            else if(DataBuff[1]=='+' && DataBuff[2]=='7') // �ٶȻ�P
//                NULL = data_Get;
//            else if(DataBuff[1]=='+' && DataBuff[2]=='8') // �ٶȻ�I
//                NULL = data_Get;
//            else if(DataBuff[1]=='+' && DataBuff[2]=='9') // �ٶȻ�D
//                NULL = data_Get;
//
//            else if(DataBuff[1]=='+' && DataBuff[2]=='0') // �ٶȻ�D
//                NULL = data_Get;


//            else if(DataBuff[1]=='+' && DataBuff[2]=='0') //Ŀ��Ƕ�
//                _pid_set.gyro_pid.integral_max = data_Get;

//            else if(DataBuff[1]=='+' && DataBuff[2]=='0') //Ŀ��Ƕ�
//                turn = data_Get;

//            else if(DataBuff[1]=='+' && DataBuff[2]=='!') //Ŀ��Ƕ�
//                NULL = data_Get;

        }

//    if(Motor_n==2)//�н���
//       {
//           if(DataBuff[1]=='+' && DataBuff[2]=='1') // ���ٶȻ�P
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='2') // ���ٶȻ�I
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='3') // ���ٶȻ�D
//               NULL = data_Get;
//
//           else if(DataBuff[1]=='+' && DataBuff[2]=='4') // �ǶȻ�P
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='5') // �ǶȻ�I
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='6') // �ǶȻ�D
//               NULL = data_Get;
//
//           else if(DataBuff[1]=='+' && DataBuff[2]=='7') // �ٶȻ�P
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='8') // �ٶȻ�I
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='9') // �ٶȻ�D
//               NULL = data_Get;
//
//
//           else if(DataBuff[1]=='+' && DataBuff[2]=='0') //Ŀ��Ƕ�
//               NULL = data_Get;
//
//       }

}
