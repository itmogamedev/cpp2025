#include "game.h"

#include <iostream>
#include <random>

Game::Game() {
  window.create(sf::VideoMode({650, 800}), "Memory Game");

  font.openFromFile("Comic Sans MS.ttf");

  first_card = -1;
  second_card = -1;
  moves = 0;
  fails = 0;
  matched_pairs = 0;
  delayFlag = false;
  gameOver = false;
  shuffleProcces = false;

  std::vector<char> symbols = {'!', '!', '@', '@', '#', '#', '$', '$',
                               '%', '%', '^', '^', '&', '&', '*', '*'};

  std::random_device rand;
  std::mt19937 g(rand());
  std::shuffle(symbols.begin(), symbols.end(), g);

  float card_width = 150.0f;
  float card_height = 150.0f;
  float card_dist = 10.0f;

  float start_x = 10.0f;
  float start_y = 150.0f;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      float x = start_x + j * (card_width + card_dist);
      float y = start_y + i * (card_height + card_dist);
      cards.push_back(Card(x, y, card_width, card_height, symbols[i * 4 + j]));
    }
  }
}

void Game::shuffle() {
  std::vector<int> unmatced_cards;
  std::vector<char> symbols_remains;

  for (int i = 0; i < cards.size(); i++) {
    if (!cards[i].getIsMatched()) {
      unmatced_cards.push_back(i);
      symbols_remains.push_back(cards[i].getSymbol());
      cards[i].setIsOpen(false);
    }
  }

  std::random_device rand;
  std::mt19937 g(rand());
  std::shuffle(symbols_remains.begin(), symbols_remains.end(), g);

  for (int i = 0; i < unmatced_cards.size(); i++) {
    cards[unmatced_cards[i]].setSymbol(symbols_remains[i]);
  }

  first_card = -1;
  second_card = -1;
}

void Game::regInput() {
  if (delayFlag || shuffleProcces) return;

  static bool wasPressed = false;
  bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

  if (!isPressed) {
    wasPressed = false;
    return;
  }

  if (wasPressed) return;
  wasPressed = true;

  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

  for (int i = 0; i < cards.size(); i++) {
    if (cards[i].getIsMatched()) continue;

    sf::FloatRect bounds = cards[i].getGlobalBounds();

    if (bounds.contains(worldPos)) {
      if (first_card == -1) {
        first_card = i;
        cards[i].setIsOpen(true);
      } else if (second_card == -1 && i != first_card) {
        second_card = i;
        cards[i].setIsOpen(true);
        moves++;
        delayFlag = true;
        inputLock.restart();
      }
      break;
    }
  }
}

void Game::update() {
  if (delayFlag && inputLock.getElapsedTime().asSeconds() > 0.8f) {
    if (first_card != -1 && second_card != -1) {
      if (cards[first_card].getSymbol() == cards[second_card].getSymbol()) {
        cards[first_card].setIsMatched(true);
        cards[second_card].setIsMatched(true);
        matched_pairs++;

        first_card = -1;
        second_card = -1;
      } else {
        fails++;
        cards[first_card].setIsOpen(false);
        cards[second_card].setIsOpen(false);
        first_card = -1;
        second_card = -1;
      }
    }

    delayFlag = false;

    if (matched_pairs == 8) {
      gameOver = true;
    }
  }

  if (fails >= 3 && !shuffleProcces && !delayFlag && !gameOver) {
    shuffleProcces = true;
    shuffleTimer.restart();
  }

  if (shuffleProcces && shuffleTimer.getElapsedTime().asSeconds() > 2.0f) {
    shuffle();
    fails = 0;
    shuffleProcces = false;
  }
}

void Game::draw() {
  window.clear(sf::Color::Black);

  for (auto& card : cards) {
    card.draw(window);
  }

  sf::Text pairsText(font, "Pairs: " + std::to_string(matched_pairs) + "/8",
                     30);
  pairsText.setPosition({20, 20});
  pairsText.setFillColor(sf::Color::White);
  window.draw(pairsText);

  sf::Text failsText(font, "Fails: " + std::to_string(fails) + "/3", 30);
  failsText.setPosition({20, 60});
  failsText.setFillColor(sf::Color::White);
  window.draw(failsText);

  if (gameOver) {
    sf::Text gameOverText(font, "You won!\nYour moves " + std::to_string(moves),
                          50);
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setPosition(
        {400 - textRect.size.x / 2, 400 - textRect.size.y / 2});
    gameOverText.setFillColor(sf::Color::Green);
    window.draw(gameOverText);
  }

  if (shuffleProcces) {
    sf::Text shuffleText(font, "Shuffling...", 40);
    sf::FloatRect textRect = shuffleText.getLocalBounds();
    shuffleText.setPosition(
        {300 - textRect.size.x / 2, 400 - textRect.size.y / 2});
    shuffleText.setFillColor(sf::Color::Yellow);
    window.draw(shuffleText);
  }

  window.display();
}

void Game::runGame() {
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
    }

    if (!gameOver) {
      regInput();
      update();
    }

    draw();
  }
}
