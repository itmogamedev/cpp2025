#include "Game.h"

#include <iostream>
#include <string>

Game::Game()
    : window_(sf::VideoMode({800, 600}), "Definitely Not OSU"),
      score_(0),
      game_time_(sf::seconds(60.0f)),
      is_game_over_(false),
      score_text_(font_) {
  if (!font_.openFromFile("arial.ttf")) {
    std::cerr << "Error: Could not load arial.ttf!" << std::endl;
  }

  score_text_.setCharacterSize(30);
  score_text_.setFillColor(sf::Color::White);
  score_text_.setPosition({20.f, 20.f});
  score_text_.setString("Score: 0\nTime: 60");
}

void Game::Run() {
  sf::Clock clock;
  while (window_.isOpen()) {
    sf::Time delta_time = clock.restart();
    ProcessEvents();
    Update(delta_time);
    Render();
  }
}

void Game::ProcessEvents() {
  while (const std::optional event = window_.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_.close();
    }

    if (is_game_over_) continue;

    if (const auto* mouse_press =
            event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouse_press->button == sf::Mouse::Button::Left) {
        sf::Vector2f mouse_pos =
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(window_));
        bool hit = false;

        for (auto it = targets_.begin(); it != targets_.end();) {
          if (it->shape.getGlobalBounds().contains(mouse_pos)) {
            it = targets_.erase(it);
            score_ += 10;
            hit = true;
            break;
          } else {
            ++it;
          }
        }

        if (!hit) {
          game_time_ -= sf::seconds(5.0f);
        }
      }
    }
  }
}

void Game::Update(sf::Time delta_time) {
  if (is_game_over_) return;

  game_time_ -= delta_time;

  if (game_time_ <= sf::Time::Zero) {
    game_time_ = sf::Time::Zero;
    is_game_over_ = true;
    return;
  }

  while (targets_.size() < 5) {
    SpawnTarget();
  }

  float dt = delta_time.asSeconds();
  for (auto& t : targets_) {
    t.shape.move(t.velocity * dt);

    sf::Vector2f pos = t.shape.getPosition();
    float r = t.shape.getRadius();

    if (pos.x - r < 0 || pos.x + r > 800) t.velocity.x *= -1;
    if (pos.y - r < 0 || pos.y + r > 600) t.velocity.y *= -1;
  }

  score_text_.setString(
      "Score: " + std::to_string(score_) +
      "\nTime: " + std::to_string(static_cast<int>(game_time_.asSeconds())));
}

void Game::SpawnTarget() {
  Target t;
  float radius = 25.0f;
  t.shape.setRadius(radius);
  t.shape.setFillColor(sf::Color::Magenta);
  t.shape.setOrigin({radius, radius});
  t.shape.setPosition({static_cast<float>(rand() % 700 + 50),
                       static_cast<float>(rand() % 500 + 50)});

  t.velocity = {static_cast<float>((rand() % 200) - 100),
                static_cast<float>((rand() % 200) - 100)};

  targets_.push_back(t);
}

void Game::Render() {
  window_.clear(sf::Color(20, 20, 20));

  if (!is_game_over_) {
    for (const auto& t : targets_) {
      window_.draw(t.shape);
    }
    window_.draw(score_text_);
  } else {
    score_text_.setCharacterSize(50);
    score_text_.setString("GAME OVER\nFinal Score: " + std::to_string(score_));
    score_text_.setPosition({150.f, 200.f});
    window_.draw(score_text_);
  }

  window_.display();
}
