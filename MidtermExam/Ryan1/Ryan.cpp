#include <Windows.h>
#include "yuhanCG.h"

POINT pt;
RECT rectangle = { 0,0,0,0 };
static RECT drawingArea = { 16, 76, 784, 464 };
POINT startPoint = { 0 };   // �׸��� ������
POINT endPoint = { 0 };     // �׸��� ����
int isDrawing = 0;          // �׸��� ���
int isMoving = 0;
int modecheck = 0; //���üũ�ϱ�
int radius = 1;
int Brush = 0;
int offsetX = 0;            // �̵��� �� x ��ǥ ��ȭ��
int offsetY = 0;            // �̵��� �� y ��ǥ ��ȭ��
int isResizing = 0;     // ũ�� ���� ��� ���θ� ��Ÿ���� ����
POINT resizeStartPoint; // ũ�� ���� �������� �����ϴ� ����
int originalRadius;     // ���� ���� �������� �����ϴ� ����
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int margin = 16;
    HDC hdc = GetDC(hwnd);
    switch (uMsg)
    {
    case WM_CREATE:
        // Create buttons
        CreateWindow(L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE, margin, margin, 135, 54, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE, 155+margin, margin, 135, 54, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE, 315+margin, margin, 135, 54, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow(L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE, 475+margin, margin, 135, 54, hwnd, (HMENU)4, NULL, NULL);
        CreateWindow(L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE, 635+margin, margin, 135, 54, hwnd, (HMENU)5, NULL, NULL);
        return 0;

    case WM_LBUTTONDOWN:
        isDrawing = 1;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        endPoint.x = startPoint.x;
        endPoint.y = startPoint.y;
        break;

    case WM_MOUSEMOVE:

        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        // ���콺 �����Ͱ� ����� ���� �ȿ� �ִ��� Ȯ��
        if (PtInRect(&drawingArea, pt)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS)); // ũ�ν��� ���콺 �����ͷ� ����
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW)); // �⺻ ȭ��ǥ ���콺 �����ͷ� ����
        }
        if (isDrawing)
        {
            // ���� Ŭ���� ���� ���¿��� ������ ��
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, &drawingArea, TRUE); // ȭ�� ����
        }
        else if (isMoving)
        {
            // ������ Ŭ���� ���� ���¿��� ������ ��
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            // ������ �簢�� �̵�
            if (modecheck == 0) {
                startPoint.x = rectangle.left;
                startPoint.y = rectangle.top;
                endPoint.x = rectangle.right;
                endPoint.y = rectangle.bottom;
                rectangle.left = mouseX - offsetX;
                rectangle.top = mouseY - offsetY;
                rectangle.right = rectangle.left + (endPoint.x - startPoint.x);
                rectangle.bottom = rectangle.top + (endPoint.y - startPoint.y);
            }
            else if (modecheck == 1) {
                if (isResizing) {
                    // ���� ���콺 ��ǥ�� ���� ���콺 ��ǥ ������ �Ÿ� ���
                    int prevX = resizeStartPoint.x;
                    int prevY = resizeStartPoint.y;
                    // ���� ���콺 ��ǥ�� ���
                    int currX = LOWORD(lParam);
                    int currY = HIWORD(lParam);
                    int dx = currX - prevX;
                    int dy = currY - prevY;
                    int newRadius = originalRadius + dx;

                    // ���� �߽� ���
                    int centerX = (startPoint.x + endPoint.x) / 2;
                    int centerY = (startPoint.y + endPoint.y) / 2;

                    // ���� �� ��ġ �� ũ�� ����
                    startPoint.x = centerX - newRadius;
                    startPoint.y = centerY - newRadius;
                    endPoint.x = centerX + newRadius;
                    endPoint.y = centerY + newRadius;

                    InvalidateRect(hwnd, &drawingArea, TRUE); // ȭ�� ����
                }
            }

            InvalidateRect(hwnd, &drawingArea, TRUE); // ȭ�� ����

        }
        break;

    case WM_LBUTTONUP:
        if (isDrawing)
        {
            // ���� Ŭ���� �� ��
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawing = 0; // �׸��� ��� ����
            if (modecheck == 0) {
                if (startPoint.x > endPoint.x) {
                    int box = startPoint.x;
                    startPoint.x = endPoint.x;
                    endPoint.x = box;
                }
                if (startPoint.y > endPoint.y) {
                    int box = startPoint.y;
                    startPoint.y = endPoint.y;
                    endPoint.y = box;
                }
                rectangle.left = startPoint.x;
                rectangle.top = startPoint.y;
                rectangle.right = endPoint.x;
                rectangle.bottom = endPoint.y;
                // ȭ�� ����
            }
            InvalidateRect(hwnd, &drawingArea, TRUE);
        }
        break;
    case WM_RBUTTONDOWN:
    {
        isMoving = 1;
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        if (modecheck == 0) {
            if (mouseX >= rectangle.left && mouseX <= rectangle.right && mouseY >= rectangle.top && mouseY <= rectangle.bottom)
            {
                offsetX = mouseX - rectangle.left;
                offsetY = mouseY - rectangle.top;
            }
        }
        else if (modecheck == 1) { // �� ���
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            int centerX = (startPoint.x + endPoint.x) / 2;
            int centerY = (startPoint.y + endPoint.y) / 2;
            int radius = abs(centerX - startPoint.x);

            // ���콺 Ŭ�� ������ �� �ȿ� �ִ��� Ȯ��
            int dx = mouseX - centerX;
            int dy = mouseY - centerY;
            if (dx * dx + dy * dy <= radius * radius) {
                isResizing = 1;
                resizeStartPoint.x = mouseX;
                resizeStartPoint.y = mouseY;
                originalRadius = radius;
            }
        }

        InvalidateRect(hwnd, &drawingArea, TRUE); // ȭ�� ����
    }
    break;
    case WM_RBUTTONUP:
        if (isMoving)
        {
            // ������ Ŭ���� �� ��
            isMoving = 0; // �̵� ��� ����
        }

        if (isResizing) {
            isResizing = 0; // ũ�� ���� ��� ����
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            if (modecheck == 2) {
                DrawBonobono(hwnd, hdc, 0);
            }
        }
        break;
    case WM_KEYUP: {
        if (modecheck == 2) {
            DrawBonobono(hwnd, hdc, 1);
        }
    }
                 break;
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {

            switch (LOWORD(wParam)) {
            case 1:
                modecheck = 0; // �簢��
                SetFocus(hwnd);
                break;
            case 2:
                modecheck = 1; // ��
                SetFocus(hwnd);
                break;
            case 3:             //���뺸��
                modecheck = 2;
                SetFocus(hwnd);
                break;
            case 4:
                modecheck = 3; // ���̾�
                SetFocus(hwnd);
                break;
            case 5:
                modecheck = 4; // ť��
                SetFocus(hwnd);
                break;
            }
            HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &drawingArea, white);
        }
        break;

    case WM_PAINT:
    {
        static int margin = 8;
        static int padding = 8;
        int boxWidth = 800 - 2 * margin - 2 * padding; // ����� ���� ������ �ڽ��� �ʺ�
        int boxHeight = 480 - 2 * margin - 2 * padding; // ����� ���� ������ �ڽ��� ����
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));
        // Ŭ���̾�Ʈ ���� �ʱ�ȭ
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        FillRect(hdc, &clientRect, hBackgroundBrush);

        HBRUSH drawC = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH boxC = CreateSolidBrush(RGB(255, 255, 255));

        RECT drawingRect = { margin, margin, 800 - margin, 480 - margin };
        FillRect(hdc, &drawingRect, drawC);

        RECT boxRect = { margin + padding, margin + padding+60, margin + padding + boxWidth, margin + padding + boxHeight};
        FillRect(hdc, &boxRect, boxC);

        if (modecheck == 0) {
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (modecheck == 1) {
            int centerX = (startPoint.x + endPoint.x) / 2;
            int centerY = (startPoint.y + endPoint.y) / 2;
            int radius = abs(centerX - startPoint.x);
            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
        }
        else if (modecheck == 2) {
            DrawBonobono(hwnd, hdc, 1);
        }
        else if (modecheck == 3) {
            DrawRyan(hwnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (modecheck == 4) {
        }


        EndPaint(hwnd, &ps);
    }
    break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    ReleaseDC(hwnd, hdc);
    return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
    /* ������ Ŭ���� ����.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.
    // ������ Ŭ���� �� ����
    wc.hInstance = hInstance;
    wc.lpszClassName = L"������";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    //wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpfnWndProc = WindowProc;
    // ������ Ŭ���� ���.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);	//����
    }
    // Window viewport ���� ����
    RECT rect = { 150, 100, 1300, 900 };
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_SYSMENU, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    // ������ ����
    HWND hwnd = CreateWindow(L"������", L"������", WS_OVERLAPPED | WS_SYSMENU, 100, 0, 816, 515, NULL, NULL, hInstance, NULL);
    // �簢�� ��ư

    //������

    // ���� �˻�.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }
    // â ���̱�.
    ShowWindow(hwnd, SW_SHOW); // â ����
    UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.
    // �޽��� ó�� ����.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // �޽��� ó��.
    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            // �޽��� �ؼ�����.
            TranslateMessage(&msg);
            // �޽����� ó���ؾ��� ���� ��������.
            DispatchMessage(&msg);
        }
    }
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    //���� �޽��� ������
    return (int)msg.wParam;
}