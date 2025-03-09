#ifndef _USER_QUEUE_H_
#define _USER_QUEUE_H_

#include "zf_common_typedef.h"

typedef struct {
	int			   front;
	int			   rear;
	int			   size;	 // ���г���
	int			   count;	 // �����ж϶������ǿ�
	unsigned char* data;	 // ����һƬ�ڴ棬dataʵ�����������׵�ַ
} QueueType;

extern QueueType usart1_rec_list;
extern QueueType usart2_rec_list;
extern QueueType usart3_rec_list;

void clear(QueueType* queue);						  // ����
bool QueueInit(QueueType* queue, int _size);		  // ��ʼ��
bool enQueue(QueueType* queue, unsigned char ch);	  // ���
bool deQueue(QueueType* queue, unsigned char* ch);	  // ���� һ�� n ��
bool isFull(QueueType* queue);						  // �ж��Ƿ�����
bool isEmpty(QueueType* queue);

#endif
