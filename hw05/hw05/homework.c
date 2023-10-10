#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

RECT rectangles[100];     // ���� ���� �簢���� �����ϴ� �迭
int numRectangles = 0;      // ���� �迭�� ����� �簢���� ����
int selectedRectangle = -1; // ������ �簢���� �ε���
POINT startPoint = { 0 };   // �簢�� �׸��� ������
POINT endPoint = { 0 };     // �簢�� �׸��� ����
int isDrawing = 0;          // �簢�� �׸��� ���
int isMoving = 0;           // �簢�� �̵� ���
int offsetX = 0;            // �̵��� �� x ��ǥ ��ȭ��
int offsetY = 0;            // �̵��� �� y ��ǥ ��ȭ��
INT box = 0;                // �ӽ����� ����
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
        // ���� Ŭ������ �簢�� �׸��� ����
        isDrawing = 1;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        endPoint.x = startPoint.x;
        endPoint.y = startPoint.y;
        break;

    case WM_MOUSEMOVE:
        if (isDrawing)
        {
            // ���� Ŭ���� ���� ���¿��� ������ ��
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, NULL, TRUE); // ȭ�� ����
        }
        else if (isMoving)
        {
            // ������ Ŭ���� ���� ���¿��� ������ ��
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            // ������ �簢�� �̵�
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
                InvalidateRect(hwnd, NULL, TRUE); // ȭ�� ����
            }
        }
        break;

    case WM_LBUTTONUP:
        if (isDrawing)
        {
            // ���� Ŭ���� �� ��
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawing = 0; // �׸��� ��� ����
            // ���ο� �簢���� �迭�� �߰�
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
            InvalidateRect(hwnd, NULL, TRUE); // ȭ�� ����
        }
        break;

    case WM_RBUTTONDOWN:
    {
        // ������ Ŭ������ �簢�� ���� ��� ����
        isMoving = 1;
        selectedRectangle = -1;

        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        // � �簢���� ���õǾ����� Ȯ��
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
            // ������ Ŭ���� �� ��
            isMoving = 0; // �̵� ��� ����
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // Ŭ���̾�Ʈ ���� �ʱ�ȭ
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

        // �׷��� �簢�� �׸���
        for (int i = 0; i < numRectangles; i++)
        {
            if (i == selectedRectangle)
            {
                // ������ �簢���� �ٸ� ������ �׸���
                HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // ������ �귯��
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
                Rectangle(hdc, rectangles[i].left, rectangles[i].top, rectangles[i].right, rectangles[i].bottom);
                SelectObject(hdc, oldBrush);
                DeleteObject(brush);
            }
            else
            {
                // �������� ���� �簢�� �׸���
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