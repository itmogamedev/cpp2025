#include "Game.h"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

Game::Game()
    : window(sf::VideoMode({500, 500}), "Zapomni Kartochki"),
      winText(font, "YOU WIN!", 50),
      movesText(font, "", 35) {
  if (!font.openFromFile("font/Cyrulik.otf")) exit(1);

  initCards();

  winText.setFillColor(sf::Color::Green);
  winText.setPosition(sf::Vector2f(120, 180));
  movesText.setFillColor(sf::Color::White);
  movesText.setPosition(sf::Vector2f(100, 260));
}

void Game::initCards() {
  std::vector<std::string> symbols = {"A", "A", "B", "B", "C", "C", "D", "D",
                                      "E", "E", "F", "F", "G", "G", "H", "H"};

  std::shuffle(symbols.begin(), symbols.end(),
               std::default_random_engine(time(0)));

  cards.clear();

  for (int i = 0; i < 16; i++) {
    Card card;

    int row = i / 4;
    int col = i % 4;
    float x = 30 + col * 110;
    float y = 30 + row * 110;

    card.shape.setPosition(sf::Vector2f(x, y));

    card.symbol = symbols[i];

    card.text.setFont(font);
    card.text.setString(symbols[i]);
    card.text.setCharacterSize(40);
    card.text.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = card.text.getLocalBounds();

    card.text.setPosition(sf::Vector2f(x + 35 - textBounds.size.x / 2,
                                       y + 20 - textBounds.size.y / 2));

    cards.push_back(card);
  }
}

void Game::processEvents() {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (waiting) continue;

    if (auto key = event->getIf<sf::Event::MouseButtonPressed>()) {
      sf::Vector2f mousePos =
          window.mapPixelToCoords(sf::Mouse::getPosition(window));

      for (Card& card : cards) {
        if (card.contains(mousePos) && !card.revealed && !card.matched) {
          card.revealed = true;

          if (!firstCard) {
            firstCard = &card;
          } else if (!secondCard) {
            secondCard = &card;
            moves++;
            waiting = true;
          }
          break;
        }
      }
    }
  }
}

void Game::checkPair() {
  if (firstCard && secondCard) {
    render();
    sf::sleep(sf::milliseconds(700));

    if (firstCard->symbol == secondCard->symbol) {
      firstCard->matched = true;
      secondCard->matched = true;

      score++;

      mistakesInRow = 0;
    } else {
      firstCard->revealed = false;
      secondCard->revealed = false;

      mistakesInRow++;
    }

    firstCard = nullptr;
    secondCard = nullptr;

    waiting = false;
    // при двух ошибках подряд карты перемешиваютс
    if (mistakesInRow >= 2) {
      shuffleCards();

      mistakesInRow = 0;
    }

    if (score == 8) {
      gameWon = true;
      movesText.setString("Moves: " + std::to_string(moves));
    }
  }
}

void Game::shuffleCards() {
  std::vector<sf::Vector2f> positions;

  for (Card& card : cards) {
    if (!card.matched) {
      positions.push_back(card.shape.getPosition());
    }
  }

  std::shuffle(positions.begin(), positions.end(),
               std::default_random_engine(time(0)));

  int index = 0;

  for (auto& card : cards) {
    if (!card.matched) {
      card.shape.setPosition(positions[index]);

      card.text.setPosition(
          sf::Vector2f(positions[index].x + 25, positions[index].y + 15));

      index++;
    }
  }
}

void Game::update() {
  if (waiting) {
    checkPair();
  }
}

void Game::render() {
  window.clear(sf::Color(30, 30, 30));

  for (auto& card : cards) {
    card.draw(window);
  }
  if (gameWon) {
    window.draw(winText);
    window.draw(movesText);
  }
  window.display();
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    render();
  }
}
