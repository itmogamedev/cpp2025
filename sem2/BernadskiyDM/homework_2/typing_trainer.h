#ifndef TYPING_TRAINER_H
#define TYPING_TRAINER_H

#include <SFML/Graphics.hpp>
#include <string>

class TypingTrainer {
  public:
    //В конструкторе задаём сколько игра будет длиться
    TypingTrainer(int total_time);
    ~TypingTrainer(); //Деструктор для удаления указателей 
    //Запуск игры
    void run();

  private:
    //Инициализация графических ресурсов;
    void initResouces();
    void generateNewTarget();
    void handleInput(uint32_t unicode_symbol);
    void update();
    void render();

    //Окно и рерсурсы
    sf::RenderWindow window;
    sf::Font font;
    // Указатели решают проблему конструктора SFML 3.0
    sf::Text* target_text;
    sf::Text* info_text;

    //Поля
    char target_char;
    int score;
    float time_limit;
    float remaining_time;
    bool is_game_over;

    //Время
    sf::Clock clock;
};

#endif //TYPING_TRAINER_H
