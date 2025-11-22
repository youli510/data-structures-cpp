#include "exercise.h"

int main() {
	char* head = (char*)malloc(sizeof(char) * 128);
	char* tail = (char*)malloc(sizeof(char) * 128);
	char* str = (char*)malloc(sizeof(char) * 128);
	char* res = (char*)malloc(sizeof(char) * 128);
	fgets(head, 128, stdin);
	head[strcspn(head, "\n")] = '\0';  
	fgets(tail, 128, stdin);
	tail[strcspn(tail, "\n")] = '\0';
	fgets(str, 128, stdin);
	str[strcspn(str, "\n")] = '\0';
	void seekstr(char* tou, char* wei, char* s,char * res);
	seekstr(head, tail, str,res);
	printf("%s", res);



	free(head);
	free(tail);
	free(str);
	free(res);
	return 0;
}


void seekstr(char* tou, char* wei, char* s,char * res) {
	char* h = strstr(s, tou);
	if (h) {
		char* t = strstr(h + strlen(tou), wei);
		if (t) {
			int len = t - h + strlen(wei);
			strncpy(res, h, len);
			res[len] = '\0';
		}
	}
}




