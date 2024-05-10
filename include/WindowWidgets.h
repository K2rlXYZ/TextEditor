#include <Windows.h>
#include <Windowsx.h>

#define ID_EXIT_BUTTON 2001
#define ID_MAXIMIZE_BUTTON 2002
#define ID_MINIMIZE_BUTTON 2003

class Button
{
public:
    HWND hwnd;
    int width;
    int height;

    Button();

    Button(HWND parentHwnd, wchar_t text[], int idButton, int x, int y, int iWidth, int iHeight);

    void MoveButton(int x, int y);
};

class ExitButton : Button
{
public:
    ExitButton();

    ExitButton(HWND parentHwnd);
};

class MaximizeButton : Button
{
public:
    MaximizeButton();

    MaximizeButton(HWND parentHwnd);
};

class MinimizeButton : Button
{
public:
    MinimizeButton();

    MinimizeButton(HWND parentHwnd);
};