#ifndef INPUT_H_
#define INPUT_H_

#include <functional>
#include <vector>

class Input
{
private:
    // Нажатая клавиша
    char pressedKey_;

    // Список подписчиков
    std::vector<std::function<void(char pressedKey)>> subsList_;

public:
    // Основная функция для ввода
    // Реагирует только на латинские буквы
    void handleInput();

    // Добавляем подписчиков в список
    void addSub(std::function<void(char pressedKey)> subCallback);

    // Уведомляем всех подписчиков о событии
    void notifySubs();

    Input()
    {
    }
};
#endif