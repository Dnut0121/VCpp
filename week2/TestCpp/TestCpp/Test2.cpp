#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
int main() {
	char check = {};
	char ch;

	printf("\" 이은석의 행복한 VC++ \"\n");
	while (1) {
		ch = _getch();
		if (ch == 27) break;
		printf("command>");
		scanf("\n%c", &check);
		if (check == 'q') {
			printf("qwer 화이팅\n");
		}
		else if (check == 'w') {
			printf("과제 너무 좋다\n");
		}
		else if (check == 'e') {
			printf("담주부턴 과제량 3배다\n");
		}
		else if (check == 'r') {
			printf("행복합니다\n");
		}
		else {
			printf("잘못입력하셨습니다 다시 입력하세요.\n");
		}
	}
	return 0;
}