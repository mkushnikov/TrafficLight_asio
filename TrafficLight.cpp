#include "TrafficLight.h"

#include <iostream>
#include <string>

const int TrafficLight::yellowTimeBlinkFrequency_ = 1;
const int TrafficLight::yellowSwitchesMaxCount_ = 4;
const int TrafficLight::redTimeSwitch_ = 2;
const int TrafficLight::greenTimeSwitch_ = 3;

void TrafficLight::emulateTrafficLight()
{
	while (!isFinished_)
	{
		if (!isStopped_ && !isTimerRunning_)
		{
			trafficLightDrawer_.clearConsole();
			trafficLightDrawer_.showControllInfo();
			drawTL(currentTrafficLightState_);
			if (timeRemainingUntilSwitch_ != 0)
			{
				myTimer_.expires_from_now(boost::posix_time::milliseconds(timeRemainingUntilSwitch_ * 1000));
				isTimerRunning_ = true;
				myTimer_.async_wait([&](const boost::system::error_code& error) {
					if (!error)
					{
						updateTLState();
						isTimerRunning_ = false;
					}
					});
				timeRemainingUntilSwitch_ = 0;
			}
			else
			{
				myTimer_.expires_from_now(boost::posix_time::milliseconds(currentSwitchTime_ * 1000));
				isTimerRunning_ = true;
				myTimer_.async_wait([&](const boost::system::error_code& error) {
					if (!error)
					{
						updateTLState();
						isTimerRunning_ = false;
					}
					});
			}
		}
		myIo_->run();
	}
}

void TrafficLight::updateTLState()
{
	switch (currentTrafficLightState_)
	{
	case STATES::EMPTY:
		if (isYellowBlinking_)
		{
			currentTrafficLightState_ = STATES::YELLOW;
			currentYellowSwitchesCount_++;
		}
		else
		{
			currentTrafficLightState_ = STATES::RED;
			currentSwitchTime_ = redTimeSwitch_;
		}
		break;
	case STATES::RED:
		currentTrafficLightState_ = STATES::YELLOW;
		currentSwitchDirection_ = SWITCH_DIRECTION::FORWARD;
		isYellowBlinking_ = true;
		currentSwitchTime_ = yellowTimeBlinkFrequency_;
		break;
	case STATES::YELLOW:
		if (isYellowBlinking_ && currentYellowSwitchesCount_ < yellowSwitchesMaxCount_)
		{
			currentTrafficLightState_ = STATES::EMPTY;
			currentYellowSwitchesCount_++;
		}
		else if (currentSwitchDirection_ == SWITCH_DIRECTION::FORWARD)
		{
			isYellowBlinking_ = false;
			currentYellowSwitchesCount_ = 0;
			currentTrafficLightState_ = STATES::GREEN;
			currentSwitchTime_ = greenTimeSwitch_;
		}
		else
		{
			isYellowBlinking_ = false;
			currentYellowSwitchesCount_ = 0;
			currentTrafficLightState_ = STATES::RED;
			currentSwitchTime_ = redTimeSwitch_;
		}
		break;
	case STATES::GREEN:
		isYellowBlinking_ = true;
		currentTrafficLightState_ = STATES::YELLOW;
		currentSwitchDirection_ = SWITCH_DIRECTION::REVERSE;
		currentSwitchTime_ = yellowTimeBlinkFrequency_;
		break;
	default:
		break;
	}
}

void TrafficLight::drawTL(TrafficLight::STATES currentState)
{
	switch (currentState)
	{
	case TrafficLight::STATES::EMPTY:
		trafficLightDrawer_.drawEmpty();
		break;
	case TrafficLight::STATES::RED:
		trafficLightDrawer_.drawRed();
		break;
	case TrafficLight::STATES::YELLOW:
		trafficLightDrawer_.drawYellow();
		break;
	case TrafficLight::STATES::GREEN:
		trafficLightDrawer_.drawGreen();
		break;
	default:
		break;
	}
}

void TrafficLight::handlePressedKey(char pressedKey)
{
	switch (pressedKey)
	{
	case 'S':
	case 's':
		onStartButtonPressed();
		break;
	case 'P':
	case 'p':
		onPauseButtonPressed();
		break;
	case 'E':
	case 'e':
		onExitButtonPressed();
		break;
	default:
		break;
	}
}

void TrafficLight::onStartButtonPressed()
{
	if (isStopped_)
	{
		isStopped_ = false;
	}
}

void TrafficLight::onPauseButtonPressed()
{
	if (isTimerRunning_)
	{
		isStopped_ = true;
		myTimer_.cancel();
		isTimerRunning_ = false;
	}
}

void TrafficLight::onExitButtonPressed()
{
	isFinished_ = true;
	myIo_->stop();
}