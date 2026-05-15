#include "game_model.h"

#include <cmath>
#include <cstdlib>

int GameModel::random(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void GameModel::spawnCircle(std::vector<OsuCircle>& array) {
  float x = random(0, WIDTH_OF_WINDOW - DIAMETR_OF_CIRCLE);
  float y = random(0, HEIGHT_OF_WINDOW - DIAMETR_OF_CIRCLE);
  float speed_x = random(MIN_SPEED, MAX_SPEED);
  float speed_y = random(MIN_SPEED, MAX_SPEED);
  array.push_back(OsuCircle(x, y, sf::Vector2f(speed_x, speed_y)));
}

void GameModel::initCircles(std::vector<OsuCircle>& array,
                            int count_of_circles) {
  for (int i = 0; i < count_of_circles; i++) {
    spawnCircle(array);
  }
}

void GameModel::initiateGame() {
  initCircles(circles, COUNT_OF_CIRCLES);
  clock.restart();
}

void GameModel::timerUpdate() {
  float deltaTime = clock.restart().asSeconds();
  time -= deltaTime;
  if (time < 0) {
    is_game_running = false;
  }
}

void GameModel::penaltyTime(float penalty_size) { time -= penalty_size; }

void GameModel::update() {
  for (int i = 0; i < circles.size(); i++) {
    circles[i].moveCircle();
  }
  timerUpdate();
  if (!is_game_running) {
    circles.clear();
  }
}

std::vector<OsuCircle>& GameModel::getCircles() { return circles; }

void GameModel::addPoints(int points) { score += points; }

int& GameModel::getScore() { return score; }

float& GameModel::getTime() { return time; }

bool GameModel::getIsGameRunning() { return is_game_running; }
