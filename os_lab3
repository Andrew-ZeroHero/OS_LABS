#include <windows.h>

void MyDraw(HWND h) {
	HDC dc = GetDC(h);
	HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH yellow = CreateSolidBrush(RGB(255, 237, 0));
	HBRUSH testbrown = CreateSolidBrush(RGB(198, 171, 120));
	HBRUSH bluesky= CreateSolidBrush(RGB(152, 221, 229));
    HBRUSH white = CreateSolidBrush(RGB(253, 255, 255));
	//95 pix=2sm
	HBRUSH sun = CreateSolidBrush(RGB(241, 237, 135));
	HBRUSH grass = CreateSolidBrush(RGB(30, 198, 14));
	//backgroung
	//sky, grass, sun
	SelectObject(dc, bluesky);
	Rectangle(dc, 0, 0, 800, 600);//sky
    SelectObject(dc, sun);
    Ellipse(dc, 100, 50, 200, 150);//sun
    SelectObject(dc, grass);
    Rectangle(dc, 0, 450, 800, 650);
    MoveToEx(dc, 350, 100, NULL );
    LineTo(dc, 350, 0);
    SelectObject(dc, testbrown);//hive
    Ellipse(dc, 500, 400, 200, 100);
   // LineTo(dc, 350, 0);
    SelectObject(dc, black);
    Ellipse(dc, 490, 290, 390, 190);
    LineTo(dc, 350, 100);
    SelectObject(dc, yellow);//bee
    Ellipse(dc, 450, 450, 350, 350);
    SelectObject(dc, black);
    Ellipse(dc, 440, 440, 340, 340);
    SelectObject(dc, yellow);
    Ellipse(dc, 430, 430, 330, 330);
    SelectObject(dc, white);
    Ellipse(dc, 488, 380, 410, 342);
    Ellipse(dc, 460, 370, 395, 290);
    
}

LONG WINAPI WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    HDC hdc;
    HDC memDC;
    HBITMAP memBM;
    PAINTSTRUCT ps;
    HANDLE hOld;
    switch (message)
    {
    case WM_PAINT: // With double buffering
        hdc = BeginPaint(hwnd, &ps);
        memDC = CreateCompatibleDC(hdc);
        memBM = CreateCompatibleBitmap(hdc, 800, 600);
        hOld = SelectObject(memDC, memBM);
        MyDraw((HWND)memDC);
        BitBlt(hdc, 0, 0, 800, 600, memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, hOld);
        DeleteObject(memBM);
        DeleteDC(memDC);
        MyDraw(hwnd);
        EndPaint(hwnd, &ps);
        break;
    case WM_ERASEBKGND:
        return 1;
    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE) PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
        if ((LOWORD(lparam) < 20) && (LOWORD(lparam) < 20)) PostQuitMessage(0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hwnd, message, wparam, lparam);
    }
    return 0;
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    MSG message;
    WNDCLASS main_window;
    memset(&main_window, 0, sizeof(WNDCLASS));

    main_window.style = CS_HREDRAW | CS_VREDRAW;
    main_window.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    main_window.hInstance = hInstance;
    main_window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    main_window.lpszClassName = L"main window";
    RegisterClass(&main_window);

    HWND main_hwnd = CreateWindow(L"main window", L"Hive and bees",
        WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(main_hwnd, nCmdShow);
    UpdateWindow(main_hwnd);
    MyDraw(main_hwnd);
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return message.wParam;
}
