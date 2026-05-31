#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "MovingCircle.h"
#include "Score.h"
#include "Timer.h"
#include "UI.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float deltaTime);
  void render();
  void restart();
  void spawnCircles();
  sf::Color generateRandomColor();

  sf::RenderWindow m_window;
  std::vector<MovingCircle> m_circles;
  Timer m_timer;
  Score m_score;
  UI m_ui;
  sf::Clock m_clock;
  bool m_gameActive;
  bool m_mousePressed;
};

#endif
