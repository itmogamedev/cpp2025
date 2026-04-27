#pragma once

#include <string>

#include "GameModel.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class GameView {
 public:
  GameView(GameModel& model, sf::RenderWindow& renderWindow,
           std::string fontFileName)
      : model(model),
        renderWindow(renderWindow),
        font(),
        timerText(font, std::format("{:.1f}", 30.f), 30) {
    font.openFromFile(fontFileName);
    timerText.setFont(font);
  }

  void render();
  sf::RenderWindow& renderWindow;

 private:
  void setPositionCenter(sf::Text& text, float xPosition, float yPosition);
  sf::Font font;
  sf::Text timerText;
  const GameModel& model;
};
