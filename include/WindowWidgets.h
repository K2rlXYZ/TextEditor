#include <Windows.h>
#include <Windowsx.h>

class Button
{
public:
    HWND hwnd;
    int width;
    int height;

    Button();

    Button(HWND parentHwnd, wchar_t text[], int x, int y, int iWidth, int iHeight);

    void MoveButton(int x, int y);
};

class ExitButton : Button
{
public:
    ExitButton();

    ExitButton(HWND parentHwnd);
};