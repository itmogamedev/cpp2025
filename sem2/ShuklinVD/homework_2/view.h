#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "game_model.h"

class View {
 private:
  sf::RenderWindow window;
  sf::Font font;
  sf::Text score_text;
  sf::Text timer_text;
  sf::Text final_text;

 public:
  View();
  void updateScoreText(GameModel& game);
  void updateTimeText(GameModel& game);
  void setFinalText(GameModel& game);
  void render(GameModel& game);
  bool isOpen() const;
  void close();
  sf::RenderWindow& getWindow();
};

#endif
