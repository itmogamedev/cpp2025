#include "TypingTrainer.h"

#include <cctype>  // для std::isalpha, std::tolower
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

TypingTrainer::TypingTrainer()
    : m_window(sf::VideoMode({kWindowWidth, kWindowHeight}), "Typing Trainer"),
      m_target_char_text(m_font, "", kTargetCharSize),
      m_score_text(m_font, "", kScoreTimerSize),
      m_timer_text(m_font, "", kScoreTimerSize),
      m_game_over_text(m_font, "GAME OVER\nPress R to restart", kGameOverSize),
      m_score(0),
      m_time_left(kInitialTime),
      m_game_over(false) {
  // Инициализация генератора случайных чисел
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  // Загрузка шрифта (файл должен лежать рядом с исполняемым)
  if (!m_font.openFromFile("arial.ttf")) {
    std::cerr << "Error: cannot load font arial.ttf" << std::endl;
  }

  // Настройка внешнего вида текстов
  m_target_char_text.setFillColor(sf::Color::White);
  m_target_char_text.setStyle(sf::Text::Bold);
  m_target_char_text.setPosition({kTargetCharX, kTargetCharY});

  m_score_text.setFillColor(sf::Color::Cyan);
  m_score_text.setPosition({kScoreX, kScoreY});

  m_timer_text.setFillColor(sf::Color::Yellow);
  m_timer_text.setPosition({kTimerX, kTimerY});

  m_game_over_text.setFillColor(sf::Color::Red);
  m_game_over_text.setStyle(sf::Text::Bold);
  m_game_over_text.setPosition({kGameOverX, kGameOverY});

  generateNewChar();
}

void TypingTrainer::generateNewChar() {
  // Генерация случайного печатного символа из диапазона ASCII 32..126
  char new_char = static_cast<char>(
      kFirstAsciiPrintable +
      std::rand() % (kLastAsciiPrintable - kFirstAsciiPrintable + 1));

  if (std::isalpha(static_cast<unsigned char>(new_char))) {
    new_char =
        static_cast<char>(std::tolower(static_cast<unsigned char>(new_char)));
  }

  m_current_char = new_char;
  m_target_char_text.setString(std::string(1, m_current_char));

  // Центрирование текста по горизонтали и вертикали относительно его локальных
  // границ. setOrigin задаёт точку, относительно которой будет
  // позиционироваться текст.
  sf::FloatRect bounds = m_target_char_text.getLocalBounds();
  m_target_char_text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
  m_target_char_text.setPosition({kTargetCharX, kTargetCharY});
}

void TypingTrainer::resetGame() {
  m_score = 0;
  m_time_left = kInitialTime;
  m_game_over = false;
  generateNewChar();
}

void TypingTrainer::run() {
  sf::Clock clock;
  while (m_window.isOpen()) {
    float delta_time = clock.restart().asSeconds();
    processEvents();
    if (!m_game_over) {
      update(delta_time);
    }
    render();
  }
}

void TypingTrainer::processEvents() {
  // В SFML 3 pollEvent() возвращает std::optional<sf::Event>
  while (auto event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_window.close();
    } else if (event->is<sf::Event::TextEntered>()) {
      if (!m_game_over) {
        // Получаем указатель на конкретный тип события TextEntered
        const auto* text_event = event->getIf<sf::Event::TextEntered>();
        char input_char = static_cast<char>(text_event->unicode);

        // Приводим введённую букву к нижнему регистру
        if (std::isalpha(static_cast<unsigned char>(input_char))) {
          input_char = static_cast<char>(
              std::tolower(static_cast<unsigned char>(input_char)));
        }

        // Проверяем, что символ печатный (диапазон ASCII)
        if (input_char >= kFirstAsciiPrintable &&
            input_char <= kLastAsciiPrintable) {
          if (input_char == m_current_char) {
            ++m_score;
            generateNewChar();
          } else {
            // Неправильное нажатие – уменьшаем время (штраф)
            m_time_left -= kPenaltyTime;
            if (m_time_left < 0.f) m_time_left = 0.f;
          }
        }
      }
    } else if (event->is<sf::Event::KeyPressed>()) {
      const auto* key_event = event->getIf<sf::Event::KeyPressed>();
      // Клавиша R перезапускает игру в любой момент
      if (key_event->code == sf::Keyboard::Key::R) {
        resetGame();
      }
    }
  }
}

void TypingTrainer::update(float delta_time) {
  if (m_time_left > 0.f) {
    m_time_left -= delta_time;
    if (m_time_left <= 0.f) {
      m_time_left = 0.f;
      m_game_over = true;
    }
  }
}

void TypingTrainer::render() {
  m_window.clear(sf::Color::Black);

  // Обновляем тексты счёта и таймера
  m_score_text.setString("Score: " + std::to_string(m_score));
  m_timer_text.setString("Time: " +
                         std::to_string(static_cast<int>(m_time_left)));

  m_window.draw(m_target_char_text);
  m_window.draw(m_score_text);
  m_window.draw(m_timer_text);

  if (m_game_over) {
    // Создаём временный текст для отображения финального счёта
    sf::Text final_score_text(m_font, "Final Score: " + std::to_string(m_score),
                              kFinalScoreSize);
    final_score_text.setFillColor(sf::Color::White);
    final_score_text.setPosition({kFinalScoreX, kFinalScoreY});
    m_window.draw(m_game_over_text);
    m_window.draw(final_score_text);
  }

  m_window.display();
}
