#ifndef DRAWER_H
#define DRAWER_H

#include <vector>
#include <string_view>

class TrafficLightDrawer
{
private:
	// ���������� ������� ��� ������ ���������
	static const std::vector<std::string_view> emptyCircle_;

	static const std::vector<std::string_view> redCircle_;

	static const std::vector<std::string_view> yellowCircle_;

	static const std::vector<std::string_view> greenCircle_;

	// ������� ��� ��������� ������ ���������
	void showLight(const std::vector<std::string_view>& circle);

public:
	// ������ �������
	void clearConsole();
	// ���������� �� ����������
	void showControllInfo();

	// ������� ��� ��������� ��������� � ���������� ������
	void drawEmpty();
	void drawRed();
	void drawYellow();
	void drawGreen();
};
#endif
