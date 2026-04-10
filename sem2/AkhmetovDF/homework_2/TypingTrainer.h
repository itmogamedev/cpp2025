#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class TypingTrainer {
 public:
  TypingTrainer();
  void run();

 private:
  // Основные методы игрового цикла
  void processEvents();  // обработка ввода с клавиатуры и закрытия окна
  void update(float delta_time);  // обновление таймера
  void render();                  // отрисовка всех элементов
  void generateNewChar();  // генерация нового случайного символа (строчная
                           // буква или знак)
  void resetGame();        // сброс состояния игры для перезапуска

  // Окно и графические объекты SFML
  sf::RenderWindow m_window;
  sf::Font m_font;
  sf::Text m_target_char_text;  // крупный символ в центре
  sf::Text m_score_text;
  sf::Text m_timer_text;
  sf::Text m_game_over_text;

  // Состояние игры
  char
      m_current_char;  // текущий целевой символ (в нижнем регистре, если буква)
  int m_score;
  float m_time_left;  // оставшееся время в секундах
  bool m_game_over;

  // Константы
  static constexpr float kInitialTime = 30.0f;  // начальное время (сек)
  static constexpr float kPenaltyTime = 2.0f;   // штраф за ошибку (сек)

  // Размеры окна
  static constexpr int kWindowWidth = 800;
  static constexpr int kWindowHeight = 600;

  // Размеры шрифтов
  static constexpr unsigned int kTargetCharSize = 200;
  static constexpr unsigned int kScoreTimerSize = 36;
  static constexpr unsigned int kGameOverSize = 48;
  static constexpr unsigned int kFinalScoreSize = 36;

  // Позиции текстовых элементов (координаты)
  static constexpr float kTargetCharX = 400.f;
  static constexpr float kTargetCharY = 250.f;
  static constexpr float kScoreX = 20.f;
  static constexpr float kScoreY = 20.f;
  static constexpr float kTimerX = 20.f;
  static constexpr float kTimerY = 70.f;
  static constexpr float kGameOverX = 200.f;
  static constexpr float kGameOverY = 250.f;
  static constexpr float kFinalScoreX = 300.f;
  static constexpr float kFinalScoreY = 400.f;

  // Диапазон печатных символов ASCII (32..126)
  static constexpr int kFirstAsciiPrintable = 32;
  static constexpr int kLastAsciiPrintable = 126;
};
