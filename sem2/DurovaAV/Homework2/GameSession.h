#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Ball.h"

class GameSession {
 public:
  GameSession();
  void launch();

 private:
  void pollInput();
  void advance(float deltaTime);
  void drawFrame();
  void processClick(sf::Vector2i mouseCoord);
  void spawnInitialBalls();
  void updateDisplayTexts();

  sf::RenderWindow mainWindow_;
  std::vector<Ball> balls_;

  int currentScore_;
  float remainingTime_;
  bool isActive_;

  sf::Font uiFont_;
  sf::Text scoreDisplay_;
  sf::Text timerDisplay_;
  sf::Text gameoverDisplay_;

  sf::Clock frameClock_;
};

#endif
