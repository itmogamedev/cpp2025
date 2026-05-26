#include "Game.h"

#include <algorithm>
#include <random>

#include "Constants.h"

Game::Game()
    : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
             "Memory Game - Zapominashki;)"),
      firstCard(nullptr),
      secondCard(nullptr),
      moves(STARTING_MOVES),
      pairsFound(STARTING_PAIRS_FOUND),
      consecutiveMisses(STARTING_CONSECUTIVE_MISSES),
      isWaiting(false),
      gameFinished(false),
      movesText(font),
      gameOverText(font) {
  if (!font.openFromFile(FONT_PATH)) {
    throw std::runtime_error("Failed to load font");
  }

  movesText.setCharacterSize(MOVES_TEXT_CHARACTER_SIZE);
  movesText.setFillColor(MOVES_TEXT_COLOR);
  movesText.setPosition(sf::Vector2f(MOVES_TEXT_X, MOVES_TEXT_Y));

  gameOverText.setCharacterSize(GAME_OVER_TEXT_CHARACTER_SIZE);
  gameOverText.setFillColor(GAME_OVER_TEXT_COLOR);
  gameOverText.setString("");

  initializeCards();
}

void Game::initializeCards() {
  std::vector<std::string> cardSymbols;
  for (int i = 0; i < PAIRS_COUNT; ++i) {
    cardSymbols.push_back(CARD_SYMBOLS[i]);
    cardSymbols.push_back(CARD_SYMBOLS[i]);
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(cardSymbols.begin(), cardSymbols.end(), g);

  cards.clear();
  for (int i = 0; i < CARD_COUNT; ++i) {
    int row = i / GRID_SIZE;
    int col = i % GRID_SIZE;
    float x = GRID_OFFSET_X + col * (CARD_WIDTH + CARD_PADDING);
    float y = GRID_OFFSET_Y + row * (CARD_HEIGHT + CARD_PADDING);

    cards.push_back(std::make_unique<Card>(font, cardSymbols[i], x, y));
  }
}

void Game::handleMouseClick(float mouseX, float mouseY) {
  for (auto& card : cards) {
    if (card->getState() == CardState::Hidden &&
        card->contains(mouseX, mouseY)) {
      card->reveal();

      if (!firstCard) {
        firstCard = card.get();
      } else if (!secondCard) {
        secondCard = card.get();
        ++moves;
        isWaiting = true;
        delayClock.restart();
      }
      break;
    }
  }
}

void Game::checkMatch() {
  if (firstCard->getSymbol() == secondCard->getSymbol()) {
    firstCard->match();
    secondCard->match();
    ++pairsFound;
    consecutiveMisses = 0;

    if (pairsFound == PAIRS_COUNT) {
      gameFinished = true;
      gameOverText.setString("Victory! Moves: " + std::to_string(moves));
      sf::FloatRect textRect = gameOverText.getLocalBounds();
      gameOverText.setOrigin(
          sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                       textRect.position.y + textRect.size.y / 2.f));
      gameOverText.setPosition(
          sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
    }
  } else {
    firstCard->hide();
    secondCard->hide();
    ++consecutiveMisses;

    if (consecutiveMisses >= CONSECUTIVE_MISSES_TO_SHUFFLE) {
      shuffleRemainingCards();
      consecutiveMisses = 0;
    }
  }

  resetSelection();
}

void Game::resetSelection() {
  firstCard = nullptr;
  secondCard = nullptr;
  isWaiting = false;
}

void Game::shuffleRemainingCards() {
  std::vector<std::string> symbols;

  for (const auto& card : cards) {
    if (card->getState() != CardState::Matched) {
      symbols.push_back(card->getSymbol());
    }
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(symbols.begin(), symbols.end(), g);

  int idx = 0;
  for (auto& card : cards) {
    if (card->getState() != CardState::Matched) {
      sf::Vector2f pos = card->getPosition();
      card = std::make_unique<Card>(font, symbols[idx], pos.x, pos.y);
      ++idx;
    }
  }
}

void Game::drawUI() {
  movesText.setString("Moves: " + std::to_string(moves));
  window.draw(movesText);

  if (gameFinished) {
    window.draw(gameOverText);
  }
}

void Game::run() {
  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      if (!gameFinished && !isWaiting) {
        if (auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
          if (mouseEvent->button == sf::Mouse::Button::Left) {
            handleMouseClick(static_cast<float>(mouseEvent->position.x),
                             static_cast<float>(mouseEvent->position.y));
          }
        }
      }
    }

    if (isWaiting && delayClock.getElapsedTime().asSeconds() >= REVEAL_DELAY) {
      checkMatch();
    }

    window.clear(BACKGROUND_COLOR);

    for (auto& card : cards) {
      card->draw(window);
    }

    drawUI();
    window.display();
  }
}
