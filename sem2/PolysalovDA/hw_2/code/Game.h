#pragma once
#include <chrono>

#include "CircleSystem.h"
#include "Constants.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "UI.h"

class Game {
 private:
  sf::RenderWindow window;
  CircleSystem circles;
  InputHandler handler;
  Renderer renderer;
  UI ui;

  float time_left;
  float game_time;
  bool game_running;
  std::chrono::steady_clock::time_point last_time;

  void handleActions(const std::vector<Actions>& actions);
  void update();
  void draw();
  void resetGame();

 public:
  Game();
  void run();
};