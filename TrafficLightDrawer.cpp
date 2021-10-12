#include <iostream>

#include "TrafficLightDrawer.h"

using std::cout;

void TrafficLightDrawer::showControllInfo()
{
    cout << "The Traffic Light @mkushnikov\n";
    cout << "Press P to pause\n";
    cout << "Press S to start\n";
    cout << "Press E to exit\n";
    cout << "Enjoy!\n";
    cout << "\n";
}

void TrafficLightDrawer::clearConsole()
{
    system("cls");
}

const std::vector<std::string_view> TrafficLightDrawer::emptyCircle_ = {
    "    ---   ",
    "  /     \\  ",
    " /       \\ ",
    "|         |",
    " \\       / ",
    "  \\     /  ",
    "    ---    "};

const std::vector<std::string_view> TrafficLightDrawer::redCircle_ = {
    "    ---   ",
    "  / RRR \\  ",
    " / RRRRR \\ ",
    "| RRRRRRR |",
    " \\ RRRRR / ",
    "  \\ RRR /  ",
    "    ---    "};

const std::vector<std::string_view> TrafficLightDrawer::yellowCircle_ = {
    "    ---   ",
    "  / YYY \\  ",
    " / YYYYY \\ ",
    "| YYYYYYY |",
    " \\ YYYYY / ",
    "  \\ YYY /  ",
    "    ---    "};

const std::vector<std::string_view> TrafficLightDrawer::greenCircle_ = {
    "    ---   ",
    "  / GGG \\  ",
    " / GGGGG \\ ",
    "| GGGGGGG |",
    " \\ GGGGG / ",
    "  \\ GGG /  ",
    "    ---    "};

void TrafficLightDrawer::showLight(const std::vector<std::string_view> &circle)
{
    for (auto line : circle)
    {
        cout << line << "\n";
    }
}

void TrafficLightDrawer::drawEmpty()
{
    showLight(emptyCircle_);
    showLight(emptyCircle_);
    showLight(emptyCircle_);
}

void TrafficLightDrawer::drawRed()
{
    showLight(redCircle_);
    showLight(emptyCircle_);
    showLight(emptyCircle_);
}

void TrafficLightDrawer::drawYellow()
{
    showLight(emptyCircle_);
    showLight(yellowCircle_);
    showLight(emptyCircle_);
}

void TrafficLightDrawer::drawGreen()
{
    showLight(emptyCircle_);
    showLight(emptyCircle_);
    showLight(greenCircle_);
}