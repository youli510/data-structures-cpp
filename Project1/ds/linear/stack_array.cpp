//栈
#include <iostream>
#include <cstdint>
typedef int bit32;
#define MAXSIZE 100
struct stack {
	bit32 data[MAXSIZE];
	int top;
};
// 初始化栈：把 top 置为 -1（表示空栈）
void initstack(stack*s) {
	s->top = -1;
}
// 分配一个栈对象并初始化，返回它的指针
stack* initstack() {
	stack* s = new stack;
	initstack(s);
	return s;
}
// 判空：top == -1
bool isempty(const stack* s) {
	return s->top == -1;
}
// 判满：top 已到 MAXSIZE-1
bool isfull(const stack* s) {
	return s->top >= MAXSIZE - 1;
}
// 入栈：top 先加 1，再把值写进去
bool push(stack*s,bit32 n) {
	if (isfull(s)) {
		std::cout << "满了";
		return false;
	}
	s->top++;
	s->data[s->top] = n;
	return true;
}
// 出栈（LIFO）：取栈顶值后 top 减 1
bool pop(stack*s,bit32*n) {
	if (isempty(s)) {
		std::cout << "空的";
		return false;
	}
	*n = s->data[s->top];
	s->top--;
	return true;
}
// 只看栈顶的值，不弹出
bool gettop(const stack*s,bit32*n) {
	if (isempty(s)) {
		std::cout << "空的";
		return false;
	}
	*n = s->data[s->top];
	return true;
}

int main() {
	stack *s=initstack();
	//initstack(&s);

	push(s, 10);
	push(s, 20);
	push(s, 30);
	bit32 e;
	pop(s, &e);
	std::cout << e << "\n";
	gettop(s, &e);
	std::cout << e << "\n";
	delete s;

	return 0;
}