//消息队列单线程
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
bool isfull(const queue* q) {
	return (q->rear + 1) % MAXSIZE == q->front;
}
bool isempty(const queue* q) {
	return q->front == q->rear;
}
bool enqueue(queue* q, bit32 e) {
	if (isfull(q)) return false;
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return true;
}
bool dequeue(queue* q, bit32* e) {
	if (isempty(q)) return false;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return true;
}

int main() {
	queue* q=initqueue();
	bit32 msg_id=0;
	bit32 val;
	for (int i = 0; i < 10;i++) {
		if (i%2==0) {
			/*if (isfull(q)) {
				std::cout << "[生产] 队列满，等待...\n";
				continue;
			}
			else {*/
			for (int j = 0; j < 3; j++) {
				msg_id++;
				if (!enqueue(q, msg_id)) {
					std::cout << "[生产] 队列满，消息" << msg_id << " 丢弃\n";
					break;
				}
				std::cout << "[生产] 消息" << msg_id << " 入队\n";
			}
		}
		else {
			if (isempty(q)) {
				std::cout << "[消费] 队列空，等待...\n";
				continue;
			}
			else {
				dequeue(q,&val);
				std::cout << "[消费] 消息" << val << " 出队\n";
			}
		}
	}
}
