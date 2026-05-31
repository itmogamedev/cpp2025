#pragma once
#include <SFML/Graphics.hpp>

class Renderer {
 private:
  sf::RenderWindow& window;

 public:
  Renderer(sf::RenderWindow& win);

  void clear(const sf::Color& color = sf::Color::Black);
  void draw(const sf::Drawable& drawable);
  void display();
};