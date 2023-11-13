#include <windows.h>
#include <math.h>
void ryan(HDC hdc, int x, int y, int z, int v) {
    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    HBRUSH skin = CreateSolidBrush(RGB(255, 200, 15));
    HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, skin); //x = 250, y = 150, z = 550, v = 480
    Ellipse(hdc, x, y, x+(z-x)/3, y+(v-y)/10*3);//��1
    Ellipse(hdc, z-(z-x)/3, y, z, y+(v - y)/10 * 3);//��2
    Ellipse(hdc, x, y+(v-y)/10, z, v);//�Ǻ�
    SelectObject(hdc, white);
    Ellipse(hdc, x + (z - x) / 3, y + (v - y) / 10 * 6, x + (z - x) / 2, y + (v - y) / 10 * 7);//�Ͼ��
    Ellipse(hdc, x + (z - x) / 2, y + (v - y) / 10 * 6, x + (z - x) / 3*2, y + (v - y) / 10 * 7);//�Ͼ��
    SelectObject(hdc, hPen);
    MoveToEx(hdc, x + (z - x) / 6 * 1, y + (v - y) / 10 * 4, NULL); LineTo(hdc, x + (z - x) / 6 * 2, y + (v - y) / 10 * 4); //�޼���2
    MoveToEx(hdc, x + (z - x) / 6 * 4, y + (v - y) / 10 * 4, NULL); LineTo(hdc, x + (z - x) / 6 * 5, y + (v - y) / 10 * 4); //��������2
    SelectObject(hdc, black);
    Ellipse(hdc, x+(z-x)/12*3, y + (v - y) / 12 * 6, x + (z - x) / 12 * 4, y + (v - y) / 12 * 7);//��1
    Ellipse(hdc, z - (z - x) / 12 * 4, y + (v - y) / 12 * 6, z- (z - x) / 12 * 3, y + (v - y) / 12 * 7);//��2
    DeleteObject(black);
}
//void ryan(HDC hdc, int x, int y, int z, int v) {
//    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
//    HBRUSH skin = CreateSolidBrush(RGB(255, 200, 15));
//    HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
//    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
//    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
//    SelectObject(hdc, skin); //x = 230, y = 150, z = 330, v = 250
//    Ellipse(hdc, 250, 150, 350, 250);//��1
//    Ellipse(hdc, 450, 150, 550, 250);//��2
//    Ellipse(hdc, 250, 180, 550, 480);//�Ǻ�
//    SelectObject(hdc, white);
//    Ellipse(hdc, 340, 330, 400, 380);//�Ͼ��
//    Ellipse(hdc, 400, 330, 460, 380);//�Ͼ��
//    SelectObject(hdc, hPen);
//    MoveToEx(hdc, 310, 270, NULL); LineTo(hdc, 350, 270); //�޼���2
//    MoveToEx(hdc, 490, 270, NULL); LineTo(hdc, 450, 270); //��������2
//    SelectObject(hdc, black);
//    Ellipse(hdc, 320, 300, 340, 320);//��1
//    Ellipse(hdc, 460, 300, 480, 320);//��2
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
POINT startPoint = { 0 };   // �׸��� ������
POINT endPoint = { 0 };     // �׸��� ����
int isDrawing = 0;          // �׸��� ���
int isMoving = 0;
int modecheck = 3; //���üũ�ϱ�
int radius = 1;
int Brush = 0;
int offsetX = 0;            // �̵��� �� x ��ǥ ��ȭ��
int offsetY = 0;            // �̵��� �� y ��ǥ ��ȭ��
int isResizing = 0;     // ũ�� ���� ��� ���θ� ��Ÿ���� ����
POINT resizeStartPoint; // ũ�� ���� �������� �����ϴ� ����
int originalRadius;     // ���� ���� �������� �����ϴ� ����
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
                HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
                HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
                HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
                HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
                SelectObject(hdc, skin);
                Ellipse(hdc, 250, 180, 550, 480);//�Ǻ�
                SelectObject(hdc, mouth);
                Ellipse(hdc, 380, 350, 420, 430);//��
                SelectObject(hdc, white);
                Ellipse(hdc, 340, 330, 400, 380);//�Ͼ��
                MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //�޼���1
                MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //�޼���2
                Ellipse(hdc, 400, 330, 460, 380);//�Ͼ��
                MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //��������1
                MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //��������2
                SelectObject(hdc, black);
                Ellipse(hdc, 380, 310, 420, 350);//��
                MoveToEx(hdc, 280, 330, NULL); LineTo(hdc, 300, 320); //�޴�1
                MoveToEx(hdc, 280, 310, NULL); LineTo(hdc, 300, 320); //�޴�2
                MoveToEx(hdc, 520, 330, NULL); LineTo(hdc, 500, 320); //������1
                MoveToEx(hdc, 520, 310, NULL); LineTo(hdc, 500, 320); //������2
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
            Ellipse(hdc, 250, 180, 550, 480);//�Ǻ�
            SelectObject(hdc, mouth);
            Ellipse(hdc, 380, 350, 420, 430);//��
            SelectObject(hdc, white);
            Ellipse(hdc, 340, 330, 400, 380);//�Ͼ��
            MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //�޼���1
            MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //�޼���2
            Ellipse(hdc, 400, 330, 460, 380);//�Ͼ��
            MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //��������1
            MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //��������2
            SelectObject(hdc, black);
            Ellipse(hdc, 380, 310, 420, 350);//��
            Ellipse(hdc, 290, 310, 300, 330);//��1
            SelectObject(hdc, white);
            Ellipse(hdc, 292, 315, 297, 325);//������1
            SelectObject(hdc, black);
            Ellipse(hdc, 500, 310, 510, 330);//��2
            SelectObject(hdc, white);
            Ellipse(hdc, 502, 315, 507, 325);//������2
            DeleteObject(white);
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
            case 3:
                modecheck = 2;
                SetFocus(hwnd);
                break;
            case 4:
                modecheck = 3; // ��
                SetFocus(hwnd);
                break;
            case 5:
                modecheck = 4; // ����
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
        int boxWidth = 800 - 2 * margin - 2 * padding; // ����� ���� ������ �ڽ��� �ʺ�
        int boxHeight = 480 - 2 * margin - 2 * padding; // ����� ���� ������ �ڽ��� ����
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));
        // Ŭ���̾�Ʈ ���� �ʱ�ȭ
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

            // ���� ������ ���
            int radius = abs(centerX - startPoint.x);

            // �� �׸���
            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
        }
        else if (modecheck == 2) {
            HBRUSH skin = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH mouth = CreateSolidBrush(RGB(255, 150, 255));
            HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
            HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, skin);
            Ellipse(hdc, 250, 180, 550, 480);//�Ǻ�
            SelectObject(hdc, mouth);
            Ellipse(hdc, 380, 350, 420, 430);//��
            SelectObject(hdc, white);
            Ellipse(hdc, 340, 330, 400, 380);//�Ͼ��
            MoveToEx(hdc, 320, 340, NULL); LineTo(hdc, 360, 350); //�޼���1
            MoveToEx(hdc, 320, 370, NULL); LineTo(hdc, 360, 360); //�޼���2
            Ellipse(hdc, 400, 330, 460, 380);//�Ͼ��
            MoveToEx(hdc, 480, 340, NULL); LineTo(hdc, 440, 350); //��������1
            MoveToEx(hdc, 480, 370, NULL); LineTo(hdc, 440, 360); //��������2
            SelectObject(hdc, black);
            Ellipse(hdc, 380, 310, 420, 350);//��
            Ellipse(hdc, 290, 310, 300, 330);//��1
            SelectObject(hdc, white);
            Ellipse(hdc, 292, 315, 297, 325);//������1
            SelectObject(hdc, black);
            Ellipse(hdc, 500, 310, 510, 330);//��2
            SelectObject(hdc, white);
            Ellipse(hdc, 502, 315, 507, 325);//������2
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
    HWND hwnd = CreateWindow(L"������", L"������", WS_OVERLAPPED | WS_SYSMENU, 100, 0, 815, 600, NULL, NULL, hInstance, NULL);
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