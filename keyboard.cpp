#include "keyboard.h"
#include "windows.h"

Keyboard::Keyboard() {}

void Keyboard::VolumeChange(bool increase)
{
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    if(increase){
        input.ki.wVk = VK_VOLUME_UP;
    } else{
        input.ki.wVk = VK_VOLUME_DOWN;
    }
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
}
