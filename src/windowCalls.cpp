#include <Windows.h>
#include <Windowsx.h>

#define WINDOW_WIDTH 544
#define WINDOW_HEIGHT 375
#define PRIMARY_COLOR RGB(48, 48, 48)
#define SECONDARY_COLOR RGB(32, 32, 32)

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

        HBRUSH hBrush = CreateSolidBrush(PRIMARY_COLOR);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        // Background
        FillRect(hdc, &WINDOW, hBrush);
        // TitleBar
        hBrush = CreateSolidBrush(SECONDARY_COLOR);
        FillRect(hdc, &TITLE_BAR, hBrush);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_NCHITTEST:
    {
        LPARAM lp = lParam;
        POINT pt = {GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
        ScreenToClient(hwnd, &pt);

        if (PtInRect(&TITLE_BAR, pt))
        {
            return HTCAPTION;
        }
        break;
    }
    case WM_SIZE:
    {
        
    }
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