#include "Game.h"

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>

namespace {

constexpr size_t kNumCircles = 5;

}  // namespace

Game::Game()
    : window_(sf::VideoMode(800, 600), "Circle Clicker Game"),
      score_(0),
      time_left_(60.0f),
      game_over_(false),
      radius_(30.0f),
      penalty_amount_(2.0f),
      window_width_(800),
      window_height_(600),
      rng_(std::random_device{}()),
      pos_dist_x_(radius_, window_width_ - radius_),
      pos_dist_y_(radius_, window_height_ - radius_),
      vel_dist_(-100.0f, 100.0f) {
  if (!font_.loadFromFile("A:/C++/MiniHW2/x64/Material/arial.ttf")) {
    std::cerr << "Error: Cannot load arial.ttf. "
              << "Place the font file in the same folder as the executable.\n";
    std::exit(EXIT_FAILURE);
  }

  score_text_.setFont(font_);
  score_text_.setCharacterSize(24);
  score_text_.setFillColor(sf::Color::White);
  score_text_.setPosition(10.0f, 10.0f);

  time_text_.setFont(font_);
  time_text_.setCharacterSize(24);
  time_text_.setFillColor(sf::Color::White);
  time_text_.setPosition(10.0f, 40.0f);

  game_over_text_.setFont(font_);
  game_over_text_.setCharacterSize(36);
  game_over_text_.setFillColor(sf::Color::Red);
  game_over_text_.setPosition(window_width_ / 2.0f - 150.0f,
                              window_height_ / 2.0f - 50.0f);

  InitializeCircles();
  UpdateTexts();
}

void Game::Run() {
  constexpr float kMaxDt = 0.02f;

  while (window_.isOpen()) {
    ProcessEvents();

    float dt = delta_clock_.restart().asSeconds();
    if (dt > kMaxDt) {
      dt = kMaxDt;
    }

    if (!game_over_) {
      Update(dt);
    }

    Render();
  }
}

void Game::ProcessEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    } else if (event.type == sf::Event::MouseButtonPressed &&
               event.mouseButton.button == sf::Mouse::Left) {
      if (!game_over_) {
        int mouse_x = event.mouseButton.x;
        int mouse_y = event.mouseButton.y;
        int hit_index = CheckCircleClick(mouse_x, mouse_y);
        if (hit_index != -1) {
          ++score_;
          SpawnRandomPosition(hit_index);
          SpawnRandomVelocity(hit_index);
          UpdateTexts();
        } else {
          time_left_ -= penalty_amount_;
          if (time_left_ < 0.0f) {
            time_left_ = 0.0f;
          }
          UpdateTexts();
          if (time_left_ <= 0.0f) {
            game_over_ = true;
          }
        }
      }
    }
  }
}

void Game::Update(float dt) {
  for (size_t i = 0; i < circles_.size(); ++i) {
    sf::Vector2f pos = circles_[i].getPosition();
    pos += velocities_[i] * dt;

    if (pos.x - radius_ < 0.0f) {
      pos.x = radius_;
      velocities_[i].x = -velocities_[i].x;
    } else if (pos.x + radius_ > window_width_) {
      pos.x = window_width_ - radius_;
      velocities_[i].x = -velocities_[i].x;
    }

    if (pos.y - radius_ < 0.0f) {
      pos.y = radius_;
      velocities_[i].y = -velocities_[i].y;
    } else if (pos.y + radius_ > window_height_) {
      pos.y = window_height_ - radius_;
      velocities_[i].y = -velocities_[i].y;
    }

    circles_[i].setPosition(pos);
  }

  time_left_ -= dt;
  if (time_left_ <= 0.0f) {
    time_left_ = 0.0f;
    game_over_ = true;
  }
  UpdateTexts();
}

void Game::Render() {
  window_.clear(sf::Color::Black);

  for (const auto& circle : circles_) {
    window_.draw(circle);
  }

  window_.draw(score_text_);
  window_.draw(time_text_);

  if (game_over_) {
    window_.draw(game_over_text_);
  }

  window_.display();
}

void Game::InitializeCircles() {
  circles_.resize(kNumCircles);
  velocities_.resize(kNumCircles);
  for (size_t i = 0; i < kNumCircles; ++i) {
    circles_[i].setRadius(radius_);
    circles_[i].setFillColor(sf::Color::Green);
    circles_[i].setOrigin(radius_, radius_);
    SpawnRandomPosition(static_cast<int>(i));
    SpawnRandomVelocity(static_cast<int>(i));
  }
}

void Game::SpawnRandomPosition(int index) {
  float x = pos_dist_x_(rng_);
  float y = pos_dist_y_(rng_);
  circles_[index].setPosition(x, y);
}

void Game::SpawnRandomVelocity(int index) {
  velocities_[index] = sf::Vector2f(vel_dist_(rng_), vel_dist_(rng_));
}

void Game::UpdateTexts() {
  score_text_.setString("Score: " + std::to_string(score_));
  time_text_.setString("Time: " +
                       std::to_string(static_cast<int>(time_left_)) + "s");
  if (game_over_) {
    game_over_text_.setString("Game Over!\nFinal Score: " +
                              std::to_string(score_) +
                              "\nClose window to exit");
  }
}

int Game::CheckCircleClick(int mouse_x, int mouse_y) const {
  sf::Vector2f mouse_point(static_cast<float>(mouse_x),
                           static_cast<float>(mouse_y));
  for (size_t i = 0; i < circles_.size(); ++i) {
    sf::Vector2f center = circles_[i].getPosition();
    float dx = mouse_point.x - center.x;
    float dy = mouse_point.y - center.y;
    if (std::hypot(dx, dy) < radius_) {
      return static_cast<int>(i);
    }
  }
  return -1;
}
