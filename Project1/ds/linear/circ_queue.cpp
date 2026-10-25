//循环队列
#include <iostream>
#include <cstdint>
#define MAXSIZE 8
typedef int bit32;
struct queue {
	bit32* data;
	int front;
	int rear;
};
// 初始化循环队列：分配数组，front = rear = 0
queue* initqueue() {
	queue* q = new queue;
	q->data = new bit32[MAXSIZE];
	q->front = 0;
	q->rear = 0;
	return q;
}
// 判满：(rear+1) % MAXSIZE == front —— 牺牲一个空位来区分「满」和「空」
bool isfull(const queue *q) {
	return (q->rear + 1) % MAXSIZE == q->front;
}
// 判空：front == rear
bool isempty(const queue *q) {
	return q->front == q->rear;
}
// 入队：写入 rear 位置，rear 环形后移
bool enqueue(queue*q,bit32 e) {
	if (isfull(q)) return false;
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return true;
}
// 出队：取 front 位置的值，front 环形后移
bool dequeue(queue *q,bit32*e) {
	if (isempty(q)) return false;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return true;
}