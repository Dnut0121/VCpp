#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;


	case WM_MOUSEMOVE:
	{
		// 마우스 이동 중
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);

		isMouseLButtonPressed = 0;

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
		InvalidateRect(hwnd, NULL, TRUE);
	}

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);
		if (isMouseLButtonPressed)
		{
			/*원그리기
			*/
			HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검정색 브러시 생성
			HBRUSH hOldBrush = SelectObject(hdc, hBlackBrush); // 현재 브러시 저장하고 검정색 브러시 선택

			int centerX = (startPoint.x + endPoint.x) / 2; // 원의 중심 x 좌표
			int centerY = (startPoint.y + endPoint.y) / 2; // 원의 중심 y 좌표
			int radius = abs(startPoint.x - endPoint.x) / 2; // 반지름 (절대값 사용)

			Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius); // 원 그리기 ellipse 함수

			/*사각형그리기
			
			RECT rect;
			rect.left = startPoint.x;     // 왼쪽 상단 점의 x 좌표
			rect.top = startPoint.y;      // 왼쪽 상단 점의 y 좌표
			rect.right = endPoint.x;     // 오른쪽 하단 점의 x 좌표
			rect.bottom = endPoint.y;  // 오른쪽 하단 점의 y 좌표

			HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검정색 브러시 생성
			FillRect(hdc, &rect, hBlackBrush); // 검정색 브러시를 사용하여 사각형을 채우기

			GetClientRect(hwnd, &rect);
			*/

			/*마우스그리기
			
			RECT rect;
			GetClientRect(hwnd, &rect);
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
			LineTo(hdc, endPoint.x, endPoint.y);
			*/
		}

		ReleaseDC(hwnd, hdc);
		//isMouseLButtonPressed = 0; //도형이 끊어져서나옴
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

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
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 1320, 800 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("컴소 Application"),
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