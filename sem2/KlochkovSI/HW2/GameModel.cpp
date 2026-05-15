#include "GameModel.h"

#include <cstdlib>

GameModel::GameModel()
    : time_remaining_(constants::kGameDuration), score_(0), game_over_(false) {
  initCircles();
}

void GameModel::initCircles() {
  circles_.clear();
  for (int i = 0; i < constants::kCircleCount; ++i) {
    circles_.emplace_back(
        constants::kCircleRadius,
        constants::kCircleColors[i % constants::kCircleCount]);
    circles_.back().randomize(static_cast<float>(constants::kWindowWidth),
                              static_cast<float>(constants::kWindowHeight));
  }
}

void GameModel::update(float delta_time) {
  time_remaining_ -= delta_time;
  if (time_remaining_ <= 0.f) {
    time_remaining_ = 0.f;
    game_over_ = true;
    return;
  }

  for (auto& circle : circles_) {
    circle.update(delta_time, static_cast<float>(constants::kWindowWidth),
                  static_cast<float>(constants::kWindowHeight));
  }
}

void GameModel::handleHit(int index) {
  circles_[index].randomize(static_cast<float>(constants::kWindowWidth),
                            static_cast<float>(constants::kWindowHeight));
  ++score_;
}

void GameModel::handleMiss() {
  time_remaining_ -= constants::kMissPenalty;
  if (time_remaining_ < 0.f) {
    time_remaining_ = 0.f;
  }
}

bool GameModel::isGameOver() const { return game_over_; }

int GameModel::getScore() const { return score_; }

float GameModel::getTimeRemaining() const { return time_remaining_; }

const std::vector<Circle>& GameModel::getCircles() const { return circles_; }

std::vector<Circle>& GameModel::getCircles() { return circles_; }
