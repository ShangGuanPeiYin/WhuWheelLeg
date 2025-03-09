#ifndef _DATAPROCESS_H_
#define _DATAPROCESS_H_
#include "zf_common_headfile.h"

// const static int ARRSIZE = 128;

typedef struct _dataProcess {
	bool get_head, get_end, get_head_id;	// ��־λ���õ���ͷ���õ���β���õ�head_id

	char rec_head[2];	   // �õ���ǰ�����ֽ� ����ͷ��
	char rec_end[2];	   // �յ���β�����ֽڣ���β)
	char recData[128];	   // ������������dataDecode
	char sendData[128];	   // ������������dataEncode
	int	 rec_len;		   // �������鵱ǰ����
	char head_id;		   // ��ͷID

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
