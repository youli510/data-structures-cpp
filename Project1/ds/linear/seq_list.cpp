//顺序表链表
#include <iostream>
#include <string>
typedef int ElemType;
#define MAXSIZE 100
//struct seqlist {
//	ElemType data[MAXSIZE];
//	int length;
//};
struct node {
	ElemType data;
	node* next;
};
int main() {
	using namespace std;
	node* initlist();
	void inserthead(node * l, ElemType n);
	void listnode(node * l);
	node* get_tail(node * l);
	node* inserttail(node * l, ElemType n);
	int insertnode(node * l, int pos, ElemType n);
	int deletenode(node * l, int pos);
	void clearlist(node * l);
	int listlength(node * l);

	node* list = initlist();
	inserthead(list, 20);
	inserthead(list, 30);
	node* tail = get_tail(list);
	tail=inserttail(tail, 60);
	tail = inserttail(tail, 80);
	inserthead(list, 50);
	insertnode(list, 4, 70);
	deletenode(list, 5);
	cout << listlength(list) << "\n";
	listnode(list);
	/*void initlist(seqlist * l);
	int insertElem(seqlist*l,int pos,ElemType e);
	int append(seqlist * l, int e);*/
	clearlist(list);
	return 0;
}
node* initlist() {
	node* head = new node;
	head->data = 0;
	head->next = NULL;
	return head;
}					//初始化节点
void inserthead(node* l,ElemType n) {
	node* p = new node;
	p->data = n;
	p->next = l->next;
	l->next = p;
}					//头插法（输出顺序与输入顺序是反的）
void listnode(node *l) {
	node* p = l->next;
	while (p != NULL) {
		std::cout << p->data<<" ";
		p = p->next;
	}
	std::cout << "\n";
}					//遍历
node* get_tail(node* l) {
	node* p = l;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}					//获取尾节点
node* inserttail(node* l,ElemType n) {
	node* p = new node;
	p->data = n;
	l->next = p;
	p->next = NULL;
	return p;
}						//尾插法
int insertnode(node* l,int pos, ElemType n) {
	node* p = l;
	int i = 0;
	while (i < pos - 1) {
		p = p->next;
		i++;
		if (p == NULL) {
			return 0;
		}
	}
	node* q = new node;
	q->data = n;
	q->next = p->next;
	p->next = q;
	return 1;
}						//插入
int deletenode(node* l, int pos) {
	node* p = l;
	int i = 0;
	while (i < pos - 1) {
		p = p->next;
		i++;
		if (p == NULL) {
			return 0;
		}
	}
	node* q = p->next;
	p->next = q->next;
	delete q;
	return 1;
}							//删除
int listlength(node* l) {
	node* p = l->next;
	int len = 0;
	while (p != NULL) {
		p = p->next;
		len++;
	}
	return len;
}							//获取长度
void clearlist(node* l) {
	node* p = l;
	while (p != NULL) {
		node* temp = p;
		p = p->next;
		delete temp;
	}
}							//释放（包括头节点）
//void freeList(Node* L)	//释放（不包括头节点，便于后续利用）
//{
//	Node* p = L->next;
//	Node* q;
//
//	while (p != NULL)
//	{
//		q = p->next;
//		delete(p);
//		p = q;
//	}
//	L->next = NULL;
//}
//void initlist(seqlist* l) {
//	l->length = 0;
//}
//int append(seqlist* l, int e) {
//	l->data[l->length] = e;
//	l->length++;
//	return 1;
//}
//int insertElem(seqlist *l,int pos,ElemType e) {
//	if (pos <= l->length) {
//		for (int i = l->length - 1; i > pos; i--) {
//			l->data[i + 1] = l->data[i];
//		}
//		l->data[pos - 1] = e;
//		l->length++;
//	}
//	return 1;
//}
