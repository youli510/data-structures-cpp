#include "exercise.h"
#include <ctype.h>
void get_char(int (*p)(char));
int number(char);
int lettle(char);

int main() {
	while (1) {
		int sign = getchar();
		if (sign == 'q' || sign == 'Q') {
			printf("退出\n");
			break;
		}
		if (sign == '1') {
			get_char(lettle);
		}
		else {
			get_char(number);
		}
		while (getchar() != '\n');
	}
	return 0;
}

void get_char(int (*p)(char)) {
	getchar();
	char ch;
	while ((ch=getchar()) != EOF && ch!='\n') {
		if (ch == ' ') continue;
		printf("%c %d ", ch, p(ch));
	}
	printf("结束");
}

int number(char ch) {
	if (!isdigit(ch)) {
		return -1;
	}
	else {
		return ch-'0';
	}
}

int lettle(char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A' + 1;
	}
	else if (ch >= 'a' && ch <= 'z') {
		return ch - 'a' + 1;
	}
	else {
		return -1;
	}
}