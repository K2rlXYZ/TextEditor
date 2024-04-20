#include <Windows.h>
#include <Windowsx.h>
#include <WindowWidgets.h>
#include <WindowDefinition.h>

int WINDOW_CONTROL_BUTTON_SIZE = (int)titleBarRect.bottom / 1.5;

Button::Button()
{
}

Button::Button(HWND parentHwnd, wchar_t text[], int x, int y, int iWidth, int iHeight)
{
    width = iWidth;
    height = iHeight;
    hwnd = CreateWindow(
        L"BUTTON",
        text,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x,
        y,
        width,
        height,
        parentHwnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(parentHwnd, GWLP_HINSTANCE),
        NULL);
}

void Button::MoveButton(int x, int y)
{
    MoveWindow(hwnd, x, y, width, height, TRUE);
}

ExitButton::ExitButton()
{
}

ExitButton::ExitButton(HWND parentHwnd) : Button(parentHwnd, L"X", titleBarRect.right - WINDOW_CONTROL_BUTTON_SIZE, titleBarRect.top, WINDOW_CONTROL_BUTTON_SIZE, WINDOW_CONTROL_BUTTON_SIZE)
{
}