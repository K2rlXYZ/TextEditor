#include <tuple>
#include <Windows.h>
#include <Windowsx.h>

#define WINDOW_WIDTH 544
#define WINDOW_HEIGHT 375
#define PRIMARY_COLOR RGB(48, 48, 48)
#define SECONDARY_COLOR RGB(32, 32, 32)

RECT WINDOW = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
RECT TITLE_BAR = {0, 0, WINDOW.right, 20};
RECT LEFT_RESIZE = {0, TITLE_BAR.bottom, 5, WINDOW.bottom - 5};
RECT RIGHT_RESIZE = {WINDOW.right - 5, TITLE_BAR.bottom, WINDOW.right, WINDOW.bottom - 5};
RECT BOTTOM_RESIZE = {5, WINDOW.bottom - 5, WINDOW.right - 5, WINDOW.bottom};
RECT BOTTOM_RIGHT_RESIZE = {WINDOW.right - 5, WINDOW.bottom - 5, WINDOW.right, WINDOW.bottom};
RECT BOTTOM_LEFT_RESIZE = {0, WINDOW.bottom - 5, 5, WINDOW.bottom};

void setSizes(int wWidth, int wHeight)
{
    WINDOW = {0, 0, wWidth, wHeight};
    TITLE_BAR = {0, 0, WINDOW.right, 20};
    LEFT_RESIZE = {0, TITLE_BAR.bottom, 5, WINDOW.bottom - 5};
    RIGHT_RESIZE = {WINDOW.right - 5, TITLE_BAR.bottom, WINDOW.right, WINDOW.bottom - 5};
    BOTTOM_RESIZE = {5, WINDOW.bottom - 5, WINDOW.right - 5, WINDOW.bottom};
    BOTTOM_RIGHT_RESIZE = {WINDOW.right - 5, WINDOW.bottom - 5, WINDOW.right, WINDOW.bottom};
    BOTTOM_LEFT_RESIZE = {0, WINDOW.bottom - 5, 5, WINDOW.bottom};
}

std::tuple<RECT *, LRESULT> RECTS[] = {
    {&TITLE_BAR, HTCAPTION},
    {&LEFT_RESIZE, HTLEFT},
    {&RIGHT_RESIZE, HTRIGHT},
    {&BOTTOM_RESIZE, HTBOTTOM},
    {&BOTTOM_RIGHT_RESIZE, HTBOTTOMRIGHT},
    {&BOTTOM_LEFT_RESIZE, HTBOTTOMLEFT}};

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
        POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
        ScreenToClient(hwnd, &pt);
        for (auto elem : RECTS)
        {
            if (PtInRect(std::get<0>(elem), pt))
            {
                return std::get<1>(elem);
            }
        }
        break;
    }
    case WM_SIZE:
    {
        int nWidth = GET_X_LPARAM(lParam);
        int nHeight = GET_Y_LPARAM(lParam);
        setSizes(nWidth, nHeight);
        InvalidateRect(hwnd, &WINDOW, 1);
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