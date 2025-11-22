#include "exercise.h"


int main() {
	int arr[10] = {0};
	int s(int, int);
	int l(int, int);
	void sort(int* a, int d, int(*p)(int, int));
	for (int i = 0; i < 10; i++) {
		scanf("%d", &arr[i]);
		getchar();
	}
	int j;
	if (scanf("%d",&j)==1 && j==1) {
		sort(arr, 10, s);
	}
	else {
		sort(arr, 10, l);
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ",arr[i]);
	}
	return 0;
}

void sort(int* a, int d, int(*p)(int, int)) {
	for (int i = 0; i < d - 1; i++) {
		for (int j = 0; j < d - i - 1; j++) {
			if (p(a[j], a[j + 1])) {
				int n = a[j];
				a[j] = a[j + 1];
				a[j + 1] = n;
			}
		}
	}
}




int l(int x, int y) {
	return (x < y) ? 1 : 0;
}


int s(int x,int y) {
	return (x > y) ? 1 : 0;
}
