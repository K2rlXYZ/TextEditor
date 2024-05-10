#include <Windows.h>
#include <Windowsx.h>
#include <WindowWidgets.h>
#include <WindowDefinition.h>

int WINDOW_CONTROL_BUTTON_SIZE = (int)titleBarRect.bottom / 1.5;
int OFFSET = (titleBarRect.bottom - WINDOW_CONTROL_BUTTON_SIZE)/2; 

Button::Button()
{
}

Button::Button(HWND parentHwnd, wchar_t text[], int idButton, int x, int y, int iWidth, int iHeight)
{
    width = iWidth;
    height = iHeight;
    hwnd = CreateWindow(
        L"BUTTON",
        text,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        x,
        y,
        width,
        height,
        parentHwnd,
        (HMENU)idButton,
        (HINSTANCE)GetWindowLongPtr(parentHwnd, GWLP_HINSTANCE),
        NULL);
}

void Button::MoveButton(int x, int y)
{
    MoveWindow(hwnd, x, y, width, height, TRUE);
}

ExitButton::ExitButton(HWND parentHwnd) : Button(
    parentHwnd, 
    L"X",
    ID_EXIT_BUTTON, 
    titleBarRect.right - WINDOW_CONTROL_BUTTON_SIZE - OFFSET, 
    titleBarRect.top + OFFSET, 
    WINDOW_CONTROL_BUTTON_SIZE, 
    WINDOW_CONTROL_BUTTON_SIZE)
{
}

MaximizeButton::MaximizeButton(HWND parentHwnd) : Button(
    parentHwnd, 
    L"🗖",
    ID_MAXIMIZE_BUTTON, 
    titleBarRect.right - WINDOW_CONTROL_BUTTON_SIZE*2 - OFFSET*2, 
    titleBarRect.top + OFFSET, 
    WINDOW_CONTROL_BUTTON_SIZE, 
    WINDOW_CONTROL_BUTTON_SIZE)
{
}

MinimizeButton::MinimizeButton(HWND parentHwnd) : Button(
    parentHwnd, 
    L"-",
    ID_MINIMIZE_BUTTON, 
    titleBarRect.right - WINDOW_CONTROL_BUTTON_SIZE*3 - OFFSET*3, 
    titleBarRect.top + OFFSET, 
    WINDOW_CONTROL_BUTTON_SIZE, 
    WINDOW_CONTROL_BUTTON_SIZE)
{
}