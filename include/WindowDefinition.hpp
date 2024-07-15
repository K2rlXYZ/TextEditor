#ifndef _WINDOW_DEFINITION_
#define _WINDOW_DEFINITION_
#include <Windows.h>
#include <tuple>

#define PRIMARY_COLOR RGB(16, 16, 16)
#define SECONDARY_COLOR RGB(32, 32, 32)
#define TERTIARY_COLOR RGB(48, 48, 48)
#define RESIZE_BOX_SIZE 3

extern int resizeBoxSize;
extern RECT windowRect;
extern RECT titleBarRect;
extern RECT leftResizeRect;
extern RECT rightResizeRect;
extern RECT bottomResizeRect;
extern RECT bottomRightResizeRect;
extern RECT bottomLeftResizeRect;
const std::tuple<RECT *, LRESULT> RESIZE_RECTS[] = {
    {&titleBarRect, HTCAPTION},
    {&leftResizeRect, HTLEFT},
    {&rightResizeRect, HTRIGHT},
    {&bottomResizeRect, HTBOTTOM},
    {&bottomRightResizeRect, HTBOTTOMRIGHT},
    {&bottomLeftResizeRect, HTBOTTOMLEFT}
};
extern RECT contentArea;

void SetSizesAndPositions(HWND hwnd, LPARAM lParam);
void PaintWindow(HWND hwnd);
LRESULT HitTest(HWND hwnd, LPARAM lParam);
void MinMaxWindowSize(LPARAM lParam);
#endif /* _WINDOW_DEFINITION_ */