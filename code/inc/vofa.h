#ifndef CODE_VOFA_H_
#define CODE_VOFA_H_

//头文件
#include "zf_common_headfile.h"
#include "zf_common_typedef.h"
#include <stdint.h>

//变量
#define JFCH_COUNT 10        //发送float型个数
extern uint8_t RxBuffer[1];//串口接收缓冲
extern uint8_t DataBuff[200];//指令内容
extern float f2;
extern float data_return; // 解析得到的数据
extern uint8_t FH_flag;

typedef struct {//数据通道格式
    float CH_Data[JFCH_COUNT];
} JustFloat;

extern JustFloat UploadDataJF;

#define VofaSendStr(data,size)   uart_write_buffer(UART_2,data,size)
//移植时，更改UserFirstReceiveData的值即可改变自定义的第一个接收结构体（表头）
//#define UserFirstReceiveData    &p1

//函数
void VOFAplusUpload_JustFloat(JustFloat* sendbuffer);
void vofa_send(void);
void vofa_receive(void);
void USART_PID_Adjust(uint8 Motor_n);
float Pow_invert(uint8 X,uint8 n);//x除以n次10


#endif /* CODE_VOFA_H_ */
