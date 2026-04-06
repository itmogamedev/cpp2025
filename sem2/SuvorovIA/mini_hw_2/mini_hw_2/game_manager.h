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
  std::pair<int, int> circle_coordinates[5] = {{640, METER * 2},
                                               {640 - 2 * METER, METER * 4},
                                               {640 + 2 * METER, METER * 4},
                                               {640 - 1 * METER, METER * 6},
                                               {640 + 1 * METER, METER * 6}};
  sf::CircleShape current_circle;
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
