//栈的链式结构
#include <iostream>
#include <cstdint>
typedef int bit32;
struct node {
	bit32 data;
	node* next;
};
struct stack {
	node* head;
};
//将“栈”和“节点”分离，提高可读性，避免误用
stack* initstack() {
	stack* s = new stack;
	s->head = new node;
	//s->head->data = 0;
	s->head->next = NULL;
	return s;
}
bool isempty(const stack *s) {
	return s->head->next == NULL;
}
// 链式栈入栈：头插法，新节点成为新的栈顶
void push(stack*s,bit32 n) {
	node* p = new node;
	p->data = n;
	p->next = s->head->next;
	s->head->next = p;
}
// 链式栈出栈：删除 head 之后的第一个节点（真正的栈顶）
bool pop(stack*s,bit32*n) {
	if (isempty(s)) return false;
	node* t = s->head->next;
	*n = s->head->data; 
	s->head->next = t->next;
	delete t;
	return true;
}
// 只看栈顶：返回 head->next 的值
bool gettop(const stack*s,bit32*n) {
	if (isempty(s)) return false;
	*n = s->head->data;
	return true;
}
// 释放所有节点（含 head）以及栈对象
void deletestack(stack*s) {
	node* p = s->head;
	while (p!=NULL) {
		node* t = p;
		p = p->next;
		delete t;
	}
	delete s;
}