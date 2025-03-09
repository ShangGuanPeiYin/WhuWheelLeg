#ifndef _DATAPROCESS_H_
#define _DATAPROCESS_H_
#include "zf_common_headfile.h"

// const static int ARRSIZE = 128;

typedef struct _dataProcess {
	bool get_head, get_end, get_head_id;	// 标志位：得到包头，得到包尾，得到head_id

	char rec_head[2];	   // 得到的前两个字节 （包头）
	char rec_end[2];	   // 收到的尾两个字节（包尾)
	char recData[128];	   // 接收数组用于dataDecode
	char sendData[128];	   // 发送数组用于dataEncode
	int	 rec_len;		   // 接收数组当前长度
	char head_id;		   // 包头ID

} DataProcessType;

//typedef struct _ControlMsg {
//	;
//	;
//	;
//} CtrlMsgType;

extern DataProcessType U2data;
//extern CtrlMsgType	   CtrlMsg;

void DataProcessInit(void);
void ReadMsg(DataProcessType* data, uint8 temp);
bool getHeadMsg(DataProcessType* data, u8 _ch);
char checkSum(char* ch, int n);
void clearFlag(DataProcessType* data);

#endif
