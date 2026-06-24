#pragma once
#include <SFML/Graphics.hpp>

#include "GameModel.h"

class GameView {
 public:
  GameView(float screen_width, float screen_height);

  void loadResources();
  void render(sf::RenderWindow& window, GameModel& model);

 private:
  void drawBackground(sf::RenderWindow& window);
  void drawHUD(sf::RenderWindow& window, GameModel& model);
  void drawGameOver(sf::RenderWindow& window, GameModel& model);

  float screen_width;
  float screen_height;

  sf::Texture ship_texture;
  sf::Texture asteroid_texture;
  sf::Texture background_texture;

  sf::Sprite background_sprite;

  sf::Font font;
};
