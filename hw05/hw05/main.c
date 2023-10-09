#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
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
		// ���콺 �̵� ��
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);

		isMouseLButtonPressed = 0;

		// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
		InvalidateRect(hwnd, NULL, TRUE);
	}

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);
		if (isMouseLButtonPressed)
		{
			/*���׸���
			*/
			HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // ������ �귯�� ����
			HBRUSH hOldBrush = SelectObject(hdc, hBlackBrush); // ���� �귯�� �����ϰ� ������ �귯�� ����

			int centerX = (startPoint.x + endPoint.x) / 2; // ���� �߽� x ��ǥ
			int centerY = (startPoint.y + endPoint.y) / 2; // ���� �߽� y ��ǥ
			int radius = abs(startPoint.x - endPoint.x) / 2; // ������ (���밪 ���)

			Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius); // �� �׸��� ellipse �Լ�

			/*�簢���׸���
			
			RECT rect;
			rect.left = startPoint.x;     // ���� ��� ���� x ��ǥ
			rect.top = startPoint.y;      // ���� ��� ���� y ��ǥ
			rect.right = endPoint.x;     // ������ �ϴ� ���� x ��ǥ
			rect.bottom = endPoint.y;  // ������ �ϴ� ���� y ��ǥ

			HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // ������ �귯�� ����
			FillRect(hdc, &rect, hBlackBrush); // ������ �귯�ø� ����Ͽ� �簢���� ä���

			GetClientRect(hwnd, &rect);
			*/

			/*���콺�׸���
			
			RECT rect;
			GetClientRect(hwnd, &rect);
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
			LineTo(hdc, endPoint.x, endPoint.y);
			*/
		}

		ReleaseDC(hwnd, hdc);
		//isMouseLButtonPressed = 0; //������ ������������
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
	/* ������ Ŭ���� ����.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.

	// ������ Ŭ���� �� ����
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//����
	}

	// Window viewport ���� ����
	RECT rect = { 150, 100, 1320, 800 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("�ļ� Application"),
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

	while (msg.message != WM_QUIT)
	{
		// �޽��� ó��.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		{

			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//���� �޽��� ������
	return (int)msg.wParam;

}