#include "zf_common_headfile.h"

Queue usart1_rec_list;	  // 记得初始化
Queue usart2_rec_list;
Queue usart3_rec_list;

/**
 * @brief 用户队列初始化
 *
 */
void user_queue_init(void)
{
	QueueInit(&usart1_rec_list, 256);
	QueueInit(&usart2_rec_list, 256);
	QueueInit(&usart3_rec_list, 256);
};

/// @brief
/// @param ch 队列数据类型
/// @param _size 队列数据长度
/// @return
bool QueueInit(Queue* queue, int _size)	   // 初始化
{
	if (queue == NULL || _size <= 0) {
		return false;	 // 错误处理，可以改为设置错误码或抛出异常
	}

	queue->front = 0;
	queue->rear	 = 0;
	queue->count = 0;
	queue->size	 = _size;

	queue->data	 = (unsigned char*) malloc(queue->size * sizeof(unsigned char));

	if (queue->data == NULL) {
		// 内存分配失败处理
		//		exit(EXIT_FAILURE);
		return false;
	}

	return true;
}

/**
 * @brief 入队
 *
 * @param queue
 * @param ch
 * @return true
 * @return false
 */
bool enQueue(Queue* queue, unsigned char ch)
{
	if (queue->count < queue->size) {
		(queue->data[queue->rear]) = ch;
		queue->rear				   = (queue->rear + 1) % queue->size;
		queue->count++;
		return true;
	} else {
		return false;
	}
}

/**
 * @brief 出队
 *
 * @param queue
 * @param ch
 * @return true
 * @return false
 */
bool deQueue(Queue* queue, unsigned char* ch)
{
	if (queue->count > 0) {
		*ch			 = queue->data[queue->front];
		queue->front = (queue->front + 1) % queue->size;
		queue->count--;
		return true;
	} else
		return false;
}

/**
 * @brief 清除
 *
 * @param queue
 */
void clear(Queue* queue)
{
	queue->front = 0;
	queue->rear	 = 0;
	queue->count = 0;
}

/**
 * @brief 判断队满
 *
 * @param queue
 * @return true
 * @return false
 */
bool isFull(Queue* queue) { return queue->count == queue->size; }

/**
 * @brief 判断队空
 *
 * @param queue
 * @return true
 * @return false
 */
bool isEmpty(Queue* queue) { return queue->count == 0; }
