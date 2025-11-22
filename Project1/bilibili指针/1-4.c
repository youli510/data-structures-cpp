#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void trans(char* s);
void delete_space(char* s);
int palindrome(char* s);
void max1(char*a,char*b,char*r);






int main() {
	char* str = (char*)malloc(128);
	char* str1 = (char*)malloc(128);
	char* r = (char*)malloc(128);
	scanf("%[^\n]",str);
	getchar();
	scanf("%[^\n]", str1);
	//trans(str);
	//delete_space(str);
	/*if (palindrome(str)) {
		printf("YES");
	}
	else {
		printf("NO");
	}
	*/
	max1(str,str1, r);
	printf("%s", r);
	free(str);
	free(str1);
	free(r);
	return 0;
}

int palindrome(char* s) {
	char* left = s;
	char* right = s + strlen(s) - 1;
	while (left < right) {
		if (*left != *right) {
			return 0;
		}
		left++;
		right--;
	}
	return 1;
}
void max1(char* a, char* b, char* r) {
	int maxlen = 0, start = 0;
	int lena = strlen(a), lenb = strlen(b);
	for (int i = 0; i < lena; i++) {
		for (int j = 0; j < lenb; j++) {
			int k = 0;
			while (a[i + k] && b[j + k] && a[i + k] == b[j + k]) k++;
			if (k > maxlen) {
				maxlen = k;
				start = i;
			}
		}
	}
	strncpy(r, a + start, maxlen);
	r[maxlen] = '\0';

}
void delete_space(char* s) {
	while (*s != '\0') {
		if (*s == ' ') {
			char* temp = s;
			while (*temp != '\0') {
				*temp = *(temp + 1);
				temp++;
			}
		}
		else {
			s++;
		}
	}
}
void trans(char* s) {
	while (*s != '\0') {
		if (*s >= 97 && *s <= 122) {
			*s -= 32;
		}
		s++;
	}
}