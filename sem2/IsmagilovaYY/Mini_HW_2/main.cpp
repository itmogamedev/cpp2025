#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  constexpr float START_TIME = 20.0f;
  constexpr float PENALTY_TIME = 1.0f;
  constexpr float WARNING_TIME = 5.0f;

  setlocale(LC_ALL, "Russian");
  srand(static_cast<unsigned>(time(nullptr)));

  sf::RenderWindow window(sf::VideoMode({800, 600}), "Typing trainer");

  // загружаем шрифт
  sf::Font font;
  if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf")) {
    std::cout << "Ошибка загрузки шрифта" << std::endl;
    return -1;
  }

  // настраиваем таймер и счётчик
  sf::Clock gameClock;
  float timeLeft = START_TIME;
  int score = 0;
  char currentChar = 'A';

  // настраиваем базовый текст, расположение и цвет
  sf::Text scoreText(font, " ", 24);
  sf::Text timeText(font, " ", 24);
  sf::Text targetText(font, std::string(1, currentChar), 200);

  scoreText.setPosition({10, 10});
  timeText.setPosition({700, 10});
  targetText.setPosition({350, 200});

  scoreText.setFillColor(sf::Color::White);
  timeText.setFillColor(sf::Color::White);
  targetText.setFillColor(sf::Color::Yellow);

  sf::Clock deltaClock;

  // главный цикл
  while (window.isOpen()) {
    // настраиваем таймер
    float deltaTime = deltaClock.restart().asSeconds();

    if (timeLeft > 0) {
      timeLeft -= deltaTime;
      if (timeLeft < 0) timeLeft = 0;
    }

    // считываем события в очереди
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // getIf: если событие является нажатием клавиши, то возвращает указатель
      // на данные о клавише
      if (timeLeft > 0 && event->is<sf::Event::KeyPressed>()) {
        const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();

        if (keyEvent) {
          char pressedChar = '\0';
          // учитываем клавиши только в диапазоне
          if (keyEvent->code >= sf::Keyboard::Key::A &&
              keyEvent->code <= sf::Keyboard::Key::Z) {
            pressedChar =
                'A' + static_cast<char>(static_cast<int>(keyEvent->code) -
                                        static_cast<int>(sf::Keyboard::Key::A));
          }
          // проверяем ввод
          if (pressedChar == currentChar) {
            score++;
            currentChar = 'A' + (rand() % 26);
          } else if (pressedChar != '\0') {
            timeLeft -= PENALTY_TIME;
            if (timeLeft < 0.0f) timeLeft = 0.0f;
          }
        }
      }
    }
    // выводим счёт, время и букву
    scoreText.setString("Score: " + std::to_string(score));
    timeText.setString("Time: " + std::to_string(static_cast<int>(timeLeft)));
    targetText.setString(std::string(1, currentChar));

    // если меньше 5 секунд, то будем менять время на красный
    if (timeLeft < WARNING_TIME) {
      timeText.setFillColor(sf::Color::Red);
    } else {
      timeText.setFillColor(sf::Color::White);
    }
    // отрисовка
    window.clear(sf::Color(30, 30, 30));
    window.draw(scoreText);
    window.draw(timeText);
    window.draw(targetText);
    // завершение игры
    if (timeLeft <= 0.0f) {
      sf::Text gameOverText(
          font, "GAME OVER!\nFinal Score: " + std::to_string(score), 50);
      gameOverText.setPosition({200, 250});
      gameOverText.setFillColor(sf::Color::Red);
      window.draw(gameOverText);
    }
    // вывод на экран
    window.display();
  }

  return 0;
}
