#include <Windows.h>
#include "yuhanCG.h"

POINT pt;
RECT rectangle = { 0,0,0,0 };
static RECT drawingArea = { 16, 76, 784, 464 };
POINT startPoint = { 0 };   // 그리기 시작점
POINT endPoint = { 0 };     // 그리기 끝점
int isDrawing = 0;          // 그리기 모드
int isMoving = 0;
int modecheck = 0; //모드체크하기
int radius = 1;
int Brush = 0;
int offsetX = 0;            // 이동할 때 x 좌표 변화량
int offsetY = 0;            // 이동할 때 y 좌표 변화량
int isResizing = 0;     // 크기 조절 모드 여부를 나타내는 변수
POINT resizeStartPoint; // 크기 조절 시작점을 저장하는 변수
int originalRadius;     // 원의 원래 반지름을 저장하는 변수
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

        // 마우스 포인터가 드로잉 영역 안에 있는지 확인
        if (PtInRect(&drawingArea, pt)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS)); // 크로스형 마우스 포인터로 변경
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW)); // 기본 화살표 마우스 포인터로 변경
        }
        if (isDrawing)
        {
            // 왼쪽 클릭을 누른 상태에서 움직일 때
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, &drawingArea, TRUE); // 화면 갱신
        }
        else if (isMoving)
        {
            // 오른쪽 클릭을 누른 상태에서 움직일 때
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            // 선택한 사각형 이동
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
                    // 현재 마우스 좌표와 이전 마우스 좌표 사이의 거리 계산
                    int prevX = resizeStartPoint.x;
                    int prevY = resizeStartPoint.y;
                    // 현재 마우스 좌표를 얻기
                    int currX = LOWORD(lParam);
                    int currY = HIWORD(lParam);
                    int dx = currX - prevX;
                    int dy = currY - prevY;
                    int newRadius = originalRadius + dx;

                    // 원의 중심 계산
                    int centerX = (startPoint.x + endPoint.x) / 2;
                    int centerY = (startPoint.y + endPoint.y) / 2;

                    // 원의 새 위치 및 크기 설정
                    startPoint.x = centerX - newRadius;
                    startPoint.y = centerY - newRadius;
                    endPoint.x = centerX + newRadius;
                    endPoint.y = centerY + newRadius;

                    InvalidateRect(hwnd, &drawingArea, TRUE); // 화면 갱신
                }
            }

            InvalidateRect(hwnd, &drawingArea, TRUE); // 화면 갱신

        }
        break;

    case WM_LBUTTONUP:
        if (isDrawing)
        {
            // 왼쪽 클릭을 뗄 때
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawing = 0; // 그리기 모드 종료
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
                // 화면 갱신
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
        else if (modecheck == 1) { // 원 모드
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            int centerX = (startPoint.x + endPoint.x) / 2;
            int centerY = (startPoint.y + endPoint.y) / 2;
            int radius = abs(centerX - startPoint.x);

            // 마우스 클릭 지점이 원 안에 있는지 확인
            int dx = mouseX - centerX;
            int dy = mouseY - centerY;
            if (dx * dx + dy * dy <= radius * radius) {
                isResizing = 1;
                resizeStartPoint.x = mouseX;
                resizeStartPoint.y = mouseY;
                originalRadius = radius;
            }
        }

        InvalidateRect(hwnd, &drawingArea, TRUE); // 화면 갱신
    }
    break;
    case WM_RBUTTONUP:
        if (isMoving)
        {
            // 오른쪽 클릭을 뗄 때
            isMoving = 0; // 이동 모드 종료
        }

        if (isResizing) {
            isResizing = 0; // 크기 조절 모드 종료
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
                modecheck = 0; // 사각형
                SetFocus(hwnd);
                break;
            case 2:
                modecheck = 1; // 원
                SetFocus(hwnd);
                break;
            case 3:             //보노보노
                modecheck = 2;
                SetFocus(hwnd);
                break;
            case 4:
                modecheck = 3; // 라이언
                SetFocus(hwnd);
                break;
            case 5:
                modecheck = 4; // 큐브
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
        int boxWidth = 800 - 2 * margin - 2 * padding; // 드로잉 영역 내부의 박스의 너비
        int boxHeight = 480 - 2 * margin - 2 * padding; // 드로잉 영역 내부의 박스의 높이
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));
        // 클라이언트 영역 초기화
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
    /* 윈도우 클래스 선언.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.
    // 윈도우 클래스 값 설정
    wc.hInstance = hInstance;
    wc.lpszClassName = L"곰돌이";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    //wc.hCursor = LoadCursor(NULL, IDC_ARROW);
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
    RECT rect = { 150, 100, 1300, 900 };
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_SYSMENU, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    // 윈도우 생성
    HWND hwnd = CreateWindow(L"곰돌이", L"곰돌이", WS_OVERLAPPED | WS_SYSMENU, 100, 0, 816, 515, NULL, NULL, hInstance, NULL);
    // 사각형 버튼

    //빨간색

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
    }
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    //종료 메시지 보내기
    return (int)msg.wParam;
}