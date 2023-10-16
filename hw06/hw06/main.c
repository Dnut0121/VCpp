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
        return 1; // 충돌
    }

    return 0; // 충돌하지 않음
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
                // 충돌 발생 시 'Hit' 메시지 출력
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // 충돌하지 않을 때 메시지 지우기
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
                // 충돌 발생 시 'Hit' 메시지 출력
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // 충돌하지 않을 때 메시지 지우기
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
                // 충돌 발생 시 'Hit' 메시지 출력
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // 충돌하지 않을 때 메시지 지우기
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
                // 충돌 발생 시 'Hit' 메시지 출력
                TextOut(hdc, 10, 10, L"Hit", 3);
            }
            else
            {
                // 충돌하지 않을 때 메시지 지우기
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
    /* 윈도우 클래스 선언.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.
    // 윈도우 클래스 값 설정
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpfnWndProc = WindowProc;
    // 윈도우 클래스 등록.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);	//예외
    }
    // Window viewport 영역 조정
    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    // 윈도우 생성
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007018 송원석"),
        WS_OVERLAPPEDWINDOW,
        0, 0,
        width, height,
        NULL, NULL,
        hInstance,
        NULL
    );
    // 오류 검사.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }
    // 창 보이기.
    ShowWindow(hwnd, SW_SHOW); // 창 띄우고
    UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.
    // 메시지 처리 루프.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // 메시지 처리.
    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            // 메시지 해석해줘.
            TranslateMessage(&msg);
            // 메시지를 처리해야할 곳에 전달해줘.
            DispatchMessage(&msg);
        }
        //if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        //{
        //	// 메시지 해석해줘.
        //	TranslateMessage(&msg);
        //	// 메시지를 처리해야할 곳에 전달해줘.
        //	DispatchMessage(&msg);
        //} // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
        //else{}
    }
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    //종료 메시지 보내기
    return (int)msg.wParam;
}