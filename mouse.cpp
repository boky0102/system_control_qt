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

void Mouse::Click()
{
    INPUT inputs[2] = {0};
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    Sleep(static_cast<DWORD>(0.01));
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(2, inputs, sizeof(INPUT));
}
