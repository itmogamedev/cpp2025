#include "Game.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

Game::Game()
    : window(sf::VideoMode(900, 600), "Find Pairs"),
      grid_width(4),
      grid_height(4),
      margin_x(20.f),
      margin_y(20.f),
      score(0),
      moves(0),
      consecutive_errors(0),
      state(WAITING),
      delay_duration(0.8f),
      first_index(-1),
      second_index(-1),
      waiting_for_second(false) {
  float windowW = window.getSize().x;
  float windowH = window.getSize().y;
  card_width = (windowW - margin_x * (grid_width + 1)) / grid_width;
  card_height = (windowH - margin_y * (grid_height + 1)) / grid_height;
  start_x = margin_x;
  start_y = margin_y;

  if (!font.loadFromFile("Roboto-Regular.ttf")) {
    std::cerr << "Error: cannot load Roboto-Regular.ttf" << std::endl;
  }
  init();
}

void Game::init() {
  std::vector<char> symbols;
  for (char c = 'A'; c <= 'H'; ++c) {
    symbols.push_back(c);
    symbols.push_back(c);
  }
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(symbols.begin(), symbols.end(),
               std::default_random_engine(seed));

  cards.clear();
  for (int row = 0; row < grid_height; ++row) {
    for (int col = 0; col < grid_width; ++col) {
      Card card;
      card.symbol = symbols[row * grid_width + col];
      card.state = HIDDEN;

      float x = start_x + col * (card_width + margin_x);
      float y = start_y + row * (card_height + margin_y);
      card.shape.setSize(sf::Vector2f(card_width, card_height));
      card.shape.setPosition(x, y);
      card.shape.setFillColor(sf::Color(100, 100, 150));
      card.shape.setOutlineThickness(2.f);
      card.shape.setOutlineColor(sf::Color::Black);

      card.text.setFont(font);
      card.text.setString(card.symbol);
      card.text.setCharacterSize(static_cast<unsigned>(card_height * 0.6f));
      card.text.setFillColor(sf::Color::White);

      sf::FloatRect textRect = card.text.getLocalBounds();
      card.text.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
      card.text.setPosition(x + card_width / 2.0f, y + card_height / 2.0f);

      cards.push_back(card);
    }
  }
  shuffleAllCards();
}

void Game::shuffleAllCards() {
  std::vector<char> syms;
  for (auto& c : cards) {
    if (c.state != REMOVED) syms.push_back(c.symbol);
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(syms.begin(), syms.end(), std::default_random_engine(seed));

  int idx = 0;
  for (auto& c : cards) {
    if (c.state != REMOVED) {
      c.symbol = syms[idx++];
      c.text.setString(c.symbol);

      sf::FloatRect textRect = c.text.getLocalBounds();
      c.text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
      c.state = HIDDEN;
    }
  }

  first_index = second_index = -1;
  waiting_for_second = false;
  state = WAITING;
}

void Game::shuffleRemainingCards() {
  std::vector<char> remainingSyms;
  for (auto& c : cards) {
    if (c.state != REMOVED) remainingSyms.push_back(c.symbol);
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(remainingSyms.begin(), remainingSyms.end(),
               std::default_random_engine(seed));

  size_t idx = 0;
  for (auto& c : cards) {
    if (c.state != REMOVED) {
      c.symbol = remainingSyms[idx++];
      c.text.setString(c.symbol);

      sf::FloatRect textRect = c.text.getLocalBounds();
      c.text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
      c.state = HIDDEN;
    }
  }

  first_index = second_index = -1;
  waiting_for_second = false;
  state = WAITING;
  consecutive_errors = 0;
}

void Game::run() {
  sf::Clock frameClock;
  while (window.isOpen()) {
    handleEvents();
    update(frameClock.restart().asSeconds());
    render();
  }
}

void Game::handleEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
      if (state != WAITING) continue;
      sf::Vector2f mousePos =
          window.mapPixelToCoords(sf::Mouse::getPosition(window));
      int idx = getCardIndex(mousePos);
      if (idx != -1 && cards[idx].state == HIDDEN) {
        openCard(idx);
      }
    }
  }
}

int Game::getCardIndex(const sf::Vector2f& mousePos) const {
  for (size_t i = 0; i < cards.size(); ++i) {
    if (cards[i].shape.getGlobalBounds().contains(mousePos))
      return static_cast<int>(i);
  }
  return -1;
}

void Game::openCard(int idx) {
  if (cards[idx].state != HIDDEN) return;

  if (!waiting_for_second) {
    first_index = idx;
    cards[first_index].state = REVEALED;
    waiting_for_second = true;
  } else {
    if (idx == first_index) return;
    second_index = idx;
    cards[second_index].state = REVEALED;
    waiting_for_second = false;
    moves++;
    checkMatch();
  }
}

void Game::checkMatch() {
  if (cards[first_index].symbol == cards[second_index].symbol) {
    removeMatchedPair();
    score++;
    consecutive_errors = 0;
    resetTurn();
    checkGameOver();
  } else {
    consecutive_errors++;
    state = DELAY;
    delay_clock.restart();
  }
}

void Game::removeMatchedPair() {
  cards[first_index].state = REMOVED;
  cards[second_index].state = REMOVED;
}

void Game::closeBothCards() {
  if (first_index != -1 && cards[first_index].state == REVEALED)
    cards[first_index].state = HIDDEN;
  if (second_index != -1 && cards[second_index].state == REVEALED)
    cards[second_index].state = HIDDEN;
}

void Game::resetTurn() {
  first_index = second_index = -1;
  waiting_for_second = false;
  state = WAITING;
}

void Game::update(float dt) {
  if (state == DELAY &&
      delay_clock.getElapsedTime().asSeconds() >= delay_duration) {
    closeBothCards();
    if (consecutive_errors >= 2) {
      shuffleRemainingCards();
      consecutive_errors = 0;
    }
    resetTurn();
  }
}

void Game::render() {
  window.clear(sf::Color(30, 30, 50));

  for (auto& card : cards) {
    if (card.state == REMOVED) continue;
    if (card.state == REVEALED) {
      card.shape.setFillColor(sf::Color(200, 200, 250));
      window.draw(card.shape);
      window.draw(card.text);
    } else {
      card.shape.setFillColor(sf::Color(80, 80, 120));
      window.draw(card.shape);
    }
  }

  sf::Text scoreText;
  scoreText.setFont(font);
  scoreText.setString("Pairs: " + std::to_string(score) + "/8");
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(10.f, 10.f);
  window.draw(scoreText);

  sf::Text movesText;
  movesText.setFont(font);
  movesText.setString("Moves: " + std::to_string(moves));
  movesText.setCharacterSize(24);
  movesText.setFillColor(sf::Color::White);
  movesText.setPosition(10.f, 40.f);
  window.draw(movesText);

  window.display();
}

void Game::checkGameOver() {
  if (score == 8) {
    sf::RectangleShape overlay(
        sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    sf::Text endText;
    endText.setFont(font);
    endText.setString("You win!\nTotal moves: " + std::to_string(moves) +
                      "\n\nPress ESC to exit");
    endText.setCharacterSize(36);
    endText.setFillColor(sf::Color::Yellow);
    sf::FloatRect textRect = endText.getLocalBounds();
    endText.setOrigin(textRect.left + textRect.width / 2.0f,
                      textRect.top + textRect.height / 2.0f);
    endText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    window.draw(endText);
    window.display();

    while (window.isOpen()) {
      sf::Event ev;
      while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) window.close();
        if (ev.type == sf::Event::KeyPressed &&
            ev.key.code == sf::Keyboard::Escape)
          window.close();
      }
    }
  }
}
