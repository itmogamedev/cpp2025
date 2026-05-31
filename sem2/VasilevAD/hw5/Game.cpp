#include "Game.h"

#include <algorithm>
#include <ctime>
#include <random>
#include <string>

Game::Game() : window(sf::VideoMode({450, 500}), "Mega Game") {
  font.openFromFile("Moderustic-Bold.ttf");
  
  total_turns = 0;
  consecutive_errors = 0;
  matches_found = 0;
  is_waiting = false;
  game_over = false;
  initCards();
}

void Game::initCards() {
  std::vector<char> symbols = {'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D',
                               'E', 'E', 'F', 'F', 'G', 'G', 'H', 'H'};
  std::shuffle(
      symbols.begin(), symbols.end(),
      std::default_random_engine(static_cast<unsigned int>(std::time(0))));

  cards.clear();
  for (int i = 0; i < 16; ++i) {
    Card card;
    card.setSymbol(symbols[i], font);
    float x = 20.0f + (i % 4) * 105.0f;
    float y = 70.0f + (i / 4) * 105.0f;
    card.setPosition(x, y);
    cards.push_back(std::move(card));
  }
}

void Game::shuffleRemaining() {
  std::vector<int> hidden_indices;
  std::vector<char> symbols;
  for (int i = 0; i < (int)cards.size(); ++i) {
    if (cards[i].getState() == CardState::Hidden) {
      hidden_indices.push_back(i);
      symbols.push_back(cards[i].getSymbol());
    }
  }
  std::shuffle(
      symbols.begin(), symbols.end(),
      std::default_random_engine(static_cast<unsigned int>(std::time(0))));
  for (size_t i = 0; i < hidden_indices.size(); ++i) {
    cards[hidden_indices[i]].setSymbol(symbols[i], font);
  }
}

void Game::handleInput() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (!is_waiting && !game_over) {
      if (const auto* mouse_event =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse_event->button == sf::Mouse::Button::Left) {
          sf::Vector2f mouse_pos =
              window.mapPixelToCoords(mouse_event->position);
          for (int i = 0; i < (int)cards.size(); ++i) {
            if (cards[i].getState() == CardState::Hidden &&
                cards[i].isClicked(mouse_pos)) {
              cards[i].setState(CardState::Opened);
              selected_indices.push_back(i);
              if (selected_indices.size() == 2) {
                is_waiting = true;
                wait_clock.restart();
                total_turns++;
              }
              break;
            }
          }
        }
      }
    }
  }
}

void Game::update() {
  if (is_waiting && wait_clock.getElapsedTime().asSeconds() > 0.8f) {
    int i1 = selected_indices[0];
    int i2 = selected_indices[1];

    if (cards[i1].getSymbol() == cards[i2].getSymbol()) {
      cards[i1].setState(CardState::Matched);
      cards[i2].setState(CardState::Matched);
      matches_found++;
      consecutive_errors = 0;
    } else {
      cards[i1].setState(CardState::Hidden);
      cards[i2].setState(CardState::Hidden);
      consecutive_errors++;
      if (consecutive_errors >= 2) {
        shuffleRemaining();
        consecutive_errors = 0;
      }
    }
    selected_indices.clear();
    is_waiting = false;

    if (matches_found == 8) game_over = true;
  }
}

void Game::render() {
  window.clear(sf::Color(30, 30, 30));

  for (auto& card : cards) {
    card.draw(window);
  }
  sf::Text ui_text(font, "", 30);
  ui_text.setFillColor(sf::Color::White);

  if (game_over) {
    ui_text.setCharacterSize(26);
    ui_text.setString("Victory! Total turns: " + std::to_string(total_turns));
    ui_text.setPosition({100.0f, 100.0f});
    window.draw(ui_text);
  } else {
    ui_text.setString("Score: " + std::to_string(matches_found) + " / 8");
    ui_text.setPosition({270.0f, 10.0f});
    window.draw(ui_text);

    ui_text.setString("Turns: " + std::to_string(total_turns));
    ui_text.setPosition({20.0f, 10.0f}); 
    window.draw(ui_text);
  }
  window.display();
}

void Game::run() {
  while (window.isOpen()) {
    handleInput();
    update();
    render();
  }
}