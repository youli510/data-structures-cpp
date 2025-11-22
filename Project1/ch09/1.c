#include "exercise.h"

int main() {
	int mmin(int, int);
	int x, y;
	scanf("%d %d",&x,&y);
	printf("%d",mmin(x,y));
	return 0;
}

int mmin(int x, int y) {
	return x < y ? x : y;
}