#include "exercise.h"


int main() {
	double arr[][5] = {
			{0.2, 0.4, 2.4, 3.5, 6.6},
			{8.5, 8.2, 1.2, 1.6, 2.4},
			{9.1, 8.5, 2.3, 6.1, 8.4},
	};
	int n, m;
	scanf("%d %d", &n, &m);
	double** creat_2d_arr(int, int);
	double ** str = creat_2d_arr(n, m);
	//double* str = (double*)malloc(sizeof(double) * n * m);
	void cope_double(double (*)[], double**, int, int);
	cope_double(arr, str, n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%lf ", str[i][j]);
		}
		printf("\n");
	}
	void free_2d_array(double** arr, int n);
	free_2d_array(str,n);
	return 0;

}
void free_2d_array(double** arr, int n) {
	for (int i = 0; i < n; i++) {
		free(arr[i]); 
	}
	free(arr); 
}
double** creat_2d_arr(int a, int b) {
	double** arr = (double**)malloc(sizeof(double*) * a);
	for (int i = 0; i < a; i++) {
		arr[i] = (double*)malloc(sizeof(double) * b);
	}
	return arr;

}
void cope_double(double (*src)[5], double** det, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			det[i][j] = src[i][j];
		}
	}
}