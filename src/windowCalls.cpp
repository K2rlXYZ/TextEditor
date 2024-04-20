#include <Windows.h>

#include <WindowWidgets.h>
#include <WindowDefinition.h>
#include <WindowCalls.h>

ExitButton exitButton;

// GUI logic
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        PaintWindow(hwnd);
        break;

    case WM_CREATE:
    {
        exitButton = ExitButton(hwnd);
    }
    break;

    // Sent after the window's size is changed
    case WM_SIZE:
        SetSizesAndPositions(hwnd, lParam);
        break;

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
    const wchar_t szClassName[] = L"WindowsApp";
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
