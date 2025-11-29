#include "exercise.h"
int find(int*,int);


int main() {
	int* m = (int*)malloc(sizeof(int) * 128);
	int n = 0;
	while (scanf("%d", m + n) == 1) {
		n++;
		if (getchar() == '\n') break;
	}
	printf("%d", find(m,n));


	free(m);
	return 0;
}

int find(int* a,int n) {
	int i,max = 0;
	for ( i = 0; i < n; i++) {
		if (a[i] > a[max]) max = i;
	}
	return max+1;
}
