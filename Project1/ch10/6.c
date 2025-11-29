#include "exercise.h"
double positive(double, double);
double reverse(double, double);
void sorting(double*, int, double(*p)());
void print(double*, int);

int main() {
	double* m = (double*)malloc(sizeof(double) * 128);
	int n = 0;
	while (scanf("%lf", m + n) == 1) n++;
	while (getchar() != '\n');
	char s = getchar();
	if (s >= 'a' && s <= 'z') {
		sorting(m, n, positive);
		print(m,n);
	}
	else if (s >= '0' && s <= '9') {
		sorting(m, n, reverse);
		print(m, n);
	}
	else {
		printf("break");
	}
	free(m);
	return 0;
}

double positive(double a, double b) {
	return a > b ? 1 : 0;
}
double reverse(double a, double b) {
	return a < b ? 1 : 0;
}
void sorting(double* s, int a, double(*p)(double, double)) {
	for (int i = 0; i < a-1; i++) {
		for (int j = 0; j < a-i - 1; j++) {
			if (p(s[j], s[j + 1])) {
				double t = s[j];
				s[j] = s[j + 1];
				s[j + 1] = t;
			}
		}
	}
}


void print(double* a, int b) {
	for (int i = 0; i < b; i++) {
		printf("%lf ",a[i]);
	}
}