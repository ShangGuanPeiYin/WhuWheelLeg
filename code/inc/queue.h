#ifndef _USER_QUEUE_H_
#define _USER_QUEUE_H_

#include "zf_common_typedef.h"

typedef struct {
	int			   front;
	int			   rear;
	int			   size;	 // 队列长度
	int			   count;	 // 用于判断队满还是空
	unsigned char* data;	 // 申请一片内存，data实际上是数组首地址
} QueueType;

extern QueueType usart1_rec_list;
extern QueueType usart2_rec_list;
extern QueueType usart3_rec_list;

void clear(QueueType* queue);						  // 擦除
bool QueueInit(QueueType* queue, int _size);		  // 初始化
bool enQueue(QueueType* queue, unsigned char ch);	  // 入队
bool deQueue(QueueType* queue, unsigned char* ch);	  // 出队 一次 n 个
bool isFull(QueueType* queue);						  // 判断是否满队
bool isEmpty(QueueType* queue);

#endif
