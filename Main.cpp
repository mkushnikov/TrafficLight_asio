#include "TrafficLight.h"
#include "Input.h"

#include <thread>

int main(int argc, char* argv[])
{
    TrafficLight myTL;
    Input myInput;

    myInput.addSub([&](char k)
                   { myTL.handlePressedKey(k); });

    std::thread input(&Input::handleInput, myInput);

    myTL.emulateTrafficLight();

    input.detach();
    return 0;
}
