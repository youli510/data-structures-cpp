//双向链表
#include <iostream>
typedef int bit32;
struct node {
	bit32 data;
	node* next, * prev;
};
// 头插：新节点插到哑结点之后，同时维护 prev 和 next 两个指针
void inserthead(node* l,bit32 n) {
	node* p = new node;
	p->data = n;
	p->prev = l;
	p->next = l->next;
	if(l->next!=NULL) l->next->prev=p;
	l->next = p;
}
// 遍历找到并返回尾节点
node* get_tail(node* l) {
	node* p = l;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}
// 尾插：把新节点接在给定尾节点之后，返回新的尾节点
node* inserttail(node* l, bit32 n) {
	node* p = new node;
	p->data = n;
	p->prev = l;
	l->next = p;
	p->next = NULL;
	return p;
}
// 返回从头数第 pos 个节点（pos=0 就是哑结点本身）
node* seeknode(node* l, int pos) {
	node* p = l;
	for (int i = 0; i < pos - 1; i++) {
		p = p->next;
		if (p == NULL)return NULL;
	}
	return p;
}
// 在第 pos 个节点之后插入一个新节点
void setnode(node* l,int pos,bit32 n) {
	node* p = seeknode(l,pos);
	node* q = new node;
	q->data = n;
	q->next = p->next;
	q->prev = p;
	if(p->next!=NULL)p->next->prev = q;
	p->next = q;
}
// 删除第 pos 个节点之后的那个节点
void removenode(node*l,int pos) {
	node* p = seeknode(l, pos);
	if (p->next == NULL)return;
	node* q = p->next;
	p->next = q->next;
	if(q->next!=NULL)q->next->prev = p;
	delete(q);
}
// 创建带哑结点的空双向链表
node* initlist() {
	node* p = new node;
	p->data = 0;
	p->next = NULL;
	p->prev = NULL;
	return p;
}
// 打印链表所有元素
void printlist(node*l) {
	node* p = l->next;
	while (p != NULL) {
		std::cout << p->data << " ";
		p = p->next;
	}
}
// 释放所有节点（含哑结点），链表之后不可再用
void clearlist(node* l) {
	node* p = l->next;
	while (p != NULL) {
		node* q = p;
		p = p->next;
		delete q;

	}
	delete l;
}
int main() {
	node* list = initlist();
	inserthead(list, 2);
	inserthead(list, 1);
	node* tail = get_tail(list);
	inserttail(tail, 4);
	setnode(list, 4, 3);
	removenode(list,4);
	printlist(list);	
	clearlist(list);
	return 0;
}