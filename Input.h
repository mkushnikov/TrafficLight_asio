#ifndef INPUT_H_
#define INPUT_H_

#include <functional>
#include <vector>

class Input
{
private:
    // ������� �������
    char pressedKey_;

    // ������ �����������
    std::vector<std::function<void(char pressedKey)>> subsList_;

public:
    // �������� ������� ��� �����
    // ��������� ������ �� ��������� �����
    void handleInput();

    // ��������� ����������� � ������
    void addSub(std::function<void(char pressedKey)> subCallback);

    // ���������� ���� ����������� � �������
    void notifySubs();

    Input()
    {
    }
};
#endif