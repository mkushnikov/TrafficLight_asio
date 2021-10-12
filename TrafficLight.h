#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/timer/timer.hpp>

#include "TrafficLightDrawer.h"

class TrafficLight
{
private:
	// ������ ��������� ��������� ��� ���������
	enum class STATES
	{
		EMPTY,
		RED,
		YELLOW,
		GREEN
	};

	// ������ ����������� ������������ ������
	enum class SWITCH_DIRECTION
	{
		FORWARD,
		REVERSE
	};

	// ������� ��� �������� �����
	static const int redTimeSwitch_;
	// ������� ��� ������� �����
	static const int greenTimeSwitch_;
	// ������� ������� ������
	static const int yellowTimeBlinkFrequency_;
	//����. ���-�� ������� ��� ������
	static const int yellowSwitchesMaxCount_;

	// ������� �������
	int currentYellowSwitchesCount_;

	// ����������, �������� ������������ ��� ���
	bool isStopped_;
	// ������������ ��� ���������� ������ ���������
	bool isFinished_;
	// ������������ ��� ����� ��������� ��������� �� ����� ������� ������
	bool isYellowBlinking_;

	// �������� ������� ����� �������
	int currentSwitchTime_;

	// ������� ��������� ���������
	STATES currentTrafficLightState_;
	// ����������� ������������
	SWITCH_DIRECTION currentSwitchDirection_;

	//IO
	boost::shared_ptr<boost::asio::io_context> myIo_;
	//boost::shared_ptr<boost::asio::io_context::work> myWork_;

	//������ ��� ������������ ���������
	boost::asio::deadline_timer myTimer_;

	//����, ������� �� ������
	bool isTimerRunning_;

	//���������� ��� �������� ���-�� ������� � ������ �����
	int timeRemainingUntilSwitch_;

	// ��������� ������� ���������
	TrafficLightDrawer trafficLightDrawer_;
	// ������������ ������ ���� � ����������� �� ������
	void drawTL(TrafficLight::STATES currentState);

	// ��������� ����� ���������
	void updateTLState();

	//������� ��� ������� �� ����
	void onPauseButtonPressed();
	void onStartButtonPressed();
	void onExitButtonPressed();

public:
	//�������� ���� ������ ���������
	void emulateTrafficLight();

	//���������� �����
	void handlePressedKey(char pressedKey);

	TrafficLight()
		: isStopped_(false),
		isFinished_(false),
		isYellowBlinking_(false),
		currentSwitchTime_(0),
		currentTrafficLightState_(TrafficLight::STATES::EMPTY),
		currentSwitchDirection_(TrafficLight::SWITCH_DIRECTION::FORWARD),
		timeRemainingUntilSwitch_(0),
		currentYellowSwitchesCount_(0),
		myIo_(new boost::asio::io_context),
		myTimer_(*myIo_),
		isTimerRunning_(false)
	{

	}
};
#endif