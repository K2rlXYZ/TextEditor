#include <Windows.h>
#include <Windowsx.h>
#include <tuple>

#include <WindowDefinition.hpp>

RECT windowRect = {0, 0, 544, 375};
RECT titleBarRect = {0, 0, windowRect.right, 20};
RECT leftResizeRect = {0, titleBarRect.bottom, RESIZE_BOX_SIZE, windowRect.bottom - RESIZE_BOX_SIZE};
RECT rightResizeRect = {windowRect.right - RESIZE_BOX_SIZE, titleBarRect.bottom, windowRect.right, windowRect.bottom - RESIZE_BOX_SIZE};
RECT bottomResizeRect = {RESIZE_BOX_SIZE, windowRect.bottom - RESIZE_BOX_SIZE, windowRect.right - RESIZE_BOX_SIZE, windowRect.bottom};
RECT bottomRightResizeRect = {windowRect.right - RESIZE_BOX_SIZE, windowRect.bottom - RESIZE_BOX_SIZE, windowRect.right, windowRect.bottom};
RECT bottomLeftResizeRect = {0, windowRect.bottom - RESIZE_BOX_SIZE, RESIZE_BOX_SIZE, windowRect.bottom};
RECT contentArea = {RESIZE_BOX_SIZE, titleBarRect.bottom + RESIZE_BOX_SIZE, rightResizeRect.left, bottomResizeRect.top};

void SetSizesAndPositions(HWND hwnd, LPARAM lParam)
{
    int wWidth = GET_X_LPARAM(lParam);
    int wHeight = GET_Y_LPARAM(lParam);
    windowRect = {0, 0, wWidth, wHeight};
    titleBarRect = {0, 0, windowRect.right, titleBarRect.bottom};
    leftResizeRect = {0, titleBarRect.bottom, RESIZE_BOX_SIZE, windowRect.bottom - RESIZE_BOX_SIZE};
    rightResizeRect = {windowRect.right - RESIZE_BOX_SIZE, titleBarRect.bottom, windowRect.right, windowRect.bottom - RESIZE_BOX_SIZE};
    bottomResizeRect = {RESIZE_BOX_SIZE, windowRect.bottom - RESIZE_BOX_SIZE, windowRect.right - RESIZE_BOX_SIZE, windowRect.bottom};
    bottomRightResizeRect = {windowRect.right - RESIZE_BOX_SIZE, windowRect.bottom - RESIZE_BOX_SIZE, windowRect.right, windowRect.bottom};
    bottomLeftResizeRect = {0, windowRect.bottom - RESIZE_BOX_SIZE, RESIZE_BOX_SIZE, windowRect.bottom};
    contentArea = {RESIZE_BOX_SIZE, titleBarRect.bottom + RESIZE_BOX_SIZE, rightResizeRect.left, bottomResizeRect.top};
    InvalidateRect(hwnd, &windowRect, true);
}

// Used for case WM_PAINT to paint the window
void PaintWindow(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    HBRUSH hBrush = CreateSolidBrush(PRIMARY_COLOR);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    // Background
    FillRect(hdc, &windowRect, hBrush);
    // Title Bar
    hBrush = CreateSolidBrush(SECONDARY_COLOR);
    FillRect(hdc, &titleBarRect, hBrush);
    // Content Area
    hBrush = CreateSolidBrush(TERTIARY_COLOR);
    FillRect(hdc, &contentArea, hBrush);

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