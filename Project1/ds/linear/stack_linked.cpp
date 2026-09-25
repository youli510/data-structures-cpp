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
void push(stack*s,bit32 n) {
	node* p = new node;
	p->data = n;
	p->next = s->head->next;
	s->head->next = p;
}
bool pop(stack*s,bit32*n) {
	if (isempty(s)) return false;
	node* t = s->head->next;
	*n = s->head->data; 
	s->head->next = t->next;
	delete t;
	return true;
}
bool gettop(const stack*s,bit32*n) {
	if (isempty(s)) return false;
	*n = s->head->data;
	return true;
}
void deletestack(stack*s) {
	node* p = s->head;
	while (p!=NULL) {
		node* t = p;
		p = p->next;
		delete t;
	}
	delete s;
}