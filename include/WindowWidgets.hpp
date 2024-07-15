#ifndef _WINDOW_WIDGETS_
#define _WINDOW_WIDGETS_
#include <Windows.h>
#include <Windowsx.h>

#define ID_EXIT_BUTTON 2001
#define ID_MAXIMIZE_BUTTON 2002
#define ID_MINIMIZE_BUTTON 2003

#define ID_TEXT_BOX 2101

#define wcbs(tbrb) tbrb-2 // (int)tbrb/1.5
#define wcbo(tbrb, wcbs) 1 // (tbrb - wcbs) / 2;

class Button
{
public:
    HWND hwnd;
    RECT rect;
    int width;
    int height;

    Button();

    Button(HWND parentHwnd, int idButton, int x, int y, int iWidth, int iHeight);

    void MoveButton(int x, int y);
    void DrwText(LPDRAWITEMSTRUCT pDIS, LPCWSTR text, LPCWSTR font, int fontSize, COLORREF textColor);
};

class ExitButton : public Button
{
public:
    ExitButton();

    ExitButton(HWND parentHwnd);

    void Drw(LPDRAWITEMSTRUCT pDIS);
};

class MaximizeButton : public Button
{
public:
    MaximizeButton();

    MaximizeButton(HWND parentHwnd);

    void Drw(LPDRAWITEMSTRUCT pDIS);
};

class MinimizeButton : public Button
{
public:
    MinimizeButton();

    MinimizeButton(HWND parentHwnd);

    void Drw(LPDRAWITEMSTRUCT pDIS);
};

class TextBox
{
public:
    HWND hwnd;
    RECT rect;

    TextBox();

    TextBox(HWND parentHwnd);

    LPWSTR getText();
    void Resize(int width, int height);
    void DrwText(LPDRAWITEMSTRUCT pDIS, LPCWSTR text, LPCWSTR font, int fontSize, COLORREF textColor);
};
#endif /* _WINDOW_WIDGETS_ */