#ifndef CODE_VOFA_H_
#define CODE_VOFA_H_

//ͷ�ļ�
#include "zf_common_headfile.h"
#include "zf_common_typedef.h"
#include <stdint.h>

//����
#define JFCH_COUNT 10        //����float�͸���
extern uint8_t RxBuffer[1];//���ڽ��ջ���
extern uint8_t DataBuff[200];//ָ������
extern float f2;
extern float data_return; // �����õ�������
extern uint8_t FH_flag;

typedef struct {//����ͨ����ʽ
    float CH_Data[JFCH_COUNT];
} JustFloat;

extern JustFloat UploadDataJF;

#define VofaSendStr(data,size)   uart_write_buffer(UART_2,data,size)
//��ֲʱ������UserFirstReceiveData��ֵ���ɸı��Զ���ĵ�һ�����սṹ�壨��ͷ��
//#define UserFirstReceiveData    &p1

//����
void VOFAplusUpload_JustFloat(JustFloat* sendbuffer);
void vofa_send(void);
void vofa_receive(void);
void USART_PID_Adjust(uint8 Motor_n);
float Pow_invert(uint8 X,uint8 n);//x����n��10


#endif /* CODE_VOFA_H_ */
