#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();
  void generateNewTarget();

  sf::RenderWindow mWindow;
  sf::Font mFont;
  sf::Text mTargetText;
  sf::Text mScoreText;

  char mTargetChar;
  int mScore;
  float mTimeLeft;
  bool mIsGameOver;
};

#endif
