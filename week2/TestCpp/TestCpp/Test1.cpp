#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
int main() {
	char check = {};
	char ch;

	printf("\"       12312314\"\n");
	printf("\"     ����������\"\n");
	printf("\"    Application\"\n");
	while (1) {
		ch = _getch();
		if (ch == 27) break;
		printf("command>");
		scanf("\n%c", &check);
		if (check == 'p') {
			printf("���� ������ �̳� ���ϴ� �л��̴�.\n");
		}
		else if (check == 'f') {
			printf("���� ������ �ʹ� ��̴�\n");
		}
		else if (check == 'j') {
			printf("������ ���� �� ���ּ���\n");
		}
	}
	return 0;
}