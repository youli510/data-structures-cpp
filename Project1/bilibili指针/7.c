#include "exercise.h"

char norepetition(char* s) {
	int a[256] = {0};
	char* t = s;
	while (*t) {
		a[*t]++;
		t++;
	}
	t = s;
	while (*t) {
		if (a[*t] == 1) {
			return *t;
		}
		t++;
	}
	return '\0';
}



int main() {

	char norepetition(char*s);
	char* str = (char*)malloc(sizeof(char) * 100);
	scanf("%[^\n]", str);
	char re = norepetition(str);
	printf("%c",re);








	
	free(str);










	/*int a[3][4] = { {1,2,3,4},{2,3,4,5},{3,4,5,6} };
	int j, i;*/
	//
	////int (*p)[4] = a;
	//int* p[3] = { a[0],a[1],a[2] };
	//for (i = 0; i < sizeof(a)/sizeof (a[0]); i++) {
	//	for (j = 0; j < sizeof (a[0])/sizeof(a[0][0]); j++) {
	//		//printf("%d", *(*(p + i) + j));
	//		printf("%d",p[i][j]);
	//	}
	//	printf("\n");
	//}
	//
	//int (*p)[4] = a, * q = a[0];
	//for (i = 0; i < 3; i++) {
	//	if (i == 0) {
	//		(*p)[i + i / 2] = *q + 1;
	//	}
	//	else {
	//		p++, q++;
	//	}
	//}
	//for (i = 0; i < 3; i++) {
	//	printf("%d,", a[i][i]);
	//}
	//printf("%d,%d\n", *((int*)p), *q);
	//
	return 0;

}