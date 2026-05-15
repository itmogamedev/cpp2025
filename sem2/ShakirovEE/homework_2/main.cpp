#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <optional>
#include <random>
#include <string>

class TypingGame {
 private:
  static constexpr float INITIAL_TIME = 10.0f;
  static constexpr float PENALTY_TIME = 1.0f;
  static constexpr sf::Vector2u WINDOW_SIZE = {800, 600};
  static constexpr unsigned FONT_SIZE_LARGE = 72;
  static constexpr unsigned FONT_SIZE_MEDIUM = 36;

  sf::RenderWindow window;
  sf::Font font;

  std::optional<sf::Text> currentCharText;
  std::optional<sf::Text> scoreText;
  std::optional<sf::Text> timerText;

  sf::Clock gameClock;
  float remainingTime;
  int score;
  bool isGameActive;
  char currentChar;

  std::random_device randomDevice;
  std::mt19937 randomGenerator;
  std::uniform_int_distribution<int> charDistribution;

  void generateNewChar() {
    currentChar = static_cast<char>(charDistribution(randomGenerator));
    if (currentCharText.has_value()) {
      currentCharText->setString(std::string(1, currentChar));
    }
  }

  void updateUIText() {
    if (scoreText.has_value()) {
      scoreText->setString("Score: " + std::to_string(score));
    }
    if (timerText.has_value()) {
      timerText->setString("Time: " +
                           std::to_string(static_cast<int>(remainingTime)));
    }
  }

 public:
  TypingGame()
      : window(sf::VideoMode(WINDOW_SIZE), "Typing Trainer"),
        randomGenerator(randomDevice()),
        charDistribution(33, 126),
        remainingTime(INITIAL_TIME),
        score(0),
        isGameActive(true) {
    if (!font.openFromFile("arial.ttf")) {
      std::cerr << "Warning: Could not load arial.ttf" << std::endl;
    }

    currentCharText.emplace(font);
    scoreText.emplace(font);
    timerText.emplace(font);

    currentCharText->setCharacterSize(FONT_SIZE_LARGE);
    currentCharText->setFillColor(sf::Color::White);
    sf::FloatRect textRect = currentCharText->getLocalBounds();
    currentCharText->setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                                textRect.position.y + textRect.size.y / 2.0f});
    currentCharText->setPosition({WINDOW_SIZE.x / 2.0f, WINDOW_SIZE.y / 2.0f});

    scoreText->setCharacterSize(FONT_SIZE_MEDIUM);
    scoreText->setFillColor(sf::Color::Green);
    scoreText->setPosition({20.0f, 20.0f});

    timerText->setCharacterSize(FONT_SIZE_MEDIUM);
    timerText->setFillColor(sf::Color::Yellow);
    timerText->setPosition({WINDOW_SIZE.x - 150.0f, 20.0f});

    generateNewChar();
    updateUIText();
  }

  void run() {
    while (window.isOpen()) {
      while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          window.close();
        } else if (const auto* keyEvent =
                       event->getIf<sf::Event::KeyPressed>()) {
          if (keyEvent->scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
          }
        } else if (const auto* textEvent =
                       event->getIf<sf::Event::TextEntered>()) {
          if (!isGameActive) continue;

          char enteredChar = static_cast<char>(textEvent->unicode);
          if (enteredChar >= 32 && enteredChar <= 126) {
            if (enteredChar == currentChar) {
              score++;
              generateNewChar();
            } else {
              remainingTime -= PENALTY_TIME;
              if (remainingTime < 0) remainingTime = 0;
            }
            updateUIText();
          }
        }
      }

      if (isGameActive) {
        sf::Time elapsed = gameClock.restart();
        remainingTime -= elapsed.asSeconds();
        updateUIText();
        if (remainingTime <= 0.0f) {
          isGameActive = false;
          remainingTime = 0.0f;
          if (timerText.has_value()) {
            timerText->setFillColor(sf::Color::Red);
          }
          updateUIText();
        }
      }

      window.clear(sf::Color::Black);
      if (currentCharText.has_value()) window.draw(*currentCharText);
      if (scoreText.has_value()) window.draw(*scoreText);
      if (timerText.has_value()) window.draw(*timerText);

      if (!isGameActive) {
        sf::Text gameOverText(font);
        gameOverText.setString("Game Over!\nPress ESC to exit");
        gameOverText.setCharacterSize(FONT_SIZE_MEDIUM);
        gameOverText.setFillColor(sf::Color::Red);
        sf::FloatRect textRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                                textRect.position.y + textRect.size.y / 2.0f});
        gameOverText.setPosition(
            {WINDOW_SIZE.x / 2.0f, WINDOW_SIZE.y / 2.0f + 100.0f});
        window.draw(gameOverText);
      }

      window.display();
    }
  }
};

int main() {
  TypingGame game;
  game.run();
  return 0;
}
