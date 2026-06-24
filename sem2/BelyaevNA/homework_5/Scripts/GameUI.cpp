#include "GameUI.h"

#include "Constants.h"

GameUI::GameUI(const sf::Font& font)
    : movesText(font, "", UI_FONT_SIZE),
      scoreText(font, "", UI_FONT_SIZE),
      chainText(font, "", CHAIN_FONT_SIZE),
      winText(font, "", WIN_FONT_SIZE) {
  movesText.setFillColor(sf::Color(COLOR_TEXT, COLOR_TEXT_G, COLOR_TEXT_B));
  movesText.setPosition({UI_X_PADDING, WINDOW_HEIGHT - UI_Y_OFFSET});

  scoreText.setFillColor(sf::Color(COLOR_GOLD_R, COLOR_GOLD_G, COLOR_GOLD_B));
  scoreText.setPosition({SCORE_X, WINDOW_HEIGHT - UI_Y_OFFSET});

  chainText.setFillColor(
      sf::Color(COLOR_CHAIN_R, COLOR_CHAIN_G, COLOR_CHAIN_B));
  chainText.setPosition({CHAIN_X, WINDOW_HEIGHT - UI_Y_OFFSET});

  winText.setFillColor(sf::Color::Green);

  winPanel.setSize({WIN_PANEL_WIDTH, WIN_PANEL_HEIGHT});
  winPanel.setPosition({(WINDOW_WIDTH - WIN_PANEL_WIDTH) / 2.0f,
                        (WINDOW_HEIGHT - WIN_PANEL_HEIGHT) / 2.0f});
  winPanel.setFillColor(sf::Color(0, 0, 0, COLOR_PANEL_A));
}

void GameUI::updateMoves(int m) {
  movesText.setString("Moves: " + std::to_string(m));
}
void GameUI::updateScore(int s) {
  scoreText.setString("Score: " + std::to_string(s));
}
void GameUI::updateChain(int m, bool a) {
  chainText.setString(a && m > 1 ? "x" + std::to_string(m) + " CHAIN!" : "");
}
void GameUI::showWinScreen(int m, int s) {
  winText.setString("YOU WIN!\nMoves: " + std::to_string(m) +
                    "\nScore: " + std::to_string(s));
  sf::FloatRect textBounds = winText.getLocalBounds();
  winText.setPosition({(WINDOW_WIDTH - textBounds.size.x) / 2.0f,
                       (WINDOW_HEIGHT - textBounds.size.y) / 2.0f});
}
void GameUI::draw(sf::RenderWindow& window) const {
  window.draw(movesText);
  window.draw(scoreText);
  window.draw(chainText);
  if (!winText.getString().isEmpty()) {
    window.draw(winPanel);
    window.draw(winText);
  }
}
