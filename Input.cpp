#include "Input.h"

#include <conio.h>

void Input::handleInput()
{
    while (true)
    {
        pressedKey_ = _getch();

        notifySubs();
    }
}

void Input::notifySubs()
{
    for (auto callback : subsList_)
    {
        callback(pressedKey_);
    }
}

void Input::addSub(std::function<void(char pressedKey)> subCallback)
{
    subsList_.push_back(subCallback);
}