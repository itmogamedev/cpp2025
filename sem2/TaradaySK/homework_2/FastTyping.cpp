#include "FastTyping.h"
char FastTyping::getRandomLetter() {
  const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, static_cast<int>(charset.size() - 1));
  return charset[dis(gen)];
}
bool FastTyping::Game() {
  sf::RenderWindow window(sf::VideoMode({1000, 400}), "HW2_FastTyping");
  sf::Font font;
  sf::Clock clock;
  window.setFramerateLimit(60);
  if (font.openFromFile("C:/Windows/Fonts/arial.ttf") == false) return -1;
  sf::Text randText(font);
  sf::Text timerText(font);
  sf::Text scoreText(font);
  randText.setCharacterSize(150);
  timerText.setCharacterSize(50);
  scoreText.setCharacterSize(50);
  timerText.setPosition({20.f, 10.f});
  scoreText.setPosition({20.f, 60.f});
  randText.setPosition({450.f, 200.f});
  timerText.setFillColor(sf::Color::White);
  scoreText.setFillColor(sf::Color::White);
  randText.setFillColor(sf::Color::White);
  char targetLetter = getRandomLetter();
  float timeLeft = 60.0f;
  int Score = 0;
  bool gameOver = false;
  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      if (gameOver == false && event->is<sf::Event::KeyPressed>()) {
        auto keyPressed = event->getIf<sf::Event::KeyPressed>();
        char pressedChar = '\\0';

        switch (keyPressed->code) {
          case sf::Keyboard::Key::A:
          case sf::Keyboard::Key::B:
          case sf::Keyboard::Key::C:
          case sf::Keyboard::Key::D:
          case sf::Keyboard::Key::E:
          case sf::Keyboard::Key::F:
          case sf::Keyboard::Key::G:
          case sf::Keyboard::Key::H:
          case sf::Keyboard::Key::I:
          case sf::Keyboard::Key::J:
          case sf::Keyboard::Key::K:
          case sf::Keyboard::Key::L:
          case sf::Keyboard::Key::M:
          case sf::Keyboard::Key::N:
          case sf::Keyboard::Key::O:
          case sf::Keyboard::Key::P:
          case sf::Keyboard::Key::Q:
          case sf::Keyboard::Key::R:
          case sf::Keyboard::Key::S:
          case sf::Keyboard::Key::T:
          case sf::Keyboard::Key::U:
          case sf::Keyboard::Key::V:
          case sf::Keyboard::Key::W:
          case sf::Keyboard::Key::X:
          case sf::Keyboard::Key::Y:
          case sf::Keyboard::Key::Z:
            pressedChar = 'A' + (static_cast<char>(keyPressed->code) -
                                 static_cast<char>(sf::Keyboard::Key::A));
            break;

          case sf::Keyboard::Key::Num0:
          case sf::Keyboard::Key::Num1:
          case sf::Keyboard::Key::Num2:
          case sf::Keyboard::Key::Num3:
          case sf::Keyboard::Key::Num4:
          case sf::Keyboard::Key::Num5:
          case sf::Keyboard::Key::Num6:
          case sf::Keyboard::Key::Num7:
          case sf::Keyboard::Key::Num8:
          case sf::Keyboard::Key::Num9:
            pressedChar = '0' + (static_cast<char>(keyPressed->code) -
                                 static_cast<char>(sf::Keyboard::Key::Num0));
            break;

          default:
            break;
        }

        if (pressedChar != '\\0') {
          if (pressedChar == targetLetter) {
            targetLetter = getRandomLetter();
            timeLeft = 10.0f - (Score / 10);
            Score++;
          } else {
            timeLeft -= 2.0f;
          }
        }
      }
    }

    if (gameOver == false) {
      timeLeft -= deltaTime;
      if (timeLeft <= 0) {
        timeLeft = 0;
        gameOver = true;
      }
    }

    if (gameOver == false) {
      randText.setString(std::string(1, targetLetter));
      timerText.setString("Time: " +
                          std::to_string(static_cast<int>(timeLeft + 0.9f)));
      scoreText.setString("Score: " + std::to_string(Score));
    } else {
      randText.setString("You got: " + std::to_string(Score));
      randText.setPosition({150.f, 200.f});
    }

    sf::FloatRect bounds = randText.getLocalBounds();

    window.clear(sf::Color::Black);
    window.draw(randText);
    window.draw(timerText);
    window.draw(scoreText);
    window.display();
  }
}
