#ifndef TYPE_SIMULATOR_GAME_H_
#define TYPE_SIMULATOR_GAME_H_
#include <SFML/Graphics.hpp>

class Game : public sf::Drawable, public sf::Transformable {
  sf::Font font;
  sf::Clock clock;
  int time;

 public:
  char current_key;
  int points;
  Game();
  void turn(char key);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void randomizeKey();
};

#endif  // TYPE_SIMULATOR_GAME_H_
