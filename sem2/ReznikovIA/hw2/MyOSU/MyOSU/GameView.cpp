#include "GameView.h"

#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Font.hpp"

void GameView::render() {
  renderWindow.clear();

  if (model.isGameOver()) {
    sf::RectangleShape buttonLose({180, 30});
    buttonLose.setPosition(
        {(model.getWidth() / 2.f) - 90, model.getHeight() - 100.f});
    buttonLose.setFillColor(sf::Color::Green);
    renderWindow.draw(buttonLose);

    sf::Text buttonText(font, "Restart", 30);
    setPositionCenter(buttonText, (model.getWidth() / 2.f),
                      model.getHeight() - 85.f);
    renderWindow.draw(buttonText);
  } else {
    const std::vector<Circle>& balls = model.getBalls();
    for (int i = 0; i < balls.size(); ++i) {
      sf::CircleShape circleShape(balls[i].radius, 30);
      circleShape.setFillColor(sf::Color::Green);
      circleShape.setPosition(balls[i].position);
      renderWindow.draw(circleShape);
    }

    timerText.setString(std::format("{:.1f}", model.getTimer()));
    renderWindow.draw(timerText);
  }

  renderWindow.display();
}

void GameView::setPositionCenter(sf::Text& text, float xPosition,
                                 float yPosition) {
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                  bounds.position.y + bounds.size.y / 2.f});
  text.setPosition({xPosition, yPosition});
}

// centerTextHorizontally(buttonText, model.getWidth(), model.getHeight() -
// 100.f); renderWindow.draw(buttonText);
