#include "Game.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <random>

Game::Game() : window(sf::VideoMode({800, 700}), "Memory Game") {
  window.setFramerateLimit(60);

  if (!font.openFromFile("arial.ttf")) {
    std::cout << "Ошибка открытия шрифта\n";
  }

  initCards();
}

void Game::initCards() {
  cards.clear();

  std::vector<std::string> symbols = {"A", "A", "B", "B", "C", "C", "D", "D",
                                      "E", "E", "F", "F", "G", "G", "H", "H"};

  // реализация рандома
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(symbols.begin(), symbols.end(), gen);

  const int rows = 4;
  const int cols = 4;
  const float cardWidth = 120.f;
  const float cardHeight = 100.f;
  const float gap = 15.f;
  const float startX = 110.f;
  const float startY = 120.f;

  // настройка карт
  for (int i = 0; i < 16; i++) {
    Card card;
    card.symbol = symbols[i];
    card.isOpen = false;
    card.isMatched = false;

    card.shape.setSize({cardWidth, cardHeight});
    card.shape.setOutlineThickness(2.f);
    card.shape.setOutlineColor(sf::Color::White);

    int row = i / cols;
    int col = i % cols;

    float x = startX + col * (cardWidth + gap);
    float y = startY + row * (cardHeight + gap);

    card.shape.setPosition({x, y});

    cards.push_back(card);
  }
}

// перемещивание не открытых карт
void Game::shuffleCards() {
  std::vector<int> unmatchedIndices;
  std::vector<sf::Vector2f> positions;

  for (int i = 0; i < static_cast<int>(cards.size()); i++) {
    if (!cards[i].isMatched && !cards[i].isOpen) {
      unmatchedIndices.push_back(i);
      positions.push_back(cards[i].shape.getPosition());
    }
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(positions.begin(), positions.end(), gen);

  for (int i = 0; i < static_cast<int>(unmatchedIndices.size()); i++) {
    cards[unmatchedIndices[i]].shape.setPosition(positions[i]);
  }
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

// считывание очереди событий
void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (const auto* mousePressed =
                   event->getIf<sf::Event::MouseButtonPressed>()) {
      if (!gameFinished && !waitingToClose &&
          mousePressed->button == sf::Mouse::Button::Left) {
        handleMouseClick(mousePressed->position.x, mousePressed->position.y);
      }
    }
  }
}

// обрабатываем нажатие мышью
void Game::handleMouseClick(int mouseX, int mouseY) {
  for (int i = 0; i < static_cast<int>(cards.size()); i++) {
    if (cards[i].shape.getGlobalBounds().contains(sf::Vector2f(
            static_cast<float>(mouseX), static_cast<float>(mouseY)))) {
      if (cards[i].isMatched || cards[i].isOpen) return;

      cards[i].isOpen = true;

      if (firstOpened == -1) {
        firstOpened = i;
      } else if (secondOpened == -1 && i != firstOpened) {
        secondOpened = i;
        moves++;
        checkPair();
      }

      return;
    }
  }
}

// проверка пар
void Game::checkPair() {
  if (firstOpened == -1 || secondOpened == -1) return;

  if (cards[firstOpened].symbol == cards[secondOpened].symbol) {
    cards[firstOpened].isMatched = true;
    cards[secondOpened].isMatched = true;

    firstOpened = -1;
    secondOpened = -1;

    score++;
    wrongStreak = 0;

    if (allMatched()) {
      gameFinished = true;
    }
  } else {
    wrongStreak++;
    waitingToClose = true;
    delayClock.restart();
  }
}

// закрываем карты
void Game::closeWrongPair() {
  if (firstOpened != -1) cards[firstOpened].isOpen = false;

  if (secondOpened != -1) cards[secondOpened].isOpen = false;

  firstOpened = -1;
  secondOpened = -1;
  waitingToClose = false;

  if (wrongStreak >= 3) {
    shuffleCards();
    wrongStreak = 0;

    showShuffleMessage = true;
    shuffleMessageClock.restart();
  }
}

// обновление
void Game::update() {
  if (waitingToClose) {
    if (delayClock.getElapsedTime().asSeconds() >= 1.0f) {
      closeWrongPair();
    }
  }

  if (showShuffleMessage) {
    if (shuffleMessageClock.getElapsedTime().asSeconds() >= 2.0f) {
      showShuffleMessage = false;
    }
  }
}

// проверяем, все ли карточки открыты
bool Game::allMatched() const {
  for (const auto& card : cards) {
    if (!card.isMatched) return false;
  }

  return true;
}

// отрисовка карт
void Game::drawCard(const Card& card) {
  if (card.isMatched) return;

  sf::RectangleShape rect = card.shape;

  if (card.isOpen)
    rect.setFillColor(sf::Color(240, 230, 140));
  else
    rect.setFillColor(sf::Color(70, 130, 180));

  window.draw(rect);

  if (card.isOpen) {
    sf::Text text(font, card.symbol, 42);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                    textBounds.position.y + textBounds.size.y / 2.f});

    text.setPosition({rectBounds.position.x + rectBounds.size.x / 2.f,
                      rectBounds.position.y + rectBounds.size.y / 2.f});

    window.draw(text);
  }
}

// отрисовка интерфейса
void Game::render() {
  window.clear(sf::Color(30, 30, 30));

  for (const auto& card : cards) {
    drawCard(card);
  }

  sf::Text info(font, "", 28);
  info.setFillColor(sf::Color::White);
  info.setString("Score: " + std::to_string(score) +
                 "    Moves: " + std::to_string(moves));
  info.setPosition({40.f, 30.f});
  window.draw(info);

  if (gameFinished) {
    sf::Text winText(font, "", 36);
    winText.setFillColor(sf::Color::Green);
    winText.setString("Victory! Moves: " + std::to_string(moves));
    winText.setPosition({220.f, 620.f});
    window.draw(winText);
  }

  if (showShuffleMessage && !gameFinished) {
    sf::Text shuffleText(font, "Cards have been shaffled!", 32);
    shuffleText.setFillColor(sf::Color::Yellow);

    sf::FloatRect bounds = shuffleText.getLocalBounds();
    shuffleText.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                           bounds.position.y + bounds.size.y / 2.f});
    shuffleText.setPosition({400.f, 650.f});

    window.draw(shuffleText);
  }

  window.display();
}
