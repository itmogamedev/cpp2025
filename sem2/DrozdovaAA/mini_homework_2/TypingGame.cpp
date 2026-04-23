#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>

class TypingGame {
 private:
  sf::RenderWindow window;
  sf::Font font;
  sf::Text screenText, additionalText;  // текст на экране и дополнительный
  std::string alf =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()"
      "-_=+[]{};:,.<>/?*";
  char desiredText;        // желаемый текст
  int scoreCounter = 0;    // счетчик очков
  float timeLeft = 25.0f;  // оставшееся время
  sf::Clock clock;         // часы начинают работать при запуске игры

 public:
  TypingGame() : window(sf::VideoMode(800, 500), "Typing Trainer") {
    if (!font.loadFromFile("arial.ttf")) exit(-1);
    screenText.setFont(font);
    screenText.setCharacterSize(150);
    screenText.setPosition(300, 150);
    additionalText.setFont(font);
    additionalText.setCharacterSize(22);
    additionalText.setPosition(25, 25);
    updateTarget();  // первый символ при запуске игры
  }

  void updateTarget() {
    desiredText =
        alf[std::rand() %
            alf.length()];  // геренация буквы = ранд число % длину алф
    screenText.setString(std::string(1, desiredText));  // поменять букву
  }

  void run() {
    while (window.isOpen()) {
      float time = clock.restart().asSeconds();  // прошедшее врея
      sf::Event e;
      while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) window.close();
        if (timeLeft > 0 && e.type == sf::Event::TextEntered &&
            e.text.unicode >= 32) {
          if (e.text.unicode == (sf::Uint32)desiredText) {
            scoreCounter++;
            updateTarget();
          } else
            timeLeft -= 2.0f;
        }
      }
      if (timeLeft > 0) {
        timeLeft -= time;
        additionalText.setString(
            "The score counter: " + std::to_string(scoreCounter) +
            "\nTime: " + std::to_string((int)timeLeft) + "s");
      } else
        screenText.setString("End!!");
      window.clear();
      window.draw(screenText);
      window.draw(additionalText);
      window.display();
    }
  }
};
