#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "CircleTarget.h"
#include "Utils.h"

class Game {
 public:
  Game(unsigned int width, unsigned int height, const std::string& title);
  void run();

 private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();
  void resetGame();
  void spawnTarget();
  bool isMouseOverTarget(const CircleTarget& target, float mouseX,
                         float mouseY);
  void handleClick(float mouseX, float mouseY);

  sf::RenderWindow window_;
  std::vector<CircleTarget> targets_;
  sf::Clock clock_;
  sf::Time game_time_limit_;
  sf::Time elapsed_game_time_;
  sf::Font font_;
  sf::Text score_text_;
  sf::Text timer_text_;
  int score_;
  bool is_game_over_;
  int initial_target_count_ = 5;
  float miss_penalty_time = 1.0f;
};
