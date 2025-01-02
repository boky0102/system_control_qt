#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
public:
    Mouse();
    static void MoveCursor(int x, int y);
    static void Click();
};

#endif // MOUSE_H
