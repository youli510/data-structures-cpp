#include "exercise.h"


int main() {
	int arr1[][4] = {
		{1,2,3,4},
		{5,6,7,8}
	};
	int n, m;
	int** dou_arr(int**,int, int);
	scanf("%d %d", &n, &m);
	int** arr2 = (int**)creat_2d_arr(n,m,sizeof(int));
	dou_arr(arr2, n, m);

	free_2d_arr(arr2, n);
	return 0;
}

int** dou_arr(int** str, int a, int b) {
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			str[i][j] = str[i][j] * 2;
		}
	}
	return str;
}


