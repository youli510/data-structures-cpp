#include "exercise.h"

int main() {
	char chline(char, int, int);
	int i, j;
	char c;
	scanf("%c %d %d",&c,&i,&j);
	printf("%c", chline(c, i, j));


	return 0;
}


char chline(char s, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			printf("%c", s);
		}
		printf("\n");
	}
}