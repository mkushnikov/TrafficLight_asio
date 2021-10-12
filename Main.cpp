#include "TrafficLight.h"
#include "Input.h"

#include <boost/thread.hpp>

int main(int argc, char* argv[])
{
	TrafficLight myTL;
	Input myInput;

	myInput.addSub([&](char k)
		{ myTL.handlePressedKey(k); });

	boost::thread input(&Input::handleInput, myInput);

	myTL.emulateTrafficLight();

	input.detach();
	return 0;
}
