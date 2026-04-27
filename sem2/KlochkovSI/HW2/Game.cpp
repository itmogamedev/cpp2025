#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <optional>

#include "Constants.h"

Game::Game()
    : window_(
          sf::VideoMode({constants::kWindowWidth, constants::kWindowHeight}),
          "OSU Game", sf::Style::Titlebar | sf::Style::Close),
      model_(),
      view_(window_),
      controller_(model_) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  window_.setFramerateLimit(constants::kFrameRateLimit);

  bool is_font_loaded =
      view_.loadFont("arial.ttf", "C:/Windows/Fonts/arial.ttf");
  (void)is_font_loaded;
}

void Game::run() {
  while (window_.isOpen()) {
    float delta_time = clock_.restart().asSeconds();

    while (const std::optional event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window_.close();
      }
      controller_.handleEvent(*event);
    }

    if (!model_.isGameOver()) {
      model_.update(delta_time);
    }

    view_.render(model_);
  }
}
