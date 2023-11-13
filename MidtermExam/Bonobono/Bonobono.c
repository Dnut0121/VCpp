#include <windows.h>
#include <math.h>
void ryan(HDC hdc, int x, int y, int z, int v) {
    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    HBRUSH skin = CreateSolidBrush(RGB(255, 200, 15));
    HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, skin); //x = 250, y = 150, z = 550, v = 480
    Ellipse(hdc, x, y, x+(z-x)/3, y+(v-y)/10*3);//귀1
    Ellipse(hdc, z-(z-x)/3, y, z, y+(v - y)/10 * 3);//귀2
    Ellipse(hdc, x, y+(v-y)/10, z, v);//피부
    SelectObject(hdc, white);
    Ellipse(hdc, x + (z - x) / 3, y + (v - y) / 10 * 6, x + (z - x) / 2, y + (v - y) / 10 * 7);//하얀색
    Ellipse(hdc, x + (z - x) / 2, y + (v - y) / 10 * 6, x + (z - x) / 3*2, y + (v - y) / 10 * 7);//하얀색
    SelectObject(hdc, hPen);
    MoveToEx(hdc, x + (z - x) / 6 * 1, y + (v - y) / 10 * 4, NULL); LineTo(hdc, x + (z - x) / 6 * 2, y + (v - y) / 10 * 4); //왼수염2
    MoveToEx(hdc, x + (z - x) / 6 * 4, y + (v - y) / 10 * 4, NULL); LineTo(hdc, x + (z - x) / 6 * 5, y + (v - y) / 10 * 4); //오른수염2
    SelectObject(hdc, black);
    Ellipse(hdc, x+(z-x)/12*3, y + (v - y) / 12 * 6, x + (z - x) / 12 * 4, y + (v - y) / 12 * 7);//눈1
    Ellipse(hdc, z - (z - x) / 12 * 4, y + (v - y) / 12 * 6, z- (z - x) / 12 * 3, y + (v - y) / 12 * 7);//눈2
    DeleteObject(black);
}
//void ryan(HDC hdc, int x, int y, int z, int v) {
//    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
//    HBRUSH skin = CreateSolidBrush(RGB(255, 200, 15));
//    HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
//    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
//    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
//    SelectObject(hdc, skin); //x = 230, y = 150, z = 330, v = 250
//    Ellipse(hdc, 250, 150, 350, 250);//귀1
//    Ellipse(hdc, 450, 150, 550, 250);//귀2
//    Ellipse(hdc, 250, 180, 550, 480);//피부
//    SelectObject(hdc, white);
//    Ellipse(hdc, 340, 330, 400, 380);//하얀색
//    Ellipse(hdc, 400, 330, 460, 380);//하얀색
//    SelectObject(hdc, hPen);
//    MoveToEx(hdc, 310, 270, NULL); LineTo(hdc, 350, 270); //왼수염2
//    MoveToEx(hdc, 490, 270, NULL); LineTo(hdc, 450, 270); //오른수염2
//    SelectObject(hdc, black);
//    Ellipse(hdc, 320, 300, 340, 320);//눈1
//    Ellipse(hdc, 460, 300, 480, 320);//눈2
//    DeleteObject(black);
//}
void DrawCube(HDC hdc, int x, int y, int size) {

    Rectangle(hdc, x, y, x + size, y + size);


    Rectangle(hdc, x + size / 4, y + size / 4, x + size + size / 4, y + size + size / 4);

    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + size / 4, y + size / 4);
    LineTo(hdc, x + size + size / 4, y + size / 4);
    LineTo(hdc, x + size, y);
    LineTo(hdc, x, y);

    MoveToEx(hdc, x, y + size, NULL);
    LineTo(hdc, x + size / 4, y + size + size / 4);
    LineTo(hdc, x + size + size / 4, y + size + size / 4);
    LineTo(hdc, x + size, y + size);
    LineTo(hdc, x, y + size);
}

