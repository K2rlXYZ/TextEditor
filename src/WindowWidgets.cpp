#include <Windows.h>
#include <Windowsx.h>
#include <uxtheme.h>
#include <strsafe.h>
#include <vsstyle.h>
#include <Vssym32.h>

#include <WindowWidgets.hpp>
#include <WindowDefinition.hpp>

Button::Button()
{
}

Button::Button(HWND parentHwnd, int idButton, int x, int y, int iWidth, int iHeight)
{
    width = iWidth;
    height = iHeight;
    rect = {x, y, x+width, y+height};

    hwnd = CreateWindow(
        L"BUTTON",
        L"",
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        rect.left,
        rect.top,
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

void Button::DrwText(LPDRAWITEMSTRUCT pDIS, LPCWSTR text, LPCWSTR font, int fontSize, COLORREF textColor)
{
    HTHEME hTheme = NULL;
    hTheme = OpenThemeData(hwnd, L"BUTTON");
    if (hTheme)
    {
        // Background
        HBRUSH hBrush = CreateSolidBrush(TERTIARY_COLOR);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(pDIS->hDC, hBrush);
        FillRect(pDIS->hDC, &pDIS->rcItem, hBrush);

        SelectObject(pDIS->hDC, hOldBrush);
        DeleteObject(hBrush);

        int y_position = fontSize;
        int closest_match = 0;
        int escapement = 0;
        int orientation = 0;
        int font_weight = FW_SEMIBOLD;
        bool italic = FALSE;
        bool ul = FALSE;
        bool xout = FALSE;

        HFONT hFont = CreateFont(y_position, closest_match, escapement, orientation, font_weight,
            italic, ul, xout, ANSI_CHARSET,
            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
            font);
        HFONT hOldFont = (HFONT) SelectObject(pDIS->hDC, hFont);
        

        DTTOPTS opts = { 0 };
        opts.dwSize = sizeof(opts);
        opts.crText = textColor;
        opts.iTextShadowType = TST_NONE;
        opts.dwFlags |= DTT_TEXTCOLOR | DTT_SHADOWTYPE;
        wchar_t* caption = const_cast<wchar_t*>(text);
        size_t cch;
        StringCchLength(caption, 2, &cch);
        DrawThemeTextEx(hTheme, pDIS->hDC, BP_PUSHBUTTON, PBS_NORMAL, 
            caption, cch, DT_CENTER | DT_VCENTER | DT_SINGLELINE, 
            &pDIS->rcItem, &opts);
        SelectObject(pDIS->hDC, hOldFont); // <-- add this
        DeleteObject(hFont);
        DeleteObject(hOldFont);
        CloseThemeData(hTheme);
    }
}

ExitButton::ExitButton(){

}

ExitButton::ExitButton(HWND parentHwnd) : Button(
    parentHwnd,
    ID_EXIT_BUTTON, 
    titleBarRect.right - wcbs(titleBarRect.bottom)*2 - wcbo(titleBarRect.bottom, wcbs(titleBarRect.bottom))*2, 
    titleBarRect.top + wcbo(titleBarRect.bottom, wcbs(titleBarRect.bottom)), 
    wcbs(titleBarRect.bottom), 
    wcbs(titleBarRect.bottom))
{
}

void ExitButton::Drw(LPDRAWITEMSTRUCT pDIS)
{
    Button::DrwText(pDIS, L"X", L"Helvetica", 16, RGB(212, 212, 212));
}

MaximizeButton::MaximizeButton(){

}

MaximizeButton::MaximizeButton(HWND parentHwnd) : Button(
    parentHwnd, 
    ID_MAXIMIZE_BUTTON, 
    titleBarRect.right - wcbs(titleBarRect.bottom)*2 - wcbo(titleBarRect.bottom, wcbs(titleBarRect.bottom))*2, 
    titleBarRect.top + wcbo(titleBarRect.bottom, wcbs(titleBarRect.bottom)),
    wcbs(titleBarRect.bottom), 
    wcbs(titleBarRect.bottom))
{
}

void MaximizeButton::Drw(LPDRAWITEMSTRUCT pDIS)
{
    Button::DrwText(pDIS, L"\u2610", L"Helvetica", 16, RGB(212, 212, 212));
}

MinimizeButton::MinimizeButton(){

}

MinimizeButton::MinimizeButton(HWND parentHwnd) : Button(
    parentHwnd, 
    ID_MINIMIZE_BUTTON, 
    titleBarRect.right - wcbs(titleBarRect.bottom)*3 - wcbo(titleBarRect.bottom, wcbs(titleBarRect.bottom))*3, 
    titleBarRect.top + wcbo(titleBarRect.bottom, wcbs(titleBarRect.bottom)),
    wcbs(titleBarRect.bottom), 
    wcbs(titleBarRect.bottom))
{
}

void MinimizeButton::Drw(LPDRAWITEMSTRUCT pDIS)
{
    Button::DrwText(pDIS, L"-", L"Helvetica", 16, RGB(212, 212, 212));
}

TextBox::TextBox()
{
}

TextBox::TextBox(HWND parentHwnd)
{
    rect = {contentArea.left, contentArea.top, contentArea.left, contentArea.top};

    hwnd = CreateWindow(
        L"EDIT",
        NULL,
        WS_VISIBLE | WS_CHILD | WS_VSCROLL | 
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
        rect.left,
        rect.top,
        rect.right-rect.left,
        rect.bottom-rect.top,
        parentHwnd,
        (HMENU)ID_TEXT_BOX,
        (HINSTANCE)GetWindowLongPtr(parentHwnd, GWLP_HINSTANCE),
        NULL);

    int fontSize = 16;
    LPCWSTR font = L"Helvetica";

    int y_position = fontSize;
    int closest_match = 0;
    int escapement = 0;
    int orientation = 0;
    int font_weight = FW_SEMIBOLD;
    bool italic = FALSE;
    bool ul = FALSE;
    bool xout = FALSE;

    HFONT hFont = CreateFont(y_position, closest_match, escapement, orientation, font_weight,
        italic, ul, xout, ANSI_CHARSET,
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
        font);
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    DeleteObject(hFont);
}

void TextBox::Resize(int width, int height)
{
    MoveWindow(hwnd, rect.left, rect.top, width, height, TRUE);
}

void TextBox::DrwText(LPDRAWITEMSTRUCT pDIS, LPCWSTR text, LPCWSTR font, int fontSize, COLORREF textColor)
{
    HTHEME hTheme = NULL;
    hTheme = OpenThemeData(hwnd, L"EDIT");
    if (hTheme)
    {
        // Background
        HBRUSH hBrush = CreateSolidBrush(TERTIARY_COLOR);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(pDIS->hDC, hBrush);
        FillRect(pDIS->hDC, &pDIS->rcItem, hBrush);

        SelectObject(pDIS->hDC, hOldBrush);
        DeleteObject(hBrush);

        int y_position = fontSize;
        int closest_match = 0;
        int escapement = 0;
        int orientation = 0;
        int font_weight = FW_SEMIBOLD;
        bool italic = FALSE;
        bool ul = FALSE;
        bool xout = FALSE;

        HFONT hFont = CreateFont(y_position, closest_match, escapement, orientation, font_weight,
            italic, ul, xout, ANSI_CHARSET,
            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
            font);
        HFONT hOldFont = (HFONT) SelectObject(pDIS->hDC, hFont);
        

        DTTOPTS opts = { 0 };
        opts.dwSize = sizeof(opts);
        opts.crText = textColor;
        opts.iTextShadowType = TST_NONE;
        opts.dwFlags |= DTT_TEXTCOLOR | DTT_SHADOWTYPE;
        wchar_t* caption = const_cast<wchar_t*>(text);
        size_t cch;
        StringCchLength(caption, 2, &cch);
        DrawThemeTextEx(hTheme, pDIS->hDC, BP_PUSHBUTTON, PBS_NORMAL, 
            caption, cch, DT_CENTER | DT_VCENTER | DT_SINGLELINE, 
            &pDIS->rcItem, &opts);
        SelectObject(pDIS->hDC, hOldFont); // <-- add this
        DeleteObject(hFont);
        DeleteObject(hOldFont);
        CloseThemeData(hTheme);
    }
}

LPWSTR TextBox::getText()
{
    int length = GetWindowTextLength(hwnd);
    LPWSTR pszMem = (LPWSTR) VirtualAlloc((LPVOID) NULL, 
    (DWORD) (length + 1), MEM_COMMIT, 
    PAGE_READWRITE);
    GetWindowText(hwnd, pszMem, length);
    OutputDebugString(pszMem);
    return pszMem;
}