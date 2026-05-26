#include "UI.h"

#include <iostream>

#include "Constants.h"
#include "FontData.hpp"

UI::UI()
    : game_over(false),
      score_text(font),
      game_over_text(font),
      lives_text(font) {
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

  lives_text.setFont(font);
  lives_text.setCharacterSize(STATS_TEXT_SIZE);
  lives_text.setFillColor(sf::Color::White);
  lives_text.setPosition({SCORE_TEXT_POSITION.x, SCORE_TEXT_POSITION.y + 30});

  game_over_text.setFont(font);
  game_over_text.setCharacterSize(GAME_OVER_TEXT_SIZE);
  game_over_text.setFillColor(sf::Color::Red);

  updateScore(START_SCORE);
  updateLives(MAX_LIVES);
}

void UI::updateScore(int score) {
  score_text.setString("Score: " + std::to_string(score));
}

void UI::updateLives(int lives) {
  lives_text.setString("Lives: " + std::to_string(lives));
  lives_text.setPosition({SCORE_TEXT_POSITION.x, SCORE_TEXT_POSITION.y + 30});
}
void UI::setGameOver(bool over, int final_score) {
  game_over = over;
  if (over) {
    game_over_text.setString("GAME OVER!\nFinal Score: " +
                             std::to_string(final_score));
    auto bounds = game_over_text.getLocalBounds();
    float center_x = WINDOW_SIZE.x / 2.0f;
    float center_y = WINDOW_SIZE.y / 2.0f;
    game_over_text.setPosition(
        {center_x - bounds.size.x / 2, center_y - bounds.size.y / 2});
  }
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(score_text, states);
  target.draw(lives_text, states);
  if (game_over) {
    target.draw(game_over_text, states);
  }
}