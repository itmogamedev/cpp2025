#include "game.h"

const sf::String kWords[] = {
    "допса",      "комса",        "отчисление", "псж",
    "лаба",       "кодстайл",     "минидз",     "бигдомашка",
    "сумотатами", "визуалстудио", "синглтон",   "солид",
    "статики",    "досрок",       "плюсы",      "петля",
};

sf::String generateWord() { return kWords[rand() % sizeof(kWords)]; }

void Game::processInput(char32_t char_entered) {
  if (phase != kTyping) return;

  if (char_entered == *word.begin()) {
    score++;

    word = word.substring(1);
    if (word.isEmpty()) {
      word = generateWord();
    }
  } else {
    time -= kTimePenalty;
    updateTime();
  }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  
}

void Game::updateTime() {
  if (phase != kTyping) return;

  if (clock.getElapsedTime().asSeconds() > time) {
    phase = kFinish;
  }
}

void Game::startGame() {
  if(phase == kTyping) return;

  word = generateWord();
  phase = kTyping;
  time = kStartTime;
  score = 0;
  clock.restart();
}