#include <Windows.h>

#define WINDOW_WIDTH 544
#define WINDOW_HEIGHT 375

RECT TITLE_BAR = {0, 0, WINDOW_WIDTH, 20};
RECT WINDOW = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
BOOL dragWindow = false;

// GUI logic
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        HBRUSH hBrush = CreateSolidBrush(RGB(32, 32, 32));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        Rectangle(hdc, TITLE_BAR.left, TITLE_BAR.top, TITLE_BAR.right, TITLE_BAR.bottom);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);

        EndPaint(hwnd, &ps);
    }
        return 0;
    case WM_LBUTTONDOWN:
        POINT pt_screen;
        GetCursorPos(&pt_screen);

        POINT pt_client;
        pt_client.x = pt_screen.x;
        pt_client.y = pt_screen.y;
        ScreenToClient(hwnd, &pt_client);

        if (PtInRect(&TITLE_BAR, pt_client))
        {
            SetCapture(hwnd);  // Capture the mouse
            dragWindow = true; // Set a flag to indicate dragging
        }
        break;
        break;
    case WM_MOUSEMOVE:
        if (dragWindow)
        {
            POINT pt_screen;
            GetCursorPos(&pt_screen);

            POINT pt_client;
            pt_client.x = pt_screen.x;
            pt_client.y = pt_screen.y;
            ScreenToClient(hwnd, &pt_client);

            RECT mainWindowRect;
            GetWindowRect(hwnd, &mainWindowRect);
            int windowWidth = mainWindowRect.right - mainWindowRect.left;
            int windowHeight = mainWindowRect.bottom - mainWindowRect.top;

            MoveWindow(hwnd, pt_screen.x - pt_client.x, pt_screen.y - pt_client.y, windowWidth, windowHeight, TRUE);
        }
        break;
    case WM_LBUTTONUP:
        ReleaseCapture();     // Release the mouse capture
        dragWindow = false; // Reset the dragging flag
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    const wchar_t szClassName[] = L"WindowsApp";
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&wincl))
        return 0;

    HWND hwnd = CreateWindowEx(
        0,
        szClassName,
        L"",
        WS_POPUP, // WS_POPUP for borderless 0 for top border with nothing on it
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL);

    ShowWindow(hwnd, nFunsterStil);

    MSG messages;
    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}