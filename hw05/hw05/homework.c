#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

RECT rectangles[100];     // 여러 개의 사각형을 저장하는 배열
int numRectangles = 0;      // 현재 배열에 저장된 사각형의 개수
int selectedRectangle = -1; // 선택한 사각형의 인덱스
POINT startPoint = { 0 };   // 사각형 그리기 시작점
POINT endPoint = { 0 };     // 사각형 그리기 끝점
int isDrawing = 0;          // 사각형 그리기 모드
int isMoving = 0;           // 사각형 이동 모드
int offsetX = 0;            // 이동할 때 x 좌표 변화량
int offsetY = 0;            // 이동할 때 y 좌표 변화량
INT box = 0;                // 임시저장 변수
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
        // 왼쪽 클릭으로 사각형 그리기 시작
        isDrawing = 1;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        endPoint.x = startPoint.x;
        endPoint.y = startPoint.y;
        break;

    case WM_MOUSEMOVE:
        if (isDrawing)
        {
            // 왼쪽 클릭을 누른 상태에서 움직일 때
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, NULL, TRUE); // 화면 갱신
        }
        else if (isMoving)
        {
            // 오른쪽 클릭을 누른 상태에서 움직일 때
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            // 선택한 사각형 이동
            if (selectedRectangle >= 0 && selectedRectangle < numRectangles)
            {
                startPoint.x = rectangles[selectedRectangle].left;
                startPoint.y = rectangles[selectedRectangle].top;
                endPoint.x = rectangles[selectedRectangle].right;
                endPoint.y = rectangles[selectedRectangle].bottom;
                rectangles[selectedRectangle].left = mouseX - offsetX;
                rectangles[selectedRectangle].top = mouseY - offsetY;
                rectangles[selectedRectangle].right = rectangles[selectedRectangle].left + (endPoint.x - startPoint.x);
                rectangles[selectedRectangle].bottom = rectangles[selectedRectangle].top + (endPoint.y - startPoint.y);
                InvalidateRect(hwnd, NULL, TRUE); // 화면 갱신
            }
        }
        break;

    case WM_LBUTTONUP:
        if (isDrawing)
        {
            // 왼쪽 클릭을 뗄 때
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawing = 0; // 그리기 모드 종료
            // 새로운 사각형을 배열에 추가
            if (startPoint.x > endPoint.x) {
                box = startPoint.x;
                startPoint.x = endPoint.x;
                endPoint.x = box;
            }
            if (startPoint.y > endPoint.y) {
                int box2 = startPoint.y;
                startPoint.y = endPoint.y;
                endPoint.y = box2;
            }

            if (numRectangles < 100)
            {
                rectangles[numRectangles].left = startPoint.x;
                rectangles[numRectangles].top = startPoint.y;
                rectangles[numRectangles].right = endPoint.x;
                rectangles[numRectangles].bottom = endPoint.y;
                numRectangles++;
            }
            InvalidateRect(hwnd, NULL, TRUE); // 화면 갱신
        }
        break;

    case WM_RBUTTONDOWN:
    {
        // 오른쪽 클릭으로 사각형 선택 모드 시작
        isMoving = 1;
        selectedRectangle = -1;

        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        // 어떤 사각형이 선택되었는지 확인
        for (int i = 0; i < numRectangles; i++)
        {
            if (mouseX >= rectangles[i].left && mouseX <= rectangles[i].right && mouseY >= rectangles[i].top && mouseY <= rectangles[i].bottom)
            {
                selectedRectangle = i;
                offsetX = mouseX - rectangles[i].left;
                offsetY = mouseY - rectangles[i].top;
                break;
            }
        }
    }
    break;

    case WM_RBUTTONUP:
        if (isMoving)
        {
            // 오른쪽 클릭을 뗄 때
            isMoving = 0; // 이동 모드 종료
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // 클라이언트 영역 초기화
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

        // 그려진 사각형 그리기
        for (int i = 0; i < numRectangles; i++)
        {
            if (i == selectedRectangle)
            {
                // 선택한 사각형을 다른 색으로 그리기
                HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 브러시
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
                Rectangle(hdc, rectangles[i].left, rectangles[i].top, rectangles[i].right, rectangles[i].bottom);
                SelectObject(hdc, oldBrush);
                DeleteObject(brush);
            }
            else
            {
                // 선택하지 않은 사각형 그리기
                Rectangle(hdc, rectangles[i].left, rectangles[i].top, rectangles[i].right, rectangles[i].bottom);
            }
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
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

    while (msg.message != WM_QUIT)
    {
        // 메시지 처리.
        if (GetMessage(&msg, hwnd, 0, 0))
            //if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
        {

            // 메시지 해석해줘.
            TranslateMessage(&msg);
            // 메시지를 처리해야할 곳에 전달해줘.
            DispatchMessage(&msg);

        }
        /*else
        {

        }*/
    }

    //종료 메시지 보내기
    return (int)msg.wParam;

}