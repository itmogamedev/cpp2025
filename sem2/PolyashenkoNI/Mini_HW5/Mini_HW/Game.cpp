#include "Game.h"

#include <algorithm>
#include <random>

const float Game::CARD_SIZE = 100.0f;
const float Game::PADDING = 20.0f;
const float Game::DELAY_SECONDS = 1.0f;

Game::Game()
    : window(sf::VideoMode(800, 600), "Memory Game"),
      firstSelected(nullptr),
      secondSelected(nullptr),
      waitingForDelay(false),
      consecutiveErrors(0),
      turns(0),
      pairsFound(0) {
  window.setFramerateLimit(60);

  if (!font.loadFromFile("arial.ttf")) {
    // резерв
  }
  turnText.setFont(font);
  turnText.setCharacterSize(24);
  turnText.setFillColor(sf::Color::Black);
  turnText.setPosition(20, 500);

  // генерация пар символов
  std::vector<int> pairIds;
  for (int i = 0; i < 8; ++i) {
    pairIds.push_back(i);
    pairIds.push_back(i);
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(pairIds.begin(), pairIds.end(), g);

  // Добавьте эту строку:
  cards.reserve(GRID_SIZE * GRID_SIZE);  // 16

  float startX = 100.0f;
  float startY = 50.0f;
  int index = 0;
  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      float x = startX + col * (CARD_SIZE + PADDING);
      float y = startY + row * (CARD_SIZE + PADDING);
      cards.emplace_back(pairIds[index], x, y, CARD_SIZE);
      ++index;
    }
  }
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
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left && !waitingForDelay &&
        pairsFound < 8) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      float mx = static_cast<float>(mousePos.x);
      float my = static_cast<float>(mousePos.y);

      for (auto& card : cards) {
        if (card.isHidden() && card.contains(mx, my)) {
          card.reveal();
          if (firstSelected == nullptr) {
            firstSelected = &card;
          } else if (secondSelected == nullptr && &card != firstSelected) {
            secondSelected = &card;
            waitingForDelay = true;
            delayClock.restart();
            ++turns;
          }
          break;
        }
      }
    }
  }
}

void Game::update() {
  if (waitingForDelay &&
      delayClock.getElapsedTime().asSeconds() >= DELAY_SECONDS) {
    checkMatch();
    waitingForDelay = false;
    firstSelected = nullptr;
    secondSelected = nullptr;
  }

  turnText.setString("Turns: " + std::to_string(turns));
}

void Game::render() {
  window.clear(sf::Color(240, 240, 240));
  for (const auto& card : cards) {
    card.draw(window);
  }
  window.draw(turnText);

  if (pairsFound == 8) {
    sf::Text winText;
    winText.setFont(font);
    winText.setCharacterSize(30);
    winText.setFillColor(sf::Color::Green);
    winText.setString("You win! Total turns: " + std::to_string(turns));
    sf::FloatRect bounds = winText.getLocalBounds();
    winText.setPosition(400 - bounds.width / 2, 300);
    window.draw(winText);
  }

  window.display();
}

void Game::checkMatch() {
  if (firstSelected->getPairId() == secondSelected->getPairId()) {
    firstSelected->remove();
    secondSelected->remove();
    ++pairsFound;
    consecutiveErrors = 0;
  } else {
    firstSelected->hide();
    secondSelected->hide();
    ++consecutiveErrors;

    if (consecutiveErrors >= 2) {
      shuffleHiddenCards();
      consecutiveErrors = 0;
    }
  }
}

void Game::shuffleHiddenCards() {
  std::vector<Card*> hiddenCards;
  for (auto& card : cards) {
    if (card.isHidden()) {
      hiddenCards.push_back(&card);
    }
  }

  // собираем текущие позиции и перемешиваем
  std::vector<sf::Vector2f> positions;
  for (auto* card : hiddenCards) {
    positions.push_back(
        card->getPosition());  // нужен публичный геттер, добавим
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(positions.begin(), positions.end(), g);

  for (size_t i = 0; i < hiddenCards.size(); ++i) {
    hiddenCards[i]->setPosition(positions[i].x, positions[i].y);
  }
}

// Небольшое дополнение в Card.h: нужно добавить геттер для позиции
// sf::Vector2f getPosition() const; и реализацию в Card.cpp:
// sf::Vector2f Card::getPosition() const { return shape.getPosition(); }
