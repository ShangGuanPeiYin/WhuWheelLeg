#ifndef _USER_QUEUE_H_
#define _USER_QUEUE_H_

#include "zf_common_typedef.h"

typedef struct {
	int			   front;
	int			   rear;
	int			   size;	 // ���г���
	int			   count;	 // �����ж϶������ǿ�
	unsigned char* data;	 // ����һƬ�ڴ棬dataʵ�����������׵�ַ
} Queue;

extern Queue usart1_rec_list;
extern Queue usart2_rec_list;
extern Queue usart3_rec_list;

void clear(Queue* queue);						  // ����
bool QueueInit(Queue* queue, int _size);		  // ��ʼ��
bool enQueue(Queue* queue, unsigned char ch);	  // ���
bool deQueue(Queue* queue, unsigned char* ch);	  // ���� һ�� n ��
bool isFull(Queue* queue);						  // �ж��Ƿ�����
bool isEmpty(Queue* queue);

#endif
