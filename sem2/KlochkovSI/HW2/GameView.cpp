#include "GameView.h"

#include <sstream>

#include "Constants.h"

GameView::GameView(sf::RenderWindow& window) : window_(window) {}

bool GameView::loadFont(const std::string& path,
                        const std::string& fallback_path) {
  if (font_.openFromFile(path)) return true;
  return font_.openFromFile(fallback_path);
}

void GameView::render(const GameModel& model) {
  drawBackground();
  drawCircles(model);
  drawHud(model);
  if (model.isGameOver()) {
    drawGameOver(model);
  }
  window_.display();
}

void GameView::drawBackground() {
  window_.clear(sf::Color(constants::kBgColorR, constants::kBgColorG,
                          constants::kBgColorB));
}

void GameView::drawCircles(const GameModel& model) {
  for (const auto& circle : model.getCircles()) {
    circle.draw(window_);
  }
}

void GameView::drawHud(const GameModel& model) {
  std::ostringstream score_ss;
  score_ss << "Score: " << model.getScore();
  sf::Text score_text(font_, score_ss.str(), constants::kHudFontSize);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition({constants::kHudScoreX, constants::kHudScoreY});
  window_.draw(score_text);

  std::ostringstream timer_ss;
  timer_ss << "Time: " << static_cast<int>(model.getTimeRemaining());
  sf::Text timer_text(font_, timer_ss.str(), constants::kHudFontSize);
  timer_text.setFillColor(model.getTimeRemaining() <
                                  constants::kTimerWarningThreshold
                              ? sf::Color::Red
                              : sf::Color::White);
  sf::FloatRect tr = timer_text.getLocalBounds();
  timer_text.setPosition({static_cast<float>(constants::kWindowWidth) -
                              tr.size.x - constants::kHudTimerPadding,
                          constants::kHudScoreY});
  window_.draw(timer_text);
}

void GameView::drawGameOver(const GameModel& model) {
  sf::RectangleShape overlay({static_cast<float>(constants::kWindowWidth),
                              static_cast<float>(constants::kWindowHeight)});
  overlay.setFillColor(sf::Color(0, 0, 0, constants::kOverlayAlpha));
  window_.draw(overlay);

  float center_x = static_cast<float>(constants::kWindowWidth) / 2.f;
  float center_y = static_cast<float>(constants::kWindowHeight) / 2.f;

  sf::Text title_text(font_, "Game Over!", constants::kGameOverTitleSize);
  title_text.setFillColor(sf::Color::Red);
  sf::FloatRect tb = title_text.getLocalBounds();
  title_text.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
  title_text.setPosition(
      {center_x, center_y - constants::kGameOverTitleOffsetY});
  window_.draw(title_text);

  std::ostringstream score_ss;
  score_ss << "Your score: " << model.getScore();
  sf::Text score_text(font_, score_ss.str(), constants::kGameOverScoreSize);
  score_text.setFillColor(sf::Color::Yellow);
  sf::FloatRect sb = score_text.getLocalBounds();
  score_text.setOrigin({sb.size.x / 2.f, sb.size.y / 2.f});
  score_text.setPosition(
      {center_x, center_y + constants::kGameOverScoreOffsetY});
  window_.draw(score_text);

  sf::Text hint_text(font_, "Close the window to exit",
                     constants::kGameOverHintSize);
  hint_text.setFillColor(sf::Color(200, 200, 200));
  sf::FloatRect hb = hint_text.getLocalBounds();
  hint_text.setOrigin({hb.size.x / 2.f, hb.size.y / 2.f});
  hint_text.setPosition({center_x, center_y + constants::kGameOverHintOffsetY});
  window_.draw(hint_text);
}
