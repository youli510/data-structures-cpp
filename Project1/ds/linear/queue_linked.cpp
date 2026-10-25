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
// 初始化链式队列：建哑结点，front 和 rear 都指向它
queue* initqueue() {
	queue* q = new queue;
	queuenode* node = new queuenode;
	node->data = 0;
	node->next = NULL;
	q->front = node;
	q->rear = node;
	return q;
}
// 判空：front == rear
bool isempty(queue* q) {
	return q->front == q->rear;
}
// 入队：在 rear 后面挂新节点，rear 后移
void enqueue(queue* q, bit32 n) {
	queuenode* node = new queuenode;
	node->data = n;
	node->next = NULL;
	q->rear->next = node;
	q->rear = node;
}
// 出队：删掉 front 的下一个节点；删空时要把 rear 退回 front
bool dequeue(queue* q, bit32* n) {
	if (isempty(q)) return false;
	queuenode* node = q->front->next;
	*n = node->data;
	q->front->next = node->next;
	if (q->rear == node) q->rear = q->front;
	delete(node);
	return true;
}
// 循环出队直到空，然后释放哑结点和队列对象
void clearqueue(queue*q) {
	while (!isempty(q)) {
		bit32 t;
		dequeue(q,&t);
	}
	delete q->front;
	delete q;
}