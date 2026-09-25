//表应用
#include <iostream>
#include <cmath>
typedef int bit32;
struct node {
	bit32 data;
	node* next;
};
int findnodeFS(node* l, int k) {
	node* fast = l->next;
	node* slow = l->next; 
	for (int i = 0; i < k; i++) {
		fast = fast->next;
	}
	while (fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}
	std::cout << "倒数第" << k << "个为" << slow->data;
	return 1;
}			
/*快慢指针*/
node* initilist() {
	node* head = new node;
	head->data = 0;
	head->next = NULL;
	return head;
}
node* initilist(bit32 n) {
	node* head = new node;
	head->data = n;
	head->next = NULL;
	return head;
}
node* get_tail(node*l) {
	if (l == NULL) return NULL;
	node* p = l;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}	
node* listtail(node*l,bit32 n) {
	node* p =new node;
	p->data = n;
	l->next = p;
	p->next = NULL;
	return p;
}
node* listtail(node*l,node*n) {
	l->next = n;
	n->next = NULL;
	return n;
}
void listhead(node* l, bit32 n) {
	node* p = new node;
	p->data = n;
	p->next = l->next;
	l->next = p;
}
void clearlist(node* l) {
	node* p = l;
	while (p != NULL) {
		node* q = p;
		p = p->next;
		delete q;
	}
}
void deletenode(node* l) {
	node* t = l->next;
	l->next = t->next;
	delete(t);
}
void listnode(node* l) {
	node* p = l->next;
	while (p != NULL) {
		std::cout << p->data <<" ";
		p = p->next;
	}
	std::cout << "\n";
}
int listlength(node* l) {
	node* p = l->next;
	int i = 0;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}
node* findstrnode(node* l, node* i) {
	if (l == NULL || i == NULL) return NULL;
	node* fast, *slow;
	int len1 = listlength(l);
	int len2 = listlength(i);
	int step=0;
	if (len1 > len2) {
		step = len1 - len2;
		fast = l;
		slow = i;
	}
	else {
		step = len2 - len1;
		fast = i;
		slow = l;
	}
	for (int i = 0; i < step; i++) {
		fast = fast->next;
	}
	while (fast->data != slow->data) {
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}
void removenode(node* l, int n) {
	int* q = new int[n];
	for (int i = 0; i < n; i++) {
		q[i] = 0;
	}
	node* p = l;
	while (p->next != NULL) {
		int index = std::abs(p->next->data);
		if (q[index] != 1) {
			q[index]=1;
			p = p->next;
		}
		else {
			deletenode(p);
		}
	}
	delete[] q;
}			//删除绝对值重复
node* reverse(node* l) {
	node* first = NULL;
	node* second = l->next;
	node* third ;
	while (second!=NULL) {
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}
	l->next = first;
	return l;
}
node* middle(node* l) {
	node* fast = l->next;
	node* slow = l;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
void removemiddle(node*l) {
	node*middlenode=middle(l);
	deletenode(middlenode);
}
void reorderlist(node*l) {
	node*middlenode=middle(l);
	node* first = NULL;
	node* second = middlenode->next;
	middlenode->next = NULL;
	node* third = NULL;
	while (second != NULL) {
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}
	node* p1 = l->next;
	node* q1 = first;
	node* p2, * q2;
	//node* prev = NULL;
	while (p1 != NULL && q1 != NULL) {
		p2 = p1->next;
		q2 = q1->next;
		p1->next = q1;
		// 如果前半段已经没有后继节点，只需保留 q1 原有的后继（q2），剩余的后半段直接接上
		if (p2 == NULL) {
			break;
		}
		q1->next = p2;
		//prev = q1;
		p1 = p2;
		q1 = q2;
	}
	/*if (q1 != NULL) {
		if (prev != NULL) prev->next = q1;
		else l->next = q1;
	}*/
}
int iscycle(node*l) {
	node* fast = l;
	node* slow = l;
	while (fast !=NULL && fast->next!=NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast==slow) {
			return 1;
		}
	}
	return 0;
}
node* findbegin(node* l) {
	node* fast = l;
	node* slow = l;
	while (fast!=NULL && fast->next!=NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast==slow) {
			int count = 1;
			node* p = fast;
			while (p->next!=slow) {
				count++;
				p = p->next;
			}
			fast = l;
			slow = l;
			for (int i = 0; i < count; i++) {
				fast = fast->next;
			}
			while (fast != slow) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
	}
	return NULL;
}
void clearcyclelist(node* l) {
	if (l == NULL) return;
	node* begin = findbegin(l);
	if (begin != NULL) {
		node* p = begin;
		while (p->next != begin) {
			p = p->next;
		}
		p->next = NULL;
	}
	clearlist(l);
	l->next = NULL;
}
void printcyclelist(node* l) {
	if (l == NULL) {
		std::cout << "空";
		return;
	}
	node* begin = findbegin(l);
	if (begin == NULL) {
		listnode(l);
		std::cout << "空";
		return;
	}
	node* p = l->next;
	while (p != NULL && p != begin) {
		std::cout << p->data << " ";
		p = p->next;
	}
	p = begin;
	if (p != NULL) {
		do {
			std::cout << p->data << " ";
			p = p->next;
		} while (p != begin);
	}
}
int main() {
	using namespace std;
	node*list=initilist();
	listhead(list, 2);
	listhead(list, 1);
	node* tail = get_tail(list);
	tail = listtail(tail, 3);
	tail = listtail(tail, 4);
	tail = listtail(tail, 5);
	tail = listtail(tail, 6);
	tail = listtail(tail, 7);
	clearlist(list);
	//node* list2 = initilist();
	///*listhead(list2, 'a');
	//listhead(list2, 'b');
	//node* tail2 = get_tail(list2);
	//tail2 = listtail(tail2, 'o');
	//tail2 = listtail(tail2, 'l');
	//tail2 = listtail(tail2, 'h');
	//tail2 = listtail(tail2, 's');
	//tail2 = listtail(tail2, 'i');*/
	//listnode(list);
	//reorderlist(list);
	////removemiddle(list);
	/*listnode(list);
	clearlist(list);*/
	////node* list2 = reverse(list);
	////listnode(list2);
	///*removenode(list,9);
	//listnode(list);*/
	////listnode(list2);
	////cout << findstrnode(list, list2)->data;
	////findnodeFS(list, 2);

	//node* list = initilist();
	//node* tail = get_tail(list);
	//tail = listtail(tail, 1);
	//tail = listtail(tail, 2);
	//tail = listtail(tail, 3);
	//node* three = tail;
	//tail = listtail(tail, 4);
	//tail = listtail(tail, 5);
	//tail = listtail(tail, 6);
	//tail = listtail(tail, 7);
	//tail = listtail(tail, 8);
	//tail->next = three;
	////node* p = findbegin(list);
	////cout << p->data;
	//printcyclelist(list);
	//clearcyclelist(list);
	//printcyclelist(list);
	//clearlist(list2);
	return 0;
}