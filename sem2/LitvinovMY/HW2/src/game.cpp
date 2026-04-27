#include "game.h"

#include <iostream>
#include <string>

const char32_t kReturnCode = 13;

const sf::String kWords[] = {
    L"допса",      L"комса",        L"отчисление", L"псж",
    L"лаба",       L"кодстайл",     L"минидз",     L"бигдомашка",
    L"сумотатами", L"визуалстудио", L"синглтон",   L"солид",
    L"статики",    L"досрок",       L"плюсы",      L"петля",
};

sf::String generateWord() {
  return kWords[rand() % (sizeof(kWords) / sizeof(*kWords))];
}

Game::Game(std::string path) {
  if (!font.openFromFile(path)) {
    std::cout << "Path is invalid. Supply a font path.";
  }
}

void Game::processInput(char32_t char_entered) {
  if (phase != kTyping) return;
  if (char_entered == kReturnCode) return;

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
  if (phase == kBegin) {
    sf::Text text(font, L"Нажмите Enter,\nчтобы начать.");
    text.setPosition({30, 30});
    text.setCharacterSize(40);
    target.draw(text);
    return;
  }

  std::wstring score_string = L"Ваш счёт: ";
  score_string += std::to_wstring(score);
  if (phase == kTyping) {
    score_string += L"\nОставшееся время: ";
    score_string += std::to_wstring(time - static_cast<int>(clock.getElapsedTime().asSeconds()));
  }
  sf::Text score_text(font, score_string);
  score_text.setPosition({80, 120});
  score_text.setCharacterSize(32);
  score_text.setStyle(sf::Text::Italic);
  target.draw(score_text);

  if (phase == kTyping) {
    sf::Text text(font, word);
    text.setPosition({30, 30});
    text.setCharacterSize(72);
    target.draw(text);
    return;
  }

  if (phase == kFinish) {
    sf::Text text(font, L"Время вышло!");
    text.setPosition({30, 30});
    text.setCharacterSize(72);
    target.draw(text);
    return;
  }
}

void Game::updateTime() {
  if (phase != kTyping) return;

  if (clock.getElapsedTime().asSeconds() > time) {
    phase = kFinish;
  }
}

void Game::startGame() {
  if (phase == kTyping) return;

  word = generateWord();
  phase = kTyping;
  time = kStartTime;
  score = 0;
  clock.restart();
}