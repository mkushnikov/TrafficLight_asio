#ifndef DRAWER_H
#define DRAWER_H

#include <vector>
#include <string_view>

class TrafficLightDrawer
{
private:
	// Символьная графика для цветов светофора
	static const std::vector<std::string_view> emptyCircle_;

	static const std::vector<std::string_view> redCircle_;

	static const std::vector<std::string_view> yellowCircle_;

	static const std::vector<std::string_view> greenCircle_;

	// Функция для отрисовки цветов светофора
	void showLight(const std::vector<std::string_view>& circle);

public:
	// Чистка консоли
	void clearConsole();
	// Информация об управлении
	void showControllInfo();

	// Функции для отрисовки светофора в конкретном стейте
	void drawEmpty();
	void drawRed();
	void drawYellow();
	void drawGreen();
};
#endif
