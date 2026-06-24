#include "Game.h"

#include <iostream>

Game::Game()
    : window_(sf::VideoMode(800, 600), "Memory Game - Find Pairs"),
      board_(100.f, 100.f, 100.f, 100.f, 20.f),
      game_over_(false) {
  if (!font_.loadFromFile("arial.ttf")) {
    std::cerr << "Failed to load arial.ttf" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  board_.setFont(font_);

  score_text_.setFont(font_);
  score_text_.setCharacterSize(24);
  score_text_.setFillColor(sf::Color::White);
  score_text_.setPosition(20.f, 20.f);

  moves_text_.setFont(font_);
  moves_text_.setCharacterSize(24);
  moves_text_.setFillColor(sf::Color::White);
  moves_text_.setPosition(20.f, 60.f);

  game_over_text_.setFont(font_);
  game_over_text_.setCharacterSize(48);
  game_over_text_.setFillColor(sf::Color::Red);
  game_over_text_.setString("");
  sf::FloatRect rect = game_over_text_.getLocalBounds();
  game_over_text_.setPosition(400.f - rect.width / 2.f,
                              300.f - rect.height / 2.f);
}

void Game::run() {
  sf::Clock clock;
  while (window_.isOpen()) {
    float dt = clock.restart().asSeconds();
    processEvents();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window_.close();

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
      if (!game_over_) board_.handleClick(sf::Mouse::getPosition(window_));
    }

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::R) {
      board_.reset();
      game_over_ = false;
      game_over_text_.setString("");
    }
  }
}

void Game::update(float deltaTime) {
  if (!game_over_) {
    board_.update(deltaTime);
    if (board_.isFinished()) {
      game_over_ = true;
      std::string msg =
          "GAME OVER! Moves: " + std::to_string(board_.getMoves());
      game_over_text_.setString(msg);
      sf::FloatRect rect = game_over_text_.getLocalBounds();
      game_over_text_.setPosition(400.f - rect.width / 2.f,
                                  300.f - rect.height / 2.f);
    }
    updateUIText();
  }
}

void Game::render() {
  window_.clear(sf::Color(50, 50, 80));
  board_.draw(window_);
  window_.draw(score_text_);
  window_.draw(moves_text_);
  if (game_over_) window_.draw(game_over_text_);
  window_.display();
}

void Game::updateUIText() {
  score_text_.setString("Score: " + std::to_string(board_.getScore()));
  moves_text_.setString("Moves: " + std::to_string(board_.getMoves()));
}
