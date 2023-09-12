#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
int main() {
	char check = {};
	char ch;

	printf("\"       12312314\"\n");
	printf("\"     이은석님의\"\n");
	printf("\"    Application\"\n");
	while (1) {
		ch = _getch();
		if (ch == 27) break;
		printf("command>");
		scanf("\n%c", &check);
		if (check == 'p') {
			printf("나는 과제를 겁나 잘하는 학생이다.\n");
		}
		else if (check == 'f') {
			printf("나는 과제가 너무 즐겁다\n");
		}
		else if (check == 'j') {
			printf("교수님 과제 더 내주세요\n");
		}
	}
	return 0;
}