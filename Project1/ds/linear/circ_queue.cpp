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
queue* initqueue() {
	queue* q = new queue;
	q->data = new bit32[MAXSIZE];
	q->front = 0;
	q->rear = 0;
	return q;
}
bool isfull(const queue *q) {
	return (q->rear + 1) % MAXSIZE == q->front;
}
bool isempty(const queue *q) {
	return q->front == q->rear;
}
bool enqueue(queue*q,bit32 e) {
	if (isfull(q)) return false;
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return true;
}
bool dequeue(queue *q,bit32*e) {
	if (isempty(q)) return false;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return true;
}