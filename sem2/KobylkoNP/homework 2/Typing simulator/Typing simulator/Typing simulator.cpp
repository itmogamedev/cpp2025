#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <vector>

void runGame() {
  // Create window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Typing Trainer",
                          sf::Style::Default);
  window.setVerticalSyncEnabled(true);

  // Load font
  sf::Font font;
  if (!font.openFromFile("CHILLER.TTF")) {
    std::cerr << "Error: Failed to load font CHILLER.TTF\n";
    return;
  }

  // Text for displaying the current symbol
  sf::Text symbolText(font, "", 120);
  symbolText.setFillColor(sf::Color::White);
  symbolText.setPosition(sf::Vector2f(400, 250));
  symbolText.setOrigin(sf::Vector2f(symbolText.getLocalBounds().size.x / 2,
                                    symbolText.getLocalBounds().size.y / 2));

  // Score text
  sf::Text scoreText(font, "Score: 0", 30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(sf::Vector2f(20, 20));

  // Time text
  sf::Text timeText(font, "Time: 30.0", 30);
  timeText.setFillColor(sf::Color::White);
  timeText.setPosition(sf::Vector2f(20, 70));

  // Game over text
  sf::Text gameOverText(font, "GAME OVER\nFinal score: 0\nPress ESC to exit",
                        40);
  gameOverText.setFillColor(sf::Color::White);
  gameOverText.setPosition(sf::Vector2f(200, 250));

  // Set of allowed characters: a-z, 0-9, !@#$%^&*()
  std::vector<char> allowedChars;
  for (char c = 'a'; c <= 'z'; ++c) allowedChars.push_back(c);
  for (char c = '0'; c <= '9'; ++c) allowedChars.push_back(c);
  std::string special = "!@#$%^&*()";
  for (char c : special) allowedChars.push_back(c);

  // Random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> dist(0, allowedChars.size() - 1);

  // First random character
  char currentChar = allowedChars[dist(gen)];
  symbolText.setString(std::string(1, currentChar));
  symbolText.setOrigin(sf::Vector2f(symbolText.getLocalBounds().size.x / 2,
                                    symbolText.getLocalBounds().size.y / 2));

  // Game parameters
  float timeLeft = 30.0f;
  int score = 0;
  bool gameRunning = true;
  sf::Clock clock;

  // Main game loop
  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    // Event handling
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();

      if (gameRunning) {
        if (auto textEvent = event->getIf<sf::Event::TextEntered>()) {
          char typedChar = static_cast<char>(textEvent->unicode);
          if (typedChar >= 32 && typedChar <= 126) {
            if (typedChar == currentChar) {
              // Correct press
              score++;
              currentChar = allowedChars[dist(gen)];
              symbolText.setString(std::string(1, currentChar));
              symbolText.setOrigin(
                  sf::Vector2f(symbolText.getLocalBounds().size.x / 2,
                               symbolText.getLocalBounds().size.y / 2));
            } else {
              // Wrong press: penalty of 1 second
              timeLeft -= 1.0f;
              if (timeLeft < 0.0f) timeLeft = 0.0f;
            }
          }
        }
      } else {
        // After game over, only ESC key closes the window
        if (auto keyEvent = event->getIf<sf::Event::KeyPressed>()) {
          if (keyEvent->scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
          }
        }
      }
    }

    // Update time and check for game over
    if (gameRunning) {
      timeLeft -= deltaTime;
      if (timeLeft <= 0.0f) {
        timeLeft = 0.0f;
        gameRunning = false;
        gameOverText.setString("GAME OVER\nFinal score: " +
                               std::to_string(score) + "\nPress ESC to exit");
      }
    }

    // Update score and time texts
    scoreText.setString("Score: " + std::to_string(score));
    timeText.setString("Time: " + std::to_string(static_cast<int>(timeLeft)));

    // Rendering
    window.clear(sf::Color::Black);
    if (gameRunning) {
      window.draw(symbolText);
      window.draw(scoreText);
      window.draw(timeText);
    } else {
      window.draw(gameOverText);
    }
    window.display();
  }
}
