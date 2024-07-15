
#include <Windows.h>

#include <WindowWidgets.hpp>
#include <WindowDefinition.hpp>
#include <main.hpp>

// GUI logic
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {

    }
    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
        if (pDIS->hwndItem == exitButton.hwnd)
        {
            exitButton.Drw(pDIS);
        }
        if (pDIS->hwndItem == maximizeButton.hwnd)
        {
            maximizeButton.Drw(pDIS);
        }
        if (pDIS->hwndItem == minimizeButton.hwnd)
        {
            minimizeButton.Drw(pDIS);
        }
        return TRUE;
    }
    case WM_PAINT:
        PaintWindow(hwnd);
        break;

    case WM_CREATE:
    {
        wcbSize = wcbs(titleBarRect.bottom);
        wcbOffset = wcbo(titleBarRect.bottom, wcbSize);
        exitButton = ExitButton(hwnd);
        maximizeButton = MaximizeButton(hwnd);
        minimizeButton = MinimizeButton(hwnd);
        textBox = TextBox(hwnd);
    }
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_EXIT_BUTTON && HIWORD(wParam) == BN_CLICKED)
        {
            exit(0);
        }
        if (LOWORD(wParam) == ID_MAXIMIZE_BUTTON && HIWORD(wParam) == BN_CLICKED)
        {
            if (maximized)
            {
                ShowWindow(hwnd, SW_NORMAL);
                maximized = false;
            }
            else
            {
                ShowWindow(hwnd, SW_MAXIMIZE);
                maximized = true;
            }
        }
        if (LOWORD(wParam) == ID_MINIMIZE_BUTTON && HIWORD(wParam) == BN_CLICKED)
        {
            ShowWindow(hwnd, SW_MINIMIZE);
        }
        break;

    // Sent after the window's size is changed
    case WM_SIZE:
    {
        SetSizesAndPositions(hwnd, lParam);
        maximized = false;
        wcbSize = wcbs(titleBarRect.bottom);
        wcbOffset = wcbo(titleBarRect.bottom, wcbSize);
        exitButton.MoveButton(titleBarRect.right - wcbSize - wcbOffset, titleBarRect.top + wcbOffset);
        maximizeButton.MoveButton(titleBarRect.right - wcbSize * 2 - wcbOffset * 2, titleBarRect.top + wcbOffset);
        minimizeButton.MoveButton(titleBarRect.right - wcbSize * 3 - wcbOffset * 3, titleBarRect.top + wcbOffset);
        textBox.Resize(contentArea.right-contentArea.left, contentArea.bottom-contentArea.top);
        break;
    }

    // Sent to a window when the size or position of the window is about to change.
    case WM_GETMINMAXINFO:
        MinMaxWindowSize(lParam);
        return 0;

    // Sent to a window in order to determine what part of the window corresponds to a particular screen coordinate.
    case WM_NCHITTEST:
        return HitTest(hwnd, lParam);

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    LPCWSTR szClassName = L"WindowsApp";
    WNDCLASSEX windowClass;

    windowClass.hInstance = hThisInstance;
    windowClass.lpszClassName = szClassName;
    windowClass.lpfnWndProc = WindowProcedure;
    windowClass.style = CS_DBLCLKS;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszMenuName = NULL;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&windowClass))
        return 0;

    HWND hwnd = CreateWindowEx(
        0,
        szClassName,
        L"",
        WS_POPUP | WS_VISIBLE, // WS_POPUP for borderless 0 for top border with nothing on it
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right,
        windowRect.bottom,
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
