#include "Game.h"

#include <algorithm>
#include <chrono>
#include <random>

const int rows = 4;
const int cols = 4;
const float size = 100.f;
const float gap = 20.f;
const float offset_X = 40.f;
const float offset_Y = 100.f;
const std::string SYMBOLS[] = {"!", "@", "#", "$", "%", "^", "&", "*"};
Game::Game()
    : window(sf::VideoMode({540, 600}), "HW5_Game"),
      firstSelectedIdx(-1),
      secondSelectedIdx(-1),
      score(0),
      totalMoves(0),
      consecutiveErrors(0),
      isWaiting(false),
      statusText(font),
      symbolText(font) {
  statusText.setCharacterSize(33);
  statusText.setFillColor(sf::Color::White);
  statusText.setPosition({50.f, 30.f});
  if (!font.openFromFile("jokerman.ttf")) {
    window.setTitle("ERROR: jokerman.ttf not found!");
  }
  symbolText.setCharacterSize(50);
  symbolText.setFillColor(sf::Color::Black);
  initCards();
  updateText();
}
void Game::initCards() {
  cards.clear();
  std::vector<int> ids;
  for (int i = 0; i < 8; ++i) {
    ids.push_back(i);
    ids.push_back(i);
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(ids.begin(), ids.end(), g);
  for (int i = 0; i < rows * cols; ++i) {
    Card card;
    card.id = ids[i];
    card.isOpened = false;
    card.isMatched = false;
    int row = i / cols;
    int col = i % cols;
    card.shape.setSize({size, size});
    float posX = offset_X + col * (size + gap);
    float posY = offset_Y + row * (size + gap);
    card.shape.setPosition({posX, posY});
    cards.push_back(card);
  }
}
void Game::shuffleRemainingCards() {
  std::vector<int> remainingIds;
  for (const auto& card : cards) {
    if (!card.isMatched) {
      remainingIds.push_back(card.id);
    }
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(remainingIds.begin(), remainingIds.end(), g);
  int idx = 0;
  for (auto& card : cards) {
    if (!card.isMatched) {
      card.id = remainingIds[idx++];
      card.isOpened = false;
    }
  }
}
void Game::handleCellClick(int index) {
  if (cards[index].isOpened || cards[index].isMatched || isWaiting) return;
  cards[index].isOpened = true;
  if (firstSelectedIdx == -1) {
    firstSelectedIdx = index;
  } else if (secondSelectedIdx == -1) {
    secondSelectedIdx = index;
    totalMoves++;
    isWaiting = true;
    delayClock.restart();
  }
}
void Game::checkMatches() {
  if (firstSelectedIdx == -1 || secondSelectedIdx == -1) return;
  if (cards[firstSelectedIdx].id == cards[secondSelectedIdx].id) {
    cards[firstSelectedIdx].isMatched = true;
    cards[secondSelectedIdx].isMatched = true;
    score++;
    consecutiveErrors = 0;
  } else {
    cards[firstSelectedIdx].isOpened = false;
    cards[secondSelectedIdx].isOpened = false;
    consecutiveErrors++;
    if (consecutiveErrors == 5) {
      shuffleRemainingCards();
      consecutiveErrors = 0;
    }
  }
  firstSelectedIdx = -1;
  secondSelectedIdx = -1;
  isWaiting = false;
  updateText();
}
void Game::updateText() {
  if (score == 8 && totalMoves == 8) {
    statusText.setString("You are cheater!!! Total moves: " +
                         std::to_string(totalMoves));
  } else if (score == 8) {
    statusText.setString("Victory! Total moves: " + std::to_string(totalMoves));
  } else {
    statusText.setString(
        "Moves: " + std::to_string(totalMoves) +
        "  |  Errors streak: " + std::to_string(consecutiveErrors));
  }
}
void Game::run() {
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto* mouseButtonEvent =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonEvent->button == sf::Mouse::Button::Left && score < 8) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          for (size_t i = 0; i < cards.size(); ++i) {
            if (cards[i].shape.getGlobalBounds().contains(
                    sf::Vector2f(mousePos))) {
              handleCellClick(static_cast<int>(i));
              break;
            }
          }
        }
      }
    }
    if (isWaiting && delayClock.getElapsedTime() >= sf::seconds(1.0f)) {
      checkMatches();
    }
    window.clear(sf::Color(90, 30, 50));
    window.draw(statusText);
    for (const auto& card : cards) {
      if (card.isMatched) continue;

      if (card.isOpened) {
        sf::RectangleShape openShape = card.shape;
        openShape.setFillColor(sf::Color::White);
        window.draw(openShape);
        symbolText.setString(SYMBOLS[card.id]);
        sf::Vector2f cardPos = card.shape.getPosition();
        symbolText.setPosition({cardPos.x + 30.f, cardPos.y + 15.f});
        window.draw(symbolText);
      } else {
        sf::RectangleShape coverShape = card.shape;
        coverShape.setFillColor(sf::Color(40, 30, 50));
        coverShape.setOutlineThickness(4.f);
        coverShape.setOutlineColor(sf::Color::White);
        window.draw(coverShape);
      }
    }
    window.display();
  }
}
