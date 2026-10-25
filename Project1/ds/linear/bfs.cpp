#include <iostream>
#include <iostream>
#include <cstdint>
#define MAXSIZE 100
using bit32 = int;
//typedef int bit32;
struct node {
	int data;
	node* left, * right;
};
struct queuenode {
	bit32 data;
	struct queuenode* next;
};
struct queue {
	bit32 data[MAXSIZE];
	int front;
	int rear;
};
// 初始化顺序队列：front = rear = 0
void initqueue(queue* q) {
	q->front = 0;
	q->rear = 0;
}
// 判空：front == rear
bool isempty(const queue* q) {
	return q->front == q->rear;
}
// 判满：front 在 0 且 rear 已到 MAXSIZE（此实现没有搬迁机制）
bool isfull(const queue* q) {
	return q->front == 0 && q->rear == MAXSIZE;
}
// 出队：取 front 位置的值，front++
bool dequeue(queue* q, bit32* e) {
	if (isempty(q)) {
		std::cout << "空的";
		return false;
	}
	*e = q->data[q->front];
	q->front++;
	return true;
}
// 入队：写到 rear 位置后 rear++（返回类型写成 bit32，实际返回的是 bool）
bit32 enqueue(queue* q, bit32 e) {
	if (q->rear >= MAXSIZE) {
		if (q->front == 0) {
			std::cout << "满了";
			return false;
		}
	}
	q->data[q->rear] = e;
	q->rear++;
	return true;
}
// 二叉树层序遍历：队列里存节点编号，用 nodes[] 表把编号换成节点指针
void bfs(node* root, queue* q, node* nodes[]) {
	enqueue(q, root->data);          // 入队的是编号（int）
	bit32 e;
	while (!isempty(q)) {
		dequeue(q, &e);              // e 是编号
		node* cur = nodes[e];        // 用编号查表拿到指针
		std::cout << cur->data << " ";
		if (cur->left != NULL)  enqueue(q, cur->left->data);
		if (cur->right != NULL) enqueue(q, cur->right->data);
	}
}
int main() {
	queue q;
	initqueue(&q);
	node* n1, * n2, * n3, * n4, * n5, * n6;
	n4 = new node{ 4, nullptr, nullptr };
	n5 = new node{ 5, nullptr, nullptr };
	n6 = new node{ 6, nullptr, nullptr };
	n2 = new node{ 2, n4, n5 };
	n3 = new node{ 3, nullptr, n6 };
	n1 = new node{ 1, n2, n3 };
	node* nodes[7];
	nodes[1] = n1;
	nodes[2] = n2;
	nodes[3] = n3;
	nodes[4] = n4;
	nodes[5] = n5;
	nodes[6] = n6;
	bfs(n1,&q,nodes);
	return 0;
}