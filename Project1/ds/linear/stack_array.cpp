//栈
#include <iostream>
#include <cstdint>
typedef int bit32;
#define MAXSIZE 100
struct stack {
	bit32 data[MAXSIZE];
	int top;
};
void initstack(stack*s) {
	s->top = -1;
}
stack* initstack() {
	stack* s = new stack;
	initstack(s);
	return s;
}
bool isempty(const stack* s) {
	return s->top == -1;
}
bool isfull(const stack* s) {
	return s->top >= MAXSIZE - 1;
}
bool push(stack*s,bit32 n) {
	if (isfull(s)) {
		std::cout << "满了";
		return false;
	}
	s->top++;
	s->data[s->top] = n;
	return true;
}
bool pop(stack*s,bit32*n) {
	if (isempty(s)) {
		std::cout << "空的";
		return false;
	}
	*n = s->data[s->top];
	s->top--;
	return true;
}
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