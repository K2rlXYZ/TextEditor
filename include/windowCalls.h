#include <windows.h>

WNDCLASSEX CreateDefaultWNDCLASSEX(HINSTANCE hInstance);

HWND WINAPI CreateDefaultWindowEx(HINSTANCE hInstance);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);