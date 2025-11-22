#include "exercise.h"


int main() {
	char* str = (char*)malloc(sizeof(char) * 128);
	char ch;
	int i = 0;
	scanf("%[^\n]", str);
	void reverse(char* first,char* end);
	reverse(str,str+strlen(str)-1);
	char *begin = str, *end = str;
	while (*end != '\0') {
		if (*end == ' ') {
			reverse(begin, end - 1);
			char *space_first = end;
			while (space_first && *space_first==' ') {
				space_first++;
			}
			if (space_first && space_first != '\0') {
				end = space_first;
			}
			else {
				break;
			}
			begin = end;
		}
		end++;
	}



	printf("%s",str);

	free(str);
	return 0;
}

void reverse(char* first ,char* end) {
	int sum = end - first + 1;
	char t;
	for (int i = 0; i < sum / 2; i++) {
		t = *first;
		*first++ = *end;
		*end-- = t;
	}

}