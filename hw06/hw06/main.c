#include <windows.h>

POINT startPoint2 = { 50, 50 };
POINT endPoint2 = { 150, 150 };

POINT startPoint1 = { 220, 70 };
POINT endPoint1 = { 270, 120 };

int isCollision()
{
    int left1 = startPoint1.x;
    int right1 = endPoint1.x;
    int top1 = startPoint1.y;
    int bottom1 = endPoint1.y;

    int left2 = startPoint2.x;
    int right2 = endPoint2.x;
    int top2 = startPoint2.y;
    int bottom2 = endPoint2.y;


    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2)
    {
        return 1; // �浹
    }

    return 0; // �浹���� ����
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    HBRUSH hBrush;

    switch (uMsg)
    {
    case WM_KEYDOWN:

        switch (wParam)
        {
        case VK_LEFT:
        {
            int prevStartX = startPoint1.x;
            int prevEndX = endPoint1.x;
            startPoint1.x -= 10;
            endPoint1.x -= 10;
            RECT rect1 = { prevStartX, startPoint1.y, prevEndX, endPoint1.y };
            RECT rect2 = { startPoint1.x, startPoint1.y, endPoint1.x, endPoint1.y };
            if (isCollision())
            {
                // �浹 �߻� �� 'Hit' �޽��� ���
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // �浹���� ���� �� �޽��� �����
                RECT messageRect = { 10, 10, 100, 30 };
                FillRect(hdc, &messageRect, (HBRUSH)(COLOR_WINDOW + 1));
            }

            InvalidateRect(hwnd, &rect1, TRUE);
            InvalidateRect(hwnd, &rect2, TRUE);
        }
        break;
        case VK_RIGHT:
        {
            int prevStartX = startPoint1.x;
            int prevEndX = endPoint1.x;
            startPoint1.x += 10;
            endPoint1.x += 10;
            RECT rect1 = { prevStartX, startPoint1.y, prevEndX, endPoint1.y };
            RECT rect2 = { startPoint1.x, startPoint1.y, endPoint1.x, endPoint1.y };

            if (isCollision())
            {
                // �浹 �߻� �� 'Hit' �޽��� ���
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // �浹���� ���� �� �޽��� �����
                RECT messageRect = { 10, 10, 100, 30 };
                FillRect(hdc, &messageRect, (HBRUSH)(COLOR_WINDOW + 1));
            }

            InvalidateRect(hwnd, &rect1, TRUE);
            InvalidateRect(hwnd, &rect2, TRUE);
        }
        break;
        case VK_UP:
        {
            int prevStartY = startPoint1.y;
            int prevEndY = endPoint1.y;
            startPoint1.y -= 10;
            endPoint1.y -= 10;
            RECT rect1 = { startPoint1.x, prevStartY, endPoint1.x, prevEndY };
            RECT rect2 = { startPoint1.x, startPoint1.y, endPoint1.x, endPoint1.y };

            if (isCollision())
            {
                // �浹 �߻� �� 'Hit' �޽��� ���
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // �浹���� ���� �� �޽��� �����
                RECT messageRect = { 10, 10, 100, 30 };
                FillRect(hdc, &messageRect, (HBRUSH)(COLOR_WINDOW + 1));
            }

            InvalidateRect(hwnd, &rect1, TRUE);
            InvalidateRect(hwnd, &rect2, TRUE);
        }
        break;
        case VK_DOWN:
        {
            int prevStartY = startPoint1.y;
            int prevEndY = endPoint1.y;
            startPoint1.y += 10;
            endPoint1.y += 10;
            RECT rect1 = { startPoint1.x, prevStartY, endPoint1.x, prevEndY };
            RECT rect2 = { startPoint1.x, startPoint1.y, endPoint1.x, endPoint1.y };

            if (isCollision())
            {
                // �浹 �߻� �� 'Hit' �޽��� ���
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // �浹���� ���� �� �޽��� �����
                RECT messageRect = { 10, 10, 100, 30 };
                FillRect(hdc, &messageRect, (HBRUSH)(COLOR_WINDOW + 1));
            }
            InvalidateRect(hwnd, &rect1, TRUE);
            InvalidateRect(hwnd, &rect2, TRUE);
        }
        break;

        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

        RECT rect2 = { startPoint2.x, startPoint2.y, endPoint2.x, endPoint2.y };
        hBrush = CreateSolidBrush(RGB(255, 0, 255)); // Green brush
        FillRect(hdc, &rect2, hBrush); // Draw the second rectangle
        DeleteObject(hBrush);

        hBrush = CreateSolidBrush(RGB(0, 0, 255)); // Pink brush
        RECT rect1 = { startPoint1.x, startPoint1.y, endPoint1.x, endPoint1.y };
        FillRect(hdc, &rect1, hBrush); // Draw the first rectangle
        DeleteObject(hBrush);
       

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
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
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
    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    // ������ ����
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007018 �ۿ���"),
        WS_OVERLAPPEDWINDOW,
        0, 0,
        width, height,
        NULL, NULL,
        hInstance,
        NULL
    );
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
        //if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        //{
        //	// �޽��� �ؼ�����.
        //	TranslateMessage(&msg);
        //	// �޽����� ó���ؾ��� ���� ��������.
        //	DispatchMessage(&msg);
        //} // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
        //else{}
    }
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    //���� �޽��� ������
    return (int)msg.wParam;
}