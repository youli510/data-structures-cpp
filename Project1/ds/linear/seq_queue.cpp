//顺序队列
#include <iostream>
#include <cstdint>
#define MAXSIZE 100
typedef int bit32;

struct queue {
	bit32 data[MAXSIZE];
	int front;
	int rear;
};
void relocate(queue* q);
// 初始化顺序队列：front = rear = 0
void initqueue(queue *q){
	q->front = 0;
	q->rear = 0;
}
// 判空：front == rear
bool isempty(const queue *q) {
	return q->front == q->rear;
}
// 判满：front 在 0 且 rear 已到 MAXSIZE
bool isfull(const queue*q) {
	return q->front == 0 && q->rear == MAXSIZE;
}
// 出队：取 front 位置的值，front++
bool dequeue(queue* q,bit32* e) {
	if (isempty(q)) {
		std::cout << "空的";
		return false;
	}
	*e = q->data[q->front];
	q->front++;
	return true;
}
// 入队：rear 到达末尾时先 relocate 腾空间，再写入
bit32 enqueue(queue*q,bit32 e) {
	if (q->rear>=MAXSIZE) {
		if (q->front == 0) {
			std::cout << "已满";
			return false;
		}
		else relocate(q);
	}
	q->data[q->rear] = e;
	q->rear++;
	return true;
}
// 数据搬迁：把 [front, rear) 这一段整体前移到下标 0 开始
void relocate(queue*q) {
	int step = q->front;
	for (int i = q->front; i < q->rear; ++i) {
		q->data[i - step] = q->data[i];
	}
	q->front = 0;
	q->rear = q->rear - step;
}
// 取队头值但不删除
bool gethead(queue*q,bit32*e) {
	if (isempty(q)) return false;
	*e = q->data[q->front];
	return true;
}
