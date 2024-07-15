#ifndef _MAIN_
#define _MAIN_
#include <windows.h>

#include <WindowWidgets.hpp>
#include <WindowDefinition.hpp>

ExitButton exitButton;
MaximizeButton maximizeButton;
MinimizeButton minimizeButton;
TextBox textBox;
bool maximized = false;
int wcbSize;
int wcbOffset;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil);

#endif /* _MAIN_ */