#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

class Game : public sf::Drawable
{
private:
  sf::Font font;
  sf::Text current_char_text;
  sf::Text score_text;
  sf::Text timer_text;
  sf::Text game_over_text;

  char current_char;
  int score;
  float time_left;
  bool is_game_over;
  float game_time;

  void generateNewChar();
  void updateTexts();

public:
  Game();
  void init();
  void handleInput(sf::Keyboard::Key key, bool shiftPressed);
  void update(float deltaTime);
  void run();
  bool isGameOver() const { return is_game_over; }
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif