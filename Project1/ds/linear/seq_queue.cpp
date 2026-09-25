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
void initqueue(queue *q){
	q->front = 0;
	q->rear = 0;
}
bool isempty(const queue *q) {
	return q->front == q->rear;
}
bool isfull(const queue*q) {
	return q->front == 0 && q->rear == MAXSIZE;
}
bool dequeue(queue* q,bit32* e) {
	if (isempty(q)) {
		std::cout << "空的";
		return false;
	}
	*e = q->data[q->front];
	q->front++;
	return true;
}
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
void relocate(queue*q) {
	int step = q->front;
	for (int i = q->front; i < q->rear; ++i) {
		q->data[i - step] = q->data[i];
	}
	q->front = 0;
	q->rear = q->rear - step;
}
bool gethead(queue*q,bit32*e) {
	if (isempty(q)) return false;
	*e = q->data[q->front];
	return true;
}
