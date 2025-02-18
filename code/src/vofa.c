#include "Vofa.h"
#include <string.h>
#include <stdio.h>
uint8_t RxBuffer[1]={0};//串口接收缓冲
uint8_t DataBuff[200]={0};//指令内容
uint8_t data_Start_Num = 0; // 记录数据位开始的地方
uint8_t data_End_Num = 0; // 记录数据位结束的地方
uint8_t data_Num = 0; // 记录数据位数
uint32_t read_length=0;
float f2=0;
float data_return = 0; // 解析得到的数据
uint8_t data_flag=0;
uint8_t FH_flag = 0; // 初始化帧头标志
/************************************************
*文件说明：          基于vofa+上位机开发，发送及接收函数（JustFloat），发送图片。
*时    间：            2021.11.26
*备    注：            未经过大量测试，可能会有bug，注释已码好，可自行修复
                                上位机下载地址https://www.vofa.plus/
***************************************************/
JustFloat UploadDataJF;
/*************************************************
*   函数功能: VOFA+发送函数，用来显示波形
*   使用方法:   VOFAplusUpload_JustFloat(&UploadDataJF);
*   备注    : UploadDataJF是全局变量，直接赋值发送即可，
*                 如：UploadDataJF.CH_Data[0] = 1;
**************************************************/
void VOFAplusUpload_JustFloat(JustFloat* sendbuffer)
{
    uint8 Tail[4] = { 0x00, 0x00, 0x80, 0x7f };
    VofaSendStr((uint8*)sendbuffer->CH_Data, sizeof(float) * JFCH_COUNT);
    VofaSendStr(Tail, sizeof(Tail));
}
/*************************************************
*   函数功能: VOFA+发送函数，整合所有要发送的数据
*   使用方法: Vofasend;
**************************************************/
void vofa_send(void)//vofa波形发送整合
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
                FH_flag = 1; // 帧头
            } else if (FH_flag == 1 && DataBuff[i] == 0x2B) {//+
                FH_flag = 2;
            } else if (FH_flag == 2) {

                FH_flag = 3;
                data_flag=i+1;
                USART_PID_Adjust(1); // 数据解析和参数赋值函数
            } else if (FH_flag == 3 && DataBuff[i] == 0x23) {//ASCII #
                FH_flag = 0;
                i = 0; // 重置索引
                data_flag=0;
            }
        }
    memset(DataBuff, 0, sizeof(DataBuff));  // 清空缓存数组

}

float Get_Data(void)
{
    float Data=0.0;
     uint8_t dot_Flag=0;//小数点标志位，能区分小数点后或小数点前 0为小数点前，1为小数点后
     uint8_t dot_after_num=1;//小数点后的第几位
     int8_t minus_Flag=1;// 负号标志位 -1为是负号 1为正号
     for(;data_flag<read_length;data_flag++)
     {

       if(DataBuff[data_flag]==0x2D)//如果第一位为负号
       {
         minus_Flag=-1;
         continue;//跳过本次循环
       }
       if(dot_Flag==0)
       {
         if(DataBuff[data_flag]==0x2E)//如果识别到小数点，则将dot_Flag置1
         {
           dot_Flag=1;
         }
         else//还没遇到小数点前的运算
         {
           Data = Data*10 + DataBuff[data_flag]-48;
         }
       }
       else//遇到小数点后的运算
       {
         Data = Data + Pow_invert(DataBuff[data_flag]-48,dot_after_num);
         dot_after_num++;
       }
     }
     return Data*minus_Flag;//将换算后的数据返回出来 这里乘上负号标志位
}

/****************************************************
 * 小数位处理
 * 函数内部调用
 ****************************************************/
float Pow_invert(uint8_t X,uint8_t n)//x除以n次10
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
    float data_Get = Get_Data(); // 存放接收到的数据
    if(0)//动量轮
        {
            if(DataBuff[1]=='+' && DataBuff[2]=='1') // 角速度环P
                pid_init.pid_roll_speed.kp = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='2') // 角速度环I
                pid_init.pid_roll_speed.ki = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='3') // 角速度环D
                pid_init.pid_roll_speed.kd = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='4') // 角度环P
                pid_init.pid_roll.kp = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='5') // 角度环I
                pid_init.pid_roll.ki = data_Get;
            else if(DataBuff[1]=='+' && DataBuff[2]=='6') // 角度环D
                pid_init.pid_roll.kd = data_Get;
//            else if(DataBuff[1]=='+' && DataBuff[2]=='7') // 速度环P
//                NULL = data_Get;
//            else if(DataBuff[1]=='+' && DataBuff[2]=='8') // 速度环I
//                NULL = data_Get;
//            else if(DataBuff[1]=='+' && DataBuff[2]=='9') // 速度环D
//                NULL = data_Get;
//
//            else if(DataBuff[1]=='+' && DataBuff[2]=='0') // 速度环D
//                NULL = data_Get;


//            else if(DataBuff[1]=='+' && DataBuff[2]=='0') //目标角度
//                _pid_set.gyro_pid.integral_max = data_Get;

//            else if(DataBuff[1]=='+' && DataBuff[2]=='0') //目标角度
//                turn = data_Get;

//            else if(DataBuff[1]=='+' && DataBuff[2]=='!') //目标角度
//                NULL = data_Get;

        }

//    if(Motor_n==2)//行进轮
//       {
//           if(DataBuff[1]=='+' && DataBuff[2]=='1') // 角速度环P
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='2') // 角速度环I
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='3') // 角速度环D
//               NULL = data_Get;
//
//           else if(DataBuff[1]=='+' && DataBuff[2]=='4') // 角度环P
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='5') // 角度环I
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='6') // 角度环D
//               NULL = data_Get;
//
//           else if(DataBuff[1]=='+' && DataBuff[2]=='7') // 速度环P
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='8') // 速度环I
//               NULL = data_Get;
//           else if(DataBuff[1]=='+' && DataBuff[2]=='9') // 速度环D
//               NULL = data_Get;
//
//
//           else if(DataBuff[1]=='+' && DataBuff[2]=='0') //目标角度
//               NULL = data_Get;
//
//       }

}
