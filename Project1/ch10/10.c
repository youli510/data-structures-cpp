#include "exercise.h"
void print_int(const void* elem);
void dou_arr(int**, int**,int, int);
int** plus_arr(int**, int**, int, int);
int** arr_mul_matrix(int** str1, int** str2, int a1, int b1);
int** arr_sub(int** str1, int** str2, int a, int b);
int** arr_mul_elem(int** str1, int** str2, int a, int b);


int main() {
	int input = 1;
	int** (*p[5])(int**, int**, int, int) = { 0, plus_arr, arr_sub, arr_mul_elem, arr_mul_matrix };
	int b,a,a1,b1;

	do {
		printf("\n*************************\n");
		printf(" 1:数组加法（对应元素）\n");
		printf(" 2:数组减法（对应元素）\n");
		printf(" 3:数组乘法（对应元素）\n");
		printf(" 4:矩阵乘法（线性代数）\n");
		printf(" 0:退出计算器\n");
		printf("*************************\n");
		printf("请选择：");
		while (scanf("%d", &input) != 1) { 
			printf("输入错误！请输入0-4的数字：");
			while (getchar() != '\n');
		}
		if (input >= 1 && input <= 3) {
			printf("请输入数组的行数和列数（空格分隔）：");
			while (scanf("%d %d", &a, &b) != 2 || a <= 0 || b <= 0) {
				printf("输入错误！请输入两个正整数：");
				while (getchar() != '\n');
			}
			int** str1 = (int**)creat_2d_arr(a, b, sizeof(int));
			int** str2 = (int**)creat_2d_arr(a, b, sizeof(int));
			if (str1 == NULL || str2 == NULL) {
				free_2d_arr(str1, a);
				free_2d_arr(str2, a);
				continue;
			}
			printf("输入第一个数组：\n");
			input_2d_arr(str1, a, b);
			printf("输入第二个数组：\n");
			input_2d_arr(str2, a, b);
			int** res = p[input](str1, str2, a, b);
			if (res != NULL) {
				show_2d_arr((void**)res, a, b, sizeof(int), print_int);
				free_2d_arr(res, a); 
			}
			free_2d_arr(str1, a);
			free_2d_arr(str2, a);
		}
		else if (input == 4) {
			printf("请输入第一个矩阵的行数和列数（str1：行 列）：");
			while (scanf("%d %d", &a1, &b1) != 2 || a1 <= 0 || b1 <= 0) {
				printf("输入错误！请输入两个正整数：");
				while (getchar() != '\n');
			}

			printf("请输入第二个矩阵的行数和列数（str2：行 列）：\n");
			printf("注意：str2的行数必须等于str1的列数（%d）\n", b1);
			int a2, b2;
			while (1) {
				scanf("%d %d", &a2, &b2);
				if (a2 == b1 && a2 > 0 && b2 > 0) break;
				printf("输入错误！str2行数必须为%d，请重新输入：", b1);
				while (getchar() != '\n');
			}
			int** str1 = (int**)creat_2d_arr(a1, b1, sizeof(int));
			int** str2 = (int**)creat_2d_arr(a2, b2, sizeof(int));
			if (str1 == NULL || str2 == NULL) {
				free_2d_arr(str1, a1);
				free_2d_arr(str2, a2);
				continue;
			}
			printf("输入第一个矩阵（%d行%d列）：\n", a1, b1);
			input_2d_arr(str1, a1, b1);
			printf("输入第二个矩阵（%d行%d列）：\n", a2, b2);
			input_2d_arr(str2, a2, b2);
			int** res = p[input](str1, str2, a1, b1);
			if (res != NULL) {
				show_2d_arr((void**)res, a, b, sizeof(int), print_int);
				free_2d_arr(res, a1);
			}
			free_2d_arr(str1, a1);
			free_2d_arr(str2, a2);

		}
		else if (input == 0) {
			printf("退出数组计算器\n");
		}
		else {
			printf("输入有误！请输入0-4的数字\n");
		}

	} while (input != 0);
	/*int arr1[][4] = {
		{1,2,3,4},
		{5,6,7,8}
	};*/
	/*int n, m;
	scanf("%d %d", &n, &m);
	int** arr2 = (int**)creat_2d_arr(n,m,sizeof(int));
	dou_arr(arr2, (int*)arr1,n, m);
	show_2d_arr((void**)arr2,n,m,sizeof(int),print_int);
	int** arr3 = (int**)creat_2d_arr(n, m, sizeof(int));
	arr3=plus_arr(arr2,(int*)arr1,n,m);
	show_2d_arr((void**)arr3, n, m, sizeof(int), print_int);*/
	//free_2d_arr(arr1, n1);
	/*free_2d_arr(arr2, n);
	free_2d_arr(arr3, n);*/
	return 0;
}
void print_int(const void* elem) {
	printf("%d ", *(const int*)elem);
}
int** plus_arr(int** str2, int** str1, int a, int b) {
	int** arr = (int**)creat_2d_arr(a, b, sizeof(int));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			arr[i][j] = str1[i][j] + str2[i][j];
		}
	}
	return arr;
}
void dou_arr(int** det,int**src, int a, int b) {
	for (int i = 0; i < a; i++) { 
		for (int j = 0; j < b; j++) { 
			det[i][j] = src[i][j]*2;
		}
	}
	
}
int** arr_mul_matrix(int** str1, int** str2, int a1, int b1) {
	int b2;
	printf("请输入第二个矩阵的列数（str2列数）：");
	while (scanf("%d", &b2) != 1 || b2 <= 0) {
		printf("输入错误！请输入正整数：");
		while (getchar() != '\n');
	}
	int** res = (int**)creat_2d_arr(a1, b2, sizeof(int));
	for (int i = 0; i < a1; i++) {
		for (int j = 0; j < b2; j++) {
			res[i][j] = 0;
			for (int k = 0; k < b1; k++) {
				res[i][j] += str1[i][k] * str2[k][j];
			}
		}
	}
	return res;
}
int** arr_sub(int** str1, int** str2, int a, int b) {
	int** res = (int**)creat_2d_arr(a, b, sizeof(int));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			res[i][j] = str1[i][j] - str2[i][j];
		}
	}
	return res;
}
int** arr_mul_elem(int** str1, int** str2, int a, int b) {
	int** res = (int**)creat_2d_arr(a, b, sizeof(int));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			res[i][j] = str1[i][j] * str2[i][j];
		}
	}
	return res;
}


