#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
int main() {
	char check = {};
	char ch;

	printf("\" �������� �ູ�� VC++ \"\n");
	while (1) {
		ch = _getch();
		if (ch == 27) break;
		printf("command>");
		scanf("\n%c", &check);
		if (check == 'q') {
			printf("qwer ȭ����\n");
		}
		else if (check == 'w') {
			printf("���� �ʹ� ����\n");
		}
		else if (check == 'e') {
			printf("���ֺ��� ������ 3���\n");
		}
		else if (check == 'r') {
			printf("�ູ�մϴ�\n");
		}
		else {
			printf("�߸��Է��ϼ̽��ϴ� �ٽ� �Է��ϼ���.\n");
		}
	}
	return 0;
}