#include <SFML/Graphics.hpp>
#include <filesystem>
#include <random>
#include <string>

// Цвета интерфейса
#define OK_COLOR sf::Color(96, 192, 139)
#define ERROR_COLOR sf::Color(192, 187, 96)
#define BACK_COLOR sf::Color(187, 96, 192)

int main() {
  // Рандом
  std::random_device rd;
  std::mt19937 rng(rd());
  // Возможные знаки для ввода
  const int charsQuantity = 66;
  const char charArr[charsQuantity]{
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'a', 'B', 'b',
      'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i',
      'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p',
      'Q', 'q', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u', 'V', 'v', 'W', 'w',
      'X', 'x', 'Y', 'y', 'Z', 'z', '-', '+', ',', '.'};
  // Настройки времени и задержек
  const float timeToPress = 2;
  const float timeToWatchError = 0.5;
  const int allGameTime = 30;
  int gameTime = allGameTime;
  // Изменяемые переменные индекса вводимого знака, текущего счёта и запуск игры
  int charIndex = 0;
  int currentScore = 0;
  bool isPlaying = false;
  // Окно
  const float windowWidth = 800;
  const float windowHeight = 600;
  sf::RenderWindow window(
      sf::VideoMode({static_cast<unsigned int>(windowWidth),
                     static_cast<unsigned int>(windowHeight)},
                    32),
      "tap^       (504464 mod 2) + 1 = 1",
      sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);
  // Тексты
  const sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
  //     Текст символа для ввода
  sf::Text keyText(font);
  keyText.setCharacterSize(windowHeight / 3);
  keyText.setPosition({0.4 * windowWidth, 0.3 * windowHeight});
  keyText.setFillColor(OK_COLOR);
  keyText.setString(charArr[charIndex]);
  //    Текст текущего счёта
  sf::Text scoreText(font);
  scoreText.setString("Your score: " + std::to_string(currentScore));
  scoreText.setCharacterSize(40);
  scoreText.setFillColor(OK_COLOR);
  //    Текст оставшегося времени
  sf::Text timeText(font);
  timeText.setCharacterSize(40);
  timeText.setPosition({0, 40});
  timeText.setFillColor(OK_COLOR);
  //    Текст меню
  sf::Text menuText(font);
  menuText.setPosition({130, 200});
  menuText.setCharacterSize(80);
  menuText.setFillColor(OK_COLOR);
  menuText.setString("Press spase\n  to run");
  // Таймеры - таймер для ввода и таймер игры
  sf::Clock tapTimer;
  sf::Clock gameTimer;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() ||
          (event->is<sf::Event::KeyPressed>() &&
           event->getIf<sf::Event::KeyPressed>()->code ==
               sf::Keyboard::Key::Escape)) {
        window.close();
        break;
      }
      if (isPlaying) {
        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
          if (textEvent->unicode == charArr[charIndex]) {
            tapTimer.restart();
            std::uniform_int_distribution<> dist(0, charsQuantity - 1);
            charIndex = dist(rng);
            keyText.setString(charArr[charIndex]);
            keyText.setFillColor(OK_COLOR);
            currentScore++;
          } else {
            gameTime--;
          }
        }
      } else {
        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
          if (textEvent->unicode == ' ') {
            isPlaying = true;
            currentScore = 0;
            gameTimer.restart();
            gameTime = allGameTime;
          }
        }
      }
    }
    if (isPlaying) {
      sf::Time curentTupTime = tapTimer.getElapsedTime();
      if (curentTupTime.asSeconds() > timeToPress) {
        keyText.setFillColor(ERROR_COLOR);
        if (curentTupTime.asSeconds() > timeToPress + timeToWatchError) {
          keyText.setFillColor(OK_COLOR);
          tapTimer.restart();
          std::uniform_int_distribution<> dist(0, charsQuantity - 1);
          charIndex = dist(rng);
          keyText.setString(charArr[charIndex]);
        }
      }
      sf::Time currentGametime = gameTimer.getElapsedTime();
      scoreText.setString("Your score: " + std::to_string(currentScore));
      timeText.setString("Time " +
                         std::to_string(static_cast<int>(
                             gameTime - currentGametime.asSeconds())) +
                         "/" + std::to_string(gameTime));
      if (currentGametime.asSeconds() >= gameTime) {
        isPlaying = false;
      }
    }
    window.clear(BACK_COLOR);
    if (isPlaying) {
      window.draw(keyText);
      window.draw(scoreText);
      window.draw(timeText);
    } else {
      timeText.setString("\nNow you\nIn main menu");
      window.draw(timeText);

      window.draw(scoreText);
      window.draw(menuText);
    }
    window.display();
  }

  return 0;
}
