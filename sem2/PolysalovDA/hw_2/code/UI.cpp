#include "UI.h"

#include <iostream>

#include "FontData.hpp"

UI::UI()
    : game_over(false),
      score_text(font),
      timer_text(font),
      game_over_text(font) {
    try {
    sf::Font loadedFont(__16847_ttf, __16847_ttf_len);
    font = std::move(loadedFont);
  } catch (const sf::Exception& e) {
    std::cerr << "Error loading font: " << e.what() << std::endl;
  }

  score_text.setFont(font);
  score_text.setCharacterSize(STATS_TEXT_SIZE);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(SCORE_TEXT_POSITION);
  score_text.setString("Score: 0");

  timer_text.setFont(font);
  timer_text.setCharacterSize(STATS_TEXT_SIZE);
  timer_text.setFillColor(sf::Color::White);
  timer_text.setPosition(TIMER_TEXT_POSITION);
  timer_text.setString("Time: 0");

  game_over_text.setFont(font);
  game_over_text.setCharacterSize(GAME_OVER_TEXT_SIZE);
  game_over_text.setFillColor(sf::Color::Red);
  game_over_text.setString("GAME OVER!");
}

void UI::updateScore(int score) {
  score_text.setString("Score: " + std::to_string(score));
}

void UI::updateTimer(float time_left) {
  timer_text.setString("Time: " + std::to_string(static_cast<int>(time_left)));
}

void UI::setGameOver(bool over, int final_score) {
  game_over = over;
  if (over) {
    game_over_text.setString("GAME OVER!\nScore: " +
                             std::to_string(final_score));
    auto bounds = game_over_text.getLocalBounds();
    sf::Vector2u window_size = WINDOW_SIZE;
    float center_x = window_size.x / 2.0f;
    float center_y = window_size.y / 2.0f;
    game_over_text.setPosition(
        {center_x - bounds.size.x / 2, center_y - bounds.size.y / 2});
  }
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(score_text, states);
  target.draw(timer_text, states);
  if (game_over) {
    target.draw(game_over_text, states);
  }
}