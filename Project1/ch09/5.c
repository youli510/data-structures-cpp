#include "exercise.h"
int little(void);
int larger(void);
void off(int* a, int* b, int (*p)(void));

int main() {
	int x, y;
	scanf("%d %d",&x,&y);
	getchar();
	int a = getchar()-'0';
	if (a == 1) {
		off(&x, &y, larger);
	}
	else {
		off(&x, &y, little);
	}
	printf("½»»»ºó:x=%d y=%d",x,y);



	return 0;
}
void off(int* a, int* b,int(*p)(void)) {
	
	if (p()) {
		int maxv = (*a > *b) ? *a : *b;
		*a = maxv;
		*b = maxv;
	}
	else {
		int minv = (*a < *b) ? *a : *b;
		*a = minv;
		*b = minv;
	}
}


int larger(void) {
	return 1;
}

int little(void) {
	return 0;
}