POINT pt;
RECT rectangle = { 0,0,0,0 };
static RECT drawingArea = { 16, 96, 784, 544 };
POINT startPoint = { 0 };   // 그리기 시작점
POINT endPoint = { 0 };     // 그리기 끝점
int isDrawing = 0;          // 그리기 모드
int isMoving = 0;
int modecheck = 3; //모드체크하기
int radius = 1;
int Brush = 0;
int offsetX = 0;            // 이동할 때 x 좌표 변화량
int offsetY = 0;            // 이동할 때 y 좌표 변화량
int isResizing = 0;     // 크기 조절 모드 여부를 나타내는 변수
POINT resizeStartPoint; // 크기 조절 시작점을 저장하는 변수
int originalRadius;     // 원의 원래 반지름을 저장하는 변수
HBRUSH redBrush;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int margin = 16;
    static int padding = 8;
    HDC hdc = GetDC(hwnd);
    switch (uMsg)
    {
    case WM_CREATE:
        // Create buttons
        CreateWindow(L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE, 0, margin, 160, 64, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE, 160, margin, 160, 64, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE, 320, margin, 160, 64, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow(L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE, 480, margin, 160, 64, hwnd, (HMENU)4, NULL, NULL);
        CreateWindow(L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE, 640, margin, 160, 64, hwnd, (HMENU)5, NULL, NULL);
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
                HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
                HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
                HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
                HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
                SelectObject(hdc, skin);
                Ellipse(hdc, 250, 180, 550, 480);//피부
                SelectObject(hdc, mouth);
                Ellipse(hdc, 380, 350, 420, 430);//입
                SelectObject(hdc, white);
                Ellipse(hdc, 340, 330, 400, 380);//하얀색
                MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //왼수염1
                MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //왼수염2
                Ellipse(hdc, 400, 330, 460, 380);//하얀색
                MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //오른수염1
                MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //오른수염2
                SelectObject(hdc, black);
                Ellipse(hdc, 380, 310, 420, 350);//코
                MoveToEx(hdc, 280, 330, NULL); LineTo(hdc, 300, 320); //왼눈1
                MoveToEx(hdc, 280, 310, NULL); LineTo(hdc, 300, 320); //왼눈2
                MoveToEx(hdc, 520, 330, NULL); LineTo(hdc, 500, 320); //오른눈1
                MoveToEx(hdc, 520, 310, NULL); LineTo(hdc, 500, 320); //오른눈2
                DeleteObject(white);
            }    
        }
        break;
    case WM_KEYUP: {
        if (modecheck == 2) {
            HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
            HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
            HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, skin);
            Ellipse(hdc, 250, 180, 550, 480);//피부
            SelectObject(hdc, mouth);
            Ellipse(hdc, 380, 350, 420, 430);//입
            SelectObject(hdc, white);
            Ellipse(hdc, 340, 330, 400, 380);//하얀색
            MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //왼수염1
            MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //왼수염2
            Ellipse(hdc, 400, 330, 460, 380);//하얀색
            MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //오른수염1
            MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //오른수염2
            SelectObject(hdc, black);
            Ellipse(hdc, 380, 310, 420, 350);//코
            Ellipse(hdc, 290, 310, 300, 330);//눈1
            SelectObject(hdc, white);
            Ellipse(hdc, 292, 315, 297, 325);//눈동자1
            SelectObject(hdc, black);
            Ellipse(hdc, 500, 310, 510, 330);//눈2
            SelectObject(hdc, white);
            Ellipse(hdc, 502, 315, 507, 325);//눈동자2
            DeleteObject(white);
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
            case 3:
                modecheck = 2;
                SetFocus(hwnd);
                break;
            case 4:
                modecheck = 3; // 별
                SetFocus(hwnd);
                break;
            case 5:
                modecheck = 4; // 직선
                SetFocus(hwnd);
                break;
            }
            HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc,&drawingArea, white);
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
        SelectObject(hdc, Brush);

        HBRUSH drawC = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH boxC = CreateSolidBrush(RGB(255, 255, 255));

        RECT drawingRect = { margin, margin + 80, 800 - margin, 480 - margin + 80 };
        FillRect(hdc, &drawingRect, drawC);

        RECT boxRect = { margin + padding, margin + padding + 80, margin + padding + boxWidth, margin + padding + boxHeight + 80 };
        FillRect(hdc, &boxRect, boxC);

        if (modecheck == 0) {
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (modecheck == 1) {
            int centerX = (startPoint.x + endPoint.x) / 2;
            int centerY = (startPoint.y + endPoint.y) / 2;

            // 원의 반지름 계산
            int radius = abs(centerX - startPoint.x);

            // 원 그리기
            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
        }
        else if (modecheck == 2) {
            HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
            HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
            HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, skin);
            Ellipse(hdc, 250, 180, 550, 480);//피부
            SelectObject(hdc, mouth);
            Ellipse(hdc, 380, 350, 420, 430);//입
            SelectObject(hdc, white);
            Ellipse(hdc, 340, 330, 400, 380);//하얀색
            MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //왼수염1
            MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //왼수염2
            Ellipse(hdc, 400, 330, 460, 380);//하얀색
            MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //오른수염1
            MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //오른수염2
            SelectObject(hdc, black);
            Ellipse(hdc, 380, 310, 420, 350);//코
            Ellipse(hdc, 290, 310, 300, 330);//눈1
            SelectObject(hdc, white);
            Ellipse(hdc, 292, 315, 297, 325);//눈동자1
            SelectObject(hdc, black);
            Ellipse(hdc, 500, 310, 510, 330);//눈2
            SelectObject(hdc, white);
            Ellipse(hdc, 502, 315, 507, 325);//눈동자2
            DeleteObject(white);
        }
        else if (modecheck == 3) {
            ryan(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (modecheck == 4) {
            DrawCube(hdc, startPoint.x, startPoint.y, endPoint.x - startPoint.x);
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
    HWND hwnd = CreateWindow(L"곰돌이", L"곰돌이", WS_OVERLAPPED | WS_SYSMENU, 100, 0, 815, 600, NULL, NULL, hInstance, NULL);
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