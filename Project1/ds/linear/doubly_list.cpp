//双向链表
#include <iostream>
typedef int bit32;
struct node {
	bit32 data;
	node* next, * prev;
};
void inserthead(node* l,bit32 n) {
	node* p = new node;
	p->data = n;
	p->prev = l;
	p->next = l->next;
	if(l->next!=NULL) l->next->prev=p;
	l->next = p;
}
node* get_tail(node* l) {
	node* p = l;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}
node* inserttail(node* l, bit32 n) {
	node* p = new node;
	p->data = n;
	p->prev = l;
	l->next = p;
	p->next = NULL;
	return p;
}
node* seeknode(node* l, int pos) {
	node* p = l;
	for (int i = 0; i < pos - 1; i++) {
		p = p->next;
		if (p == NULL)return NULL;
	}
	return p;
}
void setnode(node* l,int pos,bit32 n) {
	node* p = seeknode(l,pos);
	node* q = new node;
	q->data = n;
	q->next = p->next;
	q->prev = p;
	if(p->next!=NULL)p->next->prev = q;
	p->next = q;
}
void removenode(node*l,int pos) {
	node* p = seeknode(l, pos);
	if (p->next == NULL)return;
	node* q = p->next;
	p->next = q->next;
	if(q->next!=NULL)q->next->prev = p;
	delete(q);
}
node* initlist() {
	node* p = new node;
	p->data = 0;
	p->next = NULL;
	p->prev = NULL;
	return p;
}
void printlist(node*l) {
	node* p = l->next;
	while (p != NULL) {
		std::cout << p->data << " ";
		p = p->next;
	}
}
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