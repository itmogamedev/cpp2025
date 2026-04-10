#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>

const int kStartTime = 60;
const int kTimePenalty = 5;

enum GamePhase {
  kBegin,
  kTyping,
  kFinish,
};

class Game : public sf::Drawable {
 public:
  void processInput(char32_t char_entered);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void updateTime();
  void startGame();
 
  private:
  sf::Font font;
  GamePhase phase;
  sf::Clock clock;
  sf::String word;
  int time = kStartTime;
  int score = 0;
};

#endif  // GAME_H_
