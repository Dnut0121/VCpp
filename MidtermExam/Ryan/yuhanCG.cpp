#include "yuhanCG.h"


void DrawBonobono(HWND hwnd, HDC hdc, int blink) {
    if (blink == 0) {
        HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, skin);
        Ellipse(hdc, 250, 180, 550, 480);//ÇÇºÎ
        SelectObject(hdc, mouth);
        Ellipse(hdc, 380, 350, 420, 430);//ÀÔ
        SelectObject(hdc, white);
        Ellipse(hdc, 340, 330, 400, 380);//ÇÏ¾á»ö
        MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //¿Þ¼ö¿°1
        MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //¿Þ¼ö¿°2
        Ellipse(hdc, 400, 330, 460, 380);//ÇÏ¾á»ö
        MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //¿À¸¥¼ö¿°1
        MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //¿À¸¥¼ö¿°2
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 310, 420, 350);//ÄÚ
        MoveToEx(hdc, 280, 330, NULL); LineTo(hdc, 300, 320); //¿Þ´«1
        MoveToEx(hdc, 280, 310, NULL); LineTo(hdc, 300, 320); //¿Þ´«2
        MoveToEx(hdc, 520, 330, NULL); LineTo(hdc, 500, 320); //¿À¸¥´«1
        MoveToEx(hdc, 520, 310, NULL); LineTo(hdc, 500, 320); //¿À¸¥´«2
        DeleteObject(white);
    }
    else if (blink == 1) {
        HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, skin);
        Ellipse(hdc, 250, 180, 550, 480);//ÇÇºÎ
        SelectObject(hdc, mouth);
        Ellipse(hdc, 380, 350, 420, 430);//ÀÔ
        SelectObject(hdc, white);
        Ellipse(hdc, 340, 330, 400, 380);//ÇÏ¾á»ö
        MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //¿Þ¼ö¿°1
        MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //¿Þ¼ö¿°2
        Ellipse(hdc, 400, 330, 460, 380);//ÇÏ¾á»ö
        MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //¿À¸¥¼ö¿°1
        MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //¿À¸¥¼ö¿°2
        SelectObject(hdc, black);
        Ellipse(hdc, 380, 310, 420, 350);//ÄÚ
        Ellipse(hdc, 290, 310, 300, 330);//´«1
        SelectObject(hdc, white);
        Ellipse(hdc, 292, 315, 297, 325);//´«µ¿ÀÚ1
        SelectObject(hdc, black);
        Ellipse(hdc, 500, 310, 510, 330);//´«2
        SelectObject(hdc, white);
        Ellipse(hdc, 502, 315, 507, 325);//´«µ¿ÀÚ2
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
    Ellipse(hdc, left, top, left + (right - left) / 3, top + (bottom - top) / 10 * 3);//±Í1
    Ellipse(hdc, right - (right - left) / 3, top, right, top + (bottom - top) / 10 * 3);//±Í2
    Ellipse(hdc, left, top + (bottom - top) / 10, right, bottom);//ÇÇºÎ
    SelectObject(hdc, white);
    Ellipse(hdc, left + (right - left) / 3, top + (bottom - top) / 10 * 6, left + (right - left) / 2, top + (bottom - top) / 10 * 7);//ÇÏ¾á»ö
    Ellipse(hdc, left + (right - left) / 2, top + (bottom - top) / 10 * 6, left + (right - left) / 3 * 2, top + (bottom - top) / 10 * 7);//ÇÏ¾á»ö
    SelectObject(hdc, hPen);
    MoveToEx(hdc, left + (right - left) / 6 * 1, top + (bottom - top) / 10 * 4, NULL); LineTo(hdc, left + (right - left) / 6 * 2, top + (bottom - top) / 10 * 4); //¿Þ¼ö¿°2
    MoveToEx(hdc, left + (right - left) / 6 * 4, top + (bottom - top) / 10 * 4, NULL); LineTo(hdc, left + (right - left) / 6 * 5, top + (bottom - top) / 10 * 4); //¿À¸¥¼ö¿°2
    SelectObject(hdc, black);
    Ellipse(hdc, left + (right - left) / 12 * 3, top + (bottom - top) / 12 * 6, left + (right - left) / 12 * 4, top + (bottom - top) / 12 * 7);//´«1
    Ellipse(hdc, right - (right - left) / 12 * 4, top + (bottom - top) / 12 * 6, right - (right - left) / 12 * 3, top + (bottom - top) / 12 * 7);//´«2
    DeleteObject(black);
}
void DrawCube(HDC hdc, int x, int y, int x2, int y2) {
    // ÁÖ¾îÁø ÁÂÇ¥¸¦ »ç¿ëÇÏ¿© Å¥ºê¸¦ ±×¸®´Â ÇÔ¼ö

    int size = x2 - x;
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }

    // Å¥ºêÀÇ ¿·¸é ¼± ±×¸®±â
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + size / 4, y - size / 4);
    LineTo(hdc, x2 + size / 4, y2 - size / 4);
    LineTo(hdc, x2, y2);
    LineTo(hdc, x, y);

    // Å¥ºêÀÇ ¾Õ¸é ¼± ±×¸®±â
    MoveToEx(hdc, x, y2, NULL);
    LineTo(hdc, x + size / 4, y2 - size / 4);
    LineTo(hdc, x2 + size / 4, y2 - size / 4);
    LineTo(hdc, x2, y2);
    LineTo(hdc, x, y2);

    // Å¥ºêÀÇ Àü¸é ±×¸®±â
    if (x2 < x) {
        Rectangle(hdc, x, y, x2, y2);
        Rectangle(hdc, x + size / 4, y - size / 4, x2 + size / 4, y2 - size / 4);
    }
    else {
        Rectangle(hdc, x + size / 4, y - size / 4, x2 + size / 4, y2 - size / 4);
        Rectangle(hdc, x, y, x2, y2);
    }

}

