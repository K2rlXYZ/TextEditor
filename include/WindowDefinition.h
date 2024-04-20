#include <Windows.h>
#include <tuple>

extern RECT windowRect;
extern RECT titleBarRect;
std::tuple<RECT *, LRESULT> RESIZE_RECTS[];

void SetSizesAndPositions(HWND hwnd, LPARAM lParam);
void PaintWindow(HWND hwnd);
LRESULT HitTest(HWND hwnd, LPARAM lParam);
void MinMaxWindowSize(LPARAM lParam);