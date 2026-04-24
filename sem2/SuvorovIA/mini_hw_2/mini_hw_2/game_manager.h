#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <utility>

#include "constants.h"
#include "utils.h"

using namespace Constants;

class GameManager {
 private:
  sf::Clock gameTimer;
  float time_left = Constants::GAMETIME;
  int int_timer = time_left;
  int score = 0;
  int past = -1;
  int loose_points = 5;
  std::vector<sf::CircleShape> circles;
  int max_circles = 5;
  sf::Font timer_font;
  sf::Font score_font;
  sf::Text timer_text;
  sf::Text score_text;
  enum class GameState { RUNNING, GAMEOVER };
  GameState state;
  sf::SoundBuffer hit_buffer;
  sf::Sound hit_sound;

 public:
  void initialize();
  void startGame();
};
