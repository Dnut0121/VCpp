#include "yuhanCG.h"


void DrawBonobono(HWND hwnd, HDC hdc, int blink) {
    if (blink == 0) {
        HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, skin);
        Ellipse(hdc, 250, 150, 550, 450);//�Ǻ�
        SelectObject(hdc, mouth);
        Ellipse(hdc, 380, 320, 420, 400);//��
        SelectObject(hdc, white);
        Ellipse(hdc, 340, 300, 400, 350);//�Ͼ��
        MoveToEx(hdc, 320, 310, NULL); LineTo(hdc, 360, 320); //�޼���1
        MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 330); //�޼���2
        Ellipse(hdc, 400, 300, 460, 350);//�Ͼ��
        MoveToEx(hdc, 480, 310, NULL); LineTo(hdc, 440, 320); //��������1
        MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 330); //��������2
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 280, 420, 320);//��
        MoveToEx(hdc, 280, 300, NULL); LineTo(hdc, 300, 290); //�޴�1
        MoveToEx(hdc, 280, 280, NULL); LineTo(hdc, 300, 290); //�޴�2
        MoveToEx(hdc, 520, 300, NULL); LineTo(hdc, 500, 290); //������1
        MoveToEx(hdc, 520, 280, NULL); LineTo(hdc, 500, 290); //������2
        DeleteObject(white);
    }
    else if (blink == 1) {
        HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, skin);
        Ellipse(hdc, 250, 150, 550, 450);//�Ǻ�
        SelectObject(hdc, mouth);
        Ellipse(hdc, 380, 320, 420, 400);//��
        SelectObject(hdc, white);
        Ellipse(hdc, 340, 300, 400, 350);//�Ͼ��
        MoveToEx(hdc, 320, 310, NULL); LineTo(hdc, 360, 320); //�޼���1
        MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 330); //�޼���2
        Ellipse(hdc, 400, 300, 460, 350);//�Ͼ��
        MoveToEx(hdc, 480, 310, NULL); LineTo(hdc, 440, 320); //��������1
        MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 330); //��������2
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 280, 420, 320);//��
        Ellipse(hdc, 290, 280, 300, 300);//��1
        SelectObject(hdc, white);
        Ellipse(hdc, 292, 285, 297, 295);//������1
        SelectObject(hdc, black);
        Ellipse(hdc, 500, 280, 510, 300);//��2
        SelectObject(hdc, white);
        Ellipse(hdc, 502, 285, 507, 295);//������2
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