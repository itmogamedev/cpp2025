#include "view.h"

#include <string>

View::View(sf::RenderWindow& window, Model& model)
    : window(window), model(model) {
  loadFont();
  scoreText = sf::Text(font);
  scoreText->setCharacterSize(30);
  scoreText->setFillColor(sf::Color::White);
  scoreText->setPosition(sf::Vector2f(10, 10));

  timerText = sf::Text(font);
  timerText->setCharacterSize(30);
  timerText->setFillColor(sf::Color::White);
  timerText->setPosition(sf::Vector2f(10, 50));

  gameOverText = sf::Text(font);
  gameOverText->setCharacterSize(40);
  gameOverText->setFillColor(sf::Color::Red);
  gameOverText->setString("GAME OVER\nPress R to restart");
  gameOverText->setPosition(sf::Vector2f(200, 250));
}

void View::loadFont() {
  if (!font.openFromFile("arial.ttf")) {
    // error...
  }
}

void View::updateTexts() {
  scoreText->setString("Score: " + std::to_string(model.getScore()));
  timerText->setString(
      "Time: " + std::to_string(static_cast<int>(model.getTimeLeft())) + "s");
}

void View::draw() {
  window.clear(sf::Color::Black);

  for (const auto& circle : model.getCircles()) {
    sf::CircleShape shape(circle.radius);
    shape.setPosition(sf::Vector2f(circle.position.x - circle.radius,
                                   circle.position.y - circle.radius));
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    window.draw(shape);
  }

  updateTexts();
  window.draw(*scoreText);
  window.draw(*timerText);

  if (!model.isActive()) {
    window.draw(*gameOverText);
  }

  window.display();
}
