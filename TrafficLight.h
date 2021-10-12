#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/timer/timer.hpp>

#include "TrafficLightDrawer.h"

class TrafficLight
{
private:
	// Список состояний светофора для отрисовки
	enum class STATES
	{
		EMPTY,
		RED,
		YELLOW,
		GREEN
	};

	// Список направлений переключения цветов
	enum class SWITCH_DIRECTION
	{
		FORWARD,
		REVERSE
	};

	// Тайминг для красного цвета
	static const int redTimeSwitch_;
	// Тайминг для зелёного цвета
	static const int greenTimeSwitch_;
	// Частота мигания жёлтого
	static const int yellowTimeBlinkFrequency_;
	//Макс. кол-во миганий для жёлтого
	static const int yellowSwitchesMaxCount_;

	// Счётчик миганий
	int currentYellowSwitchesCount_;

	// Определяет, запущено переключение или нет
	bool isStopped_;
	// Используется для завершения работы светофора
	bool isFinished_;
	// Используется для смены состояний светофора по время мигания жёлтого
	bool isYellowBlinking_;

	// Содержит текущее время мигания
	int currentSwitchTime_;

	// Текущее состояние светофора
	STATES currentTrafficLightState_;
	// Направление переключения
	SWITCH_DIRECTION currentSwitchDirection_;

	//IO
	boost::shared_ptr<boost::asio::io_context> myIo_;
	//boost::shared_ptr<boost::asio::io_context::work> myWork_;

	//Таймер для переключений светофора
	boost::asio::deadline_timer myTimer_;

	//Флаг, запущен ли таймер
	bool isTimerRunning_;

	//Переменная для хранения кол-ва времени в случае Паузы
	int timeRemainingUntilSwitch_;

	// Отрисовка стейтов светофора
	TrafficLightDrawer trafficLightDrawer_;
	// Отрисовываем нужный цвет в зависимости от стейта
	void drawTL(TrafficLight::STATES currentState);

	// Обновляем стейт светофора
	void updateTLState();

	//Функции для реакции на ввод
	void onPauseButtonPressed();
	void onStartButtonPressed();
	void onExitButtonPressed();

public:
	//Основной цикл работы светофора
	void emulateTrafficLight();

	//Обработчик ввода
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