#include <Windows.h>
#include <Windowsx.h>
#include <tuple>

#define PRIMARY_COLOR RGB(48, 48, 48)
#define SECONDARY_COLOR RGB(32, 32, 32)

extern RECT windowRect = {0, 0, 544, 375};
extern RECT titleBarRect = {0, 0, windowRect.right, 20};
RECT leftResizeRect = {0, titleBarRect.bottom, 5, windowRect.bottom - 5};
RECT rightResizeRect = {windowRect.right - 5, titleBarRect.bottom, windowRect.right, windowRect.bottom - 5};
RECT bottomResizeRect = {5, windowRect.bottom - 5, windowRect.right - 5, windowRect.bottom};
RECT bottomRightResizeRect = {windowRect.right - 5, windowRect.bottom - 5, windowRect.right, windowRect.bottom};
RECT bottomLeftResizeRect = {0, windowRect.bottom - 5, 5, windowRect.bottom};

void SetSizesAndPositions(HWND hwnd, LPARAM lParam)
{
    int wWidth = GET_X_LPARAM(lParam);
    int wHeight = GET_Y_LPARAM(lParam);
    windowRect = {0, 0, wWidth, wHeight};
    titleBarRect = {0, 0, windowRect.right, 20};
    leftResizeRect = {0, titleBarRect.bottom, 5, windowRect.bottom - 5};
    rightResizeRect = {windowRect.right - 5, titleBarRect.bottom, windowRect.right, windowRect.bottom - 5};
    bottomResizeRect = {5, windowRect.bottom - 5, windowRect.right - 5, windowRect.bottom};
    bottomRightResizeRect = {windowRect.right - 5, windowRect.bottom - 5, windowRect.right, windowRect.bottom};
    bottomLeftResizeRect = {0, windowRect.bottom - 5, 5, windowRect.bottom};
    InvalidateRect(hwnd, &windowRect, true);
}

const std::tuple<RECT *, LRESULT> RESIZE_RECTS[] = {
    {&titleBarRect, HTCAPTION},
    {&leftResizeRect, HTLEFT},
    {&rightResizeRect, HTRIGHT},
    {&bottomResizeRect, HTBOTTOM},
    {&bottomRightResizeRect, HTBOTTOMRIGHT},
    {&bottomLeftResizeRect, HTBOTTOMLEFT}
};

// Used for case WM_PAINT to paint the window
void PaintWindow(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    HBRUSH hBrush = CreateSolidBrush(PRIMARY_COLOR);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    // Background
    FillRect(hdc, &windowRect, hBrush);
    // TitleBar
    hBrush = CreateSolidBrush(SECONDARY_COLOR);
    FillRect(hdc, &titleBarRect, hBrush);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);

    EndPaint(hwnd, &ps);
}

LRESULT HitTest(HWND hwnd, LPARAM lParam)
{
    POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
    ScreenToClient(hwnd, &pt);
    for (auto elem : RESIZE_RECTS)
    {
        if (PtInRect(std::get<0>(elem), pt))
        {
            return std::get<1>(elem);
        }
    }
    return HTCLIENT;
}

void MinMaxWindowSize(LPARAM lParam)
{
    MINMAXINFO *minMaxInfo = (MINMAXINFO *)lParam;
    minMaxInfo->ptMinTrackSize.x = 544; // Minimum window width
    minMaxInfo->ptMinTrackSize.y = 375; // Minimum window height
}