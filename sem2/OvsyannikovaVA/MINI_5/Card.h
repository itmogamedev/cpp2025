#include <SFML/Graphics.hpp>
#include <string>

class Card {
 public:
  sf::RectangleShape shape;
  sf::Font font;
  sf::Text text;

  std::string symbol;

  bool revealed = false;
  bool matched = false;

  Card();

  void draw(sf::RenderWindow& window);
  bool contains(sf::Vector2f point);
};
