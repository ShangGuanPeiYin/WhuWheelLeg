#include "zf_common_headfile.h"

Queue usart1_rec_list;	  // �ǵó�ʼ��
Queue usart2_rec_list;
Queue usart3_rec_list;

/**
 * @brief �û����г�ʼ��
 *
 */
void user_queue_init(void)
{
	QueueInit(&usart1_rec_list, 256);
	QueueInit(&usart2_rec_list, 256);
	QueueInit(&usart3_rec_list, 256);
};

/// @brief
/// @param ch ������������
/// @param _size �������ݳ���
/// @return
bool QueueInit(Queue* queue, int _size)	   // ��ʼ��
{
	if (queue == NULL || _size <= 0) {
		return false;	 // ���������Ը�Ϊ���ô�������׳��쳣
	}

	queue->front = 0;
	queue->rear	 = 0;
	queue->count = 0;
	queue->size	 = _size;

	queue->data	 = (unsigned char*) malloc(queue->size * sizeof(unsigned char));

	if (queue->data == NULL) {
		// �ڴ����ʧ�ܴ���
		//		exit(EXIT_FAILURE);
		return false;
	}

	return true;
}

/**
 * @brief ���
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
 * @brief ����
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
 * @brief ���
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
 * @brief �ж϶���
 *
 * @param queue
 * @return true
 * @return false
 */
bool isFull(Queue* queue) { return queue->count == queue->size; }

/**
 * @brief �ж϶ӿ�
 *
 * @param queue
 * @return true
 * @return false
 */
bool isEmpty(Queue* queue) { return queue->count == 0; }
