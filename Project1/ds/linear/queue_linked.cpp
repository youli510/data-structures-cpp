//队列链式结构
#include <iostream>
#include <cstdint>
#define MAXSIZE1 100
using bit32 = int;
//typedef int bit32;

struct queuenode {
	bit32 data;
	struct queuenode* next;
};
struct queue {
	queuenode* front;
	queuenode* rear;
};
queue* initqueue() {
	queue* q = new queue;
	queuenode* node = new queuenode;
	node->data = 0;
	node->next = NULL;
	q->front = node;
	q->rear = node;
	return q;
}
bool isempty(queue* q) {
	return q->front == q->rear;
}
void enqueue(queue* q, bit32 n) {
	queuenode* node = new queuenode;
	node->data = n;
	node->next = NULL;
	q->rear->next = node;
	q->rear = node;
}
bool dequeue(queue* q, bit32* n) {
	if (isempty(q)) return false;
	queuenode* node = q->front->next;
	*n = node->data;
	q->front->next = node->next;
	if (q->rear == node) q->rear = q->front;
	delete(node);
	return true;
}
void clearqueue(queue*q) {
	while (!isempty(q)) {
		bit32 t;
		dequeue(q,&t);
	}
	delete q->front;
	delete q;
}