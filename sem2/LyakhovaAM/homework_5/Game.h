#ifndef MINIHW5_GAME_H_
#define MINIHW5_GAME_H_

#include <SFML/Graphics.hpp>
#include <vector>

const std::vector<std::string> card_patterns = {
    "UwU", "(/>v<)/ ", "T_T", "\\(0v0)/ ", ">:>", "QWQ", "(*_*&)", "/G_G\\"};

class Game : public sf::Drawable, sf::Transformable {
  sf::Font font;
  sf::Clock clock;
  int turns;
  int count_opened_cards;
  std::vector<std::string> cards;
  std::vector<bool> opened_cards, left_cards;
  bool win;

 public:
  int faults;
  Game();
  void randomizeCards();
  void turn(sf::Vector2i mouse);
  void checkCards();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif  // MINIHW5_GAME_H_
