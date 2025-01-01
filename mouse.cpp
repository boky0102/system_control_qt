#include "mouse.h"
#include "windows.h"

Mouse::Mouse() {}

void Mouse::MoveCursor(int x, int y)
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    input.mi.dx = x;
    input.mi.dy = y;
    SendInput(1, &input, sizeof(INPUT));
    DWORD d = static_cast<DWORD>(0.01);
    Sleep(d);
}
