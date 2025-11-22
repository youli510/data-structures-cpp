#include "exercise.h"
void change(double*, double*, double*,int (*p)(void));
int small(void);
int big(void);

int main() {
	double a, b, c;
	scanf("%lf %lf %lf",&a,&b,&c);
	int i;
	if (scanf("%d",&i)==1 && i==1) {
		change(&a, &b, &c, small);
	}
	else {
		change(&a, &b, &c, big);
	}

	printf("½»»»ºó:%lf %lf %lf ", a, b, c);
	return 0;
}

void change(double* a, double* b, double* c, int (*p)(void)) {
    double x = *a, y = *b, z = *c;
    double min_val, mid_val, max_val;
    if (x < y) {
        if (y < z) {         
            min_val = x;
            mid_val = y;
            max_val = z;
        }
        else if (x < z) {   
            min_val = x;
            mid_val = z;
            max_val = y;
        }
        else {              
            min_val = z;
            mid_val = x;
            max_val = y;
        }
    }
    else {
        if (x < z) {          
            min_val = y;
            mid_val = x;
            max_val = z;
        }
        else if (y < z) {   
            min_val = y;
            mid_val = z;
            max_val = x;
        }
        else {              
            min_val = z;
            mid_val = y;
            max_val = x;
        }
    }
    if (p() == 1) {  
        *a = min_val;
        *b = mid_val;
        *c = max_val;
    }
    else {          
        *a = max_val;
        *b = mid_val;
        *c = min_val;
    }
}

int small(void) {
	return 1;
}
int big(void) {
	return 0;
}



