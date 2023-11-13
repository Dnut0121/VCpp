#include "yuhanCG.h"


void DrawBonobono(HWND hwnd, HDC hdc, int blink) {
    if (blink == 0) {
        HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, skin);
        Ellipse(hdc, 250, 180, 550, 480);//�Ǻ�
        SelectObject(hdc, mouth);
        Ellipse(hdc, 380, 350, 420, 430);//��
        SelectObject(hdc, white);
        Ellipse(hdc, 340, 330, 400, 380);//�Ͼ��
        MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //�޼���1
        MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //�޼���2
        Ellipse(hdc, 400, 330, 460, 380);//�Ͼ��
        MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //��������1
        MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //��������2
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 310, 420, 350);//��
        MoveToEx(hdc, 280, 330, NULL); LineTo(hdc, 300, 320); //�޴�1
        MoveToEx(hdc, 280, 310, NULL); LineTo(hdc, 300, 320); //�޴�2
        MoveToEx(hdc, 520, 330, NULL); LineTo(hdc, 500, 320); //������1
        MoveToEx(hdc, 520, 310, NULL); LineTo(hdc, 500, 320); //������2
        DeleteObject(white);
    }
    else if (blink == 1) {
        HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, skin);
        Ellipse(hdc, 250, 180, 550, 480);//�Ǻ�
        SelectObject(hdc, mouth);
        Ellipse(hdc, 380, 350, 420, 430);//��
        SelectObject(hdc, white);
        Ellipse(hdc, 340, 330, 400, 380);//�Ͼ��
        MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //�޼���1
        MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //�޼���2
        Ellipse(hdc, 400, 330, 460, 380);//�Ͼ��
        MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //��������1
        MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //��������2
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 310, 420, 350);//��
        Ellipse(hdc, 290, 310, 300, 330);//��1
        SelectObject(hdc, white);
        Ellipse(hdc, 292, 315, 297, 325);//������1
        SelectObject(hdc, black);
        Ellipse(hdc, 500, 310, 510, 330);//��2
        SelectObject(hdc, white);
        Ellipse(hdc, 502, 315, 507, 325);//������2
        DeleteObject(white);
    }

}
void DrawRyan(HWND hwnd, HDC hdc, int left, int top, int right, int bottom) {
    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    HBRUSH skin = CreateSolidBrush(RGB(255, 200, 15));
    HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, skin); //left = 250, top = 150, right = 550, bottom = 480
    Ellipse(hdc, left, top, left + (right - left) / 3, top + (bottom - top) / 10 * 3);//��1
    Ellipse(hdc, right - (right - left) / 3, top, right, top + (bottom - top) / 10 * 3);//��2
    Ellipse(hdc, left, top + (bottom - top) / 10, right, bottom);//�Ǻ�
    SelectObject(hdc, white);
    Ellipse(hdc, left + (right - left) / 3, top + (bottom - top) / 10 * 6, left + (right - left) / 2, top + (bottom - top) / 10 * 7);//�Ͼ��
    Ellipse(hdc, left + (right - left) / 2, top + (bottom - top) / 10 * 6, left + (right - left) / 3 * 2, top + (bottom - top) / 10 * 7);//�Ͼ��
    SelectObject(hdc, hPen);
    MoveToEx(hdc, left + (right - left) / 6 * 1, top + (bottom - top) / 10 * 4, NULL); LineTo(hdc, left + (right - left) / 6 * 2, top + (bottom - top) / 10 * 4); //�޼���2
    MoveToEx(hdc, left + (right - left) / 6 * 4, top + (bottom - top) / 10 * 4, NULL); LineTo(hdc, left + (right - left) / 6 * 5, top + (bottom - top) / 10 * 4); //��������2
    SelectObject(hdc, black);
    Ellipse(hdc, left + (right - left) / 12 * 3, top + (bottom - top) / 12 * 6, left + (right - left) / 12 * 4, top + (bottom - top) / 12 * 7);//��1
    Ellipse(hdc, right - (right - left) / 12 * 4, top + (bottom - top) / 12 * 6, right - (right - left) / 12 * 3, top + (bottom - top) / 12 * 7);//��2
    DeleteObject(black);
}
void DrawCube(HDC hdc, int x, int y, int x2, int y2) {
    // �־��� ��ǥ�� ����Ͽ� ť�긦 �׸��� �Լ�

    int size = x2 - x;
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }

    // ť���� ���� �� �׸���
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + size / 4, y - size / 4);
    LineTo(hdc, x2 + size / 4, y2 - size / 4);
    LineTo(hdc, x2, y2);
    LineTo(hdc, x, y);

    // ť���� �ո� �� �׸���
    MoveToEx(hdc, x, y2, NULL);
    LineTo(hdc, x + size / 4, y2 - size / 4);
    LineTo(hdc, x2 + size / 4, y2 - size / 4);
    LineTo(hdc, x2, y2);
    LineTo(hdc, x, y2);

    // ť���� ���� �׸���
    if (x2 < x) {
        Rectangle(hdc, x, y, x2, y2);
        Rectangle(hdc, x + size / 4, y - size / 4, x2 + size / 4, y2 - size / 4);
    }
    else {
        Rectangle(hdc, x + size / 4, y - size / 4, x2 + size / 4, y2 - size / 4);
        Rectangle(hdc, x, y, x2, y2);
    }

}

