#include "exercise.h"


int main() {
	double countdown(double,double);
	float a, b;
	scanf("%f %f",&a,&b);
	printf("%f",countdown(a,b));

	return 0;
}



double countdown(double x, double y) {
	double x1 = 1 / x,y1=1/y;
	double avg = 1 / ((x1 + y1) / 2);
	return avg;
}