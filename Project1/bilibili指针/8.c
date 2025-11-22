#include "exercise.h"

int main() {
	char* str = (char*)malloc(sizeof(char) * 100);
	int a;
	void left(char*,int);
	scanf("%s %d", str, &a);
	left(str, a);
	printf("%s",str);
	free(str);
	return 0;
}


void left(char* s, int a) {
	char* n = (char*)malloc(sizeof(char) * a);
	int len = strlen(s);
	for (int i = 0; i < a; i++) {
		n[i] = s[i];
	}
	for (int i = a; i < len; i++) {
		s[i - a] = s[i];
	}
	for (int i = 0; i < a; i++) {
		s[len - a + i] = n[i];
	}


	/*int i = a - 1;
	while (s[i] != '\0') {
		s[i - a] = s[i];
		i++;
	}
	for (int i =strlen(s)-a ; i < a; i++) {
		s[i]=n[i-a+1];
	}*/
	free(n);
}