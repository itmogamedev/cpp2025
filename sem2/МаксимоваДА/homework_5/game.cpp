#include "game.h"

#include <random>

#include "const.h"

bool Game::isWaiting() const { return is_waiting_state; }

int Game::getScore() const { return player_score; }

int Game::getMoves() const { return total_attempts; }

const std::vector<Card>& Game::getField() const { return playing_field; }

bool Game::isGameComplete() const {
  for (const auto& single_card : playing_field) {
    if (!single_card.isMatched()) return false;
  }
  return true;
}

Game::Game()
    : player_score(0),
      total_attempts(0),
      error_counter(0),
      first_card_index(-1),
      second_card_index(-1),
      is_waiting_state(false) {
  initializeField();
}

void Game::initializeField() {
  playing_field.resize(TOTAL_CARDS);
  for (int i = 0; i < TOTAL_CARDS; ++i) {
    playing_field[i].setSymbol(i / 2);
    playing_field[i].setOpened(false);
    playing_field[i].setMatched(false);
  }
  std::random_device random_device;
  std::mt19937 random_generator(random_device());
  std::shuffle(playing_field.begin(), playing_field.end(), random_generator);
}

void Game::shuffleRemaining() {
  std::vector<int> remaining_symbols;
  for (const auto& single_card : playing_field) {
    if (!single_card.isMatched()) {
      remaining_symbols.push_back(single_card.getSymbol());
    }
  }
  std::random_device random_device;
  std::mt19937 random_generator(random_device());
  std::shuffle(remaining_symbols.begin(), remaining_symbols.end(),
               random_generator);

  int symbol_index = 0;
  for (auto& single_card : playing_field) {
    if (!single_card.isMatched()) {
      single_card.setSymbol(remaining_symbols[symbol_index++]);
    }
  }
  error_counter = 0;
}

void Game::openCard(int card_id) {
  if (is_waiting_state) return;
  if (card_id < 0 || card_id >= TOTAL_CARDS) return;
  if (playing_field[card_id].isMatched()) return;
  if (playing_field[card_id].isOpened()) return;

  if (first_card_index == -1) {
    first_card_index = card_id;
    playing_field[first_card_index].setOpened(true);
  } else if (second_card_index == -1 && card_id != first_card_index) {
    second_card_index = card_id;
    playing_field[second_card_index].setOpened(true);
    is_waiting_state = true;
  }
}

void Game::processMatch() {
  if (!is_waiting_state) return;
  if (first_card_index == -1 || second_card_index == -1) return;

  Card& first_card = playing_field[first_card_index];
  Card& second_card = playing_field[second_card_index];

  if (first_card.getSymbol() == second_card.getSymbol()) {
    first_card.setMatched(true);
    second_card.setMatched(true);
    player_score++;
    error_counter = 0;
  } else {
    error_counter++;
    if (error_counter >= MAX_CONSECUTIVE_ERRORS) {
      shuffleRemaining();
    }
  }

  first_card.setOpened(false);
  second_card.setOpened(false);
  total_attempts++;
  first_card_index = -1;
  second_card_index = -1;
  is_waiting_state = false;
}