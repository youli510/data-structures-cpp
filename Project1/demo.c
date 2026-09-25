#define _CRT_SECURE_NO_WARNINGS 1
#include <threads.h>
#include "exercise.h"

#define size 30
int main() {
	int n[size] = {0};
	int a;
	scanf("a=%d", &a);
	getchar();
	for (int i = 0; i < a; i++) {
		scanf("%d",&n[i]);
	}
	for (int i = 1; i < a; i++) {
		int k = n[i];
		int j = i - 1;
		while (j >= 0 && n[j] < k) {
			n[j + 1] = n[j];
			j--;
		}
		n[j + 1] = k;
	}
	for (int i = 0; i < a; i++) {
		printf("%d ", n[i]);
	}
	return 0;
}