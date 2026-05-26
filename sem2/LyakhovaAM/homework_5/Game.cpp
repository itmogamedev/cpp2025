#include "Game.h"

#include <iostream>
#include <random>
#include <set>

Game::Game() {
  font.openFromFile("arialmt.ttf");
  turns = faults = 0;
  win = false;
  clock.stop();
  opened_cards.resize(16);
  left_cards.resize(16);
  randomizeCards();
}

void Game::randomizeCards() {
  std::mt19937 rand(time(NULL));
  std::uniform_int_distribution<> seg(0, 15);
  count_opened_cards = 0;
  std::fill(opened_cards.begin(), opened_cards.end(), false);
  std::fill(left_cards.begin(), left_cards.end(), false);
  if (cards.empty()) {
    cards.resize(16);
    for (auto str : card_patterns) {
      int ind = seg(rand);
      while (left_cards[ind]) ind = seg(rand);
      cards[ind] = str;
      left_cards[ind] = true;
      ind = seg(rand);
      while (left_cards[ind]) ind = seg(rand);
      cards[ind] = str;
      left_cards[ind] = true;
    }
  } else {
    std::set<std::string> left_cards_patterns;
    for (auto str : cards) {
      if (str.size()) left_cards_patterns.insert(str);
    }
    cards.clear();
    cards.resize(16);
    for (auto str : left_cards_patterns) {
      int ind = seg(rand);
      while (left_cards[ind]) ind = seg(rand);
      cards[ind] = str;
      left_cards[ind] = true;
      ind = seg(rand);
      while (left_cards[ind]) ind = seg(rand);
      cards[ind] = str;
      left_cards[ind] = true;
    }
  }
}

void Game::turn(sf::Vector2i mouse) {
  int tile_x = mouse.x / 200, tile_y = mouse.y / 200;
  if (count_opened_cards == 2 || !left_cards[tile_x + tile_y * 4] ||
      opened_cards[tile_x + tile_y * 4])
    return;
  opened_cards[tile_x + tile_y * 4] = true;
  ++count_opened_cards;
  ++turns;
  if (count_opened_cards == 2) clock.start();
}

void Game::checkCards() {
  int count_left = 0;
  for (auto card : left_cards)
    if (card) ++count_left;
  if (!count_left) {
    win = 1;
    return;
  }
  if (faults == 3 && clock.getElapsedTime().asSeconds() > 1) {
    faults = 0;
    clock.reset();
    randomizeCards();
  }
  if (count_opened_cards < 2 || clock.getElapsedTime().asSeconds() < 2) return;
  clock.reset();
  int ind_first = -1, ind_second;
  for (int i = 0; i < cards.size(); ++i) {
    if (left_cards[i] && opened_cards[i]) {
      if (ind_first == -1)
        ind_first = i;
      else
        ind_second = i;
    }
  }
  opened_cards[ind_first] = opened_cards[ind_second] = false;
  count_opened_cards = 0;
  if (cards[ind_first] == cards[ind_second]) {
    faults = 0;
    left_cards[ind_first] = left_cards[ind_second] = false;
    cards[ind_first].clear();
    cards[ind_second].clear();
  } else {
    ++faults;
    if (faults == 3) clock.start();
  }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Text text(font);
  if (win) {
    text.setCharacterSize(52);
    text.setString("You won!\nYou made " + std::to_string(turns) + " turns");
    text.setPosition({100, 300});
    target.draw(text);
    return;
  }
  if (faults == 3) {
    text.setCharacterSize(52);
    text.setString("Randomize_cards...");
    text.setPosition({150, 300});
    target.draw(text);
    return;
  }
  sf::RectangleShape rectangle;
  rectangle.setSize({200, 200});
  rectangle.setFillColor({120, 215, 185, 255});
  rectangle.setOutlineThickness(5);
  rectangle.setOutlineColor(sf::Color::Black);
  text.setCharacterSize(52);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (opened_cards[i + j * 4])
        rectangle.setFillColor({105, 145, 220, 255});
      else {
        if (left_cards[i + j * 4])
          rectangle.setFillColor({120, 200, 175, 255});
        else
          rectangle.setFillColor(sf::Color::Black);
      }
      rectangle.setPosition(
          {static_cast<float>(i) * 200, static_cast<float>(j) * 200});
      target.draw(rectangle);
      if (opened_cards[i + j * 4]) {
        text.setPosition(
            {static_cast<float>(i) * 200 + 180 / cards[i + j * 4].size(),
             static_cast<float>(j) * 200 + 50});
        text.setString(cards[i + j * 4]);
        target.draw(text);
      }
    }
  }
}
