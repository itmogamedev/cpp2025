#include "game.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>

Game::Game()
    : window(sf::VideoMode(kWindowWidth, kWindowHeight),
             "Memory Match - Variant 1"),
      font_ready(false),
      board({kPadding, kTopBarHeight}, {kCardSize, kCardSize}, kGap,
            std::random_device{}()),
      first_card(-1),
      second_card(-1),
      waiting_for_close(false),
      moves(0),
      matches(0),
      consecutive_errors(0),
      game_won(false) {
  window.setFramerateLimit(60);
  font_ready = loadFont();
}

bool Game::loadFont() {
  auto tryLoad = [this](const std::string& path) {
    std::ifstream probe(path);
    if (!probe.good()) {
      return false;
    }
    return font.loadFromFile(path);
  };
  if (tryLoad("arial.ttf")) {
    return true;
  }
  if (tryLoad("C:/Windows/Fonts/arial.ttf")) {
    return true;
  }
  std::cerr << "Warning: could not load font; text will not render.\n";
  return false;
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
      continue;
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left && !waiting_for_close &&
        !game_won) {
      handleClick(event.mouseButton.x, event.mouseButton.y);
    }
  }
}

void Game::handleClick(int mouse_x, int mouse_y) {
  sf::Vector2f point(static_cast<float>(mouse_x),
                     static_cast<float>(mouse_y));
  int idx = board.findCardAt(point);
  if (idx < 0) {
    return;
  }
  if (board.cardAt(idx).getState() != CardState::Hidden) {
    return;
  }
  if (idx == first_card) {
    return;
  }

  board.cardAt(idx).setState(CardState::Revealed);
  if (first_card < 0) {
    first_card = idx;
  } else {
    second_card = idx;
    ++moves;
    waiting_for_close = true;
    reveal_clock.restart();
  }
}

void Game::update() {
  if (!waiting_for_close) {
    return;
  }
  if (reveal_clock.getElapsedTime().asSeconds() >= kRevealDelaySeconds) {
    resolvePair();
  }
}

void Game::resolvePair() {
  Card& a = board.cardAt(first_card);
  Card& b = board.cardAt(second_card);
  if (a.getSymbol() == b.getSymbol()) {
    a.setState(CardState::Matched);
    b.setState(CardState::Matched);
    ++matches;
    consecutive_errors = 0;
    if (matches == Board::kPairCount) {
      game_won = true;
    }
  } else {
    a.setState(CardState::Hidden);
    b.setState(CardState::Hidden);
    ++consecutive_errors;
    if (consecutive_errors >= 2) {
      board.shuffleHidden();
      consecutive_errors = 0;
    }
  }
  first_card = -1;
  second_card = -1;
  waiting_for_close = false;
}

void Game::render() {
  window.clear(sf::Color(30, 30, 50));
  drawStatusBar();
  board.draw(window, font, font_ready);
  if (game_won) {
    drawWinBanner();
  }
  window.display();
}

void Game::drawStatusBar() {
  if (!font_ready) {
    return;
  }
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(28);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);
  text.setString("Moves: " + std::to_string(moves) +
                 "    Pairs: " + std::to_string(matches) + " / " +
                 std::to_string(Board::kPairCount));
  text.setPosition(kPadding, 30.f);
  window.draw(text);
}

void Game::drawWinBanner() {
  sf::RectangleShape overlay(
      sf::Vector2f(static_cast<float>(kWindowWidth),
                   static_cast<float>(kWindowHeight)));
  overlay.setFillColor(sf::Color(0, 0, 0, 180));
  window.draw(overlay);

  if (!font_ready) {
    return;
  }
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Bold);
  text.setString("You won!\nMoves: " + std::to_string(moves));

  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(bounds.left + bounds.width / 2.f,
                 bounds.top + bounds.height / 2.f);
  text.setPosition(static_cast<float>(kWindowWidth) / 2.f,
                   static_cast<float>(kWindowHeight) / 2.f);
  window.draw(text);
}
