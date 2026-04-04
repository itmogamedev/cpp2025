#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "constants.h"
#include "osu_circle.h"

class GameModel {
 private:
  int score = 0;
  float time = TIME_OF_GAME;
  sf::Clock clock;
  std::vector<OsuCircle> circles;
  bool is_game_running = true;

 public:
  int random(int min, int max);
  void spawnCircle(std::vector<OsuCircle>& array);
  void initCircles(std::vector<OsuCircle>& array, int count_of_circles);
  void initiateGame();
  void timerUpdate();
  void penaltyTime(float penalty_size);
  void update();
  std::vector<OsuCircle>& getCircles();
  void addPoints(int points);
  int& getScore();
  float& getTime();
  bool getIsGameRunning();
};

#endif
