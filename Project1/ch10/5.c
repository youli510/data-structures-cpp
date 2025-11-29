#include "exercise.h"
double d(double*, int);

int main() {
	double* m = (double*)malloc(sizeof(double) * 128);
	int n = 0;
	while (scanf("%lf", m + n) == 1) n++;
	printf("%lf",d(m,n));
	free(m);

	return 0;



}


double d(double* a, int b) {
	double max = a[0], min = a[0];
	for (int i = 1; i < b; i++) {
		if (a[i] > max) max = a[i];
		if (a[i] < min) min = a[i];
	}
	return max - min;
}