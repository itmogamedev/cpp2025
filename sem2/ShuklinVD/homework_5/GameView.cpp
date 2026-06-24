#include "GameView.h"

#include <string>

#include "constants.h"

GameView::GameView(float screen_width, float screen_height)
    : screen_width(screen_width), screen_height(screen_height) {}

void GameView::loadResources() {
  ship_texture.loadFromFile("assets/ship.png");
  asteroid_texture.loadFromFile("assets/asteroid.png");
  background_texture.loadFromFile("assets/background.png");
  font.loadFromFile("C:/Windows/Fonts/arial.ttf");

  background_sprite.setTexture(background_texture);
  sf::Vector2u bg_size = background_texture.getSize();
  if (bg_size.x > 0 && bg_size.y > 0) {
    float scale_x = screen_width / static_cast<float>(bg_size.x);
    float scale_y = screen_height / static_cast<float>(bg_size.y);
    background_sprite.setScale(scale_x, scale_y);
  }
}

void GameView::render(sf::RenderWindow& window, GameModel& model) {
  window.clear(sf::Color(BG_R, BG_G, BG_B));

  drawBackground(window);

  const std::vector<Bullet>& bullets = model.getBullets();
  for (size_t i = 0; i < bullets.size(); i++) {
    const Bullet& bullet = bullets[i];
    sf::RectangleShape rect(
        sf::Vector2f(bullet.getWidth(), bullet.getHeight()));
    rect.setPosition(bullet.getX(), bullet.getY());
    rect.setFillColor(
        sf::Color(BULLET_COLOR_R, BULLET_COLOR_G, BULLET_COLOR_B));
    window.draw(rect);
  }

  const std::vector<Asteroid>& asteroids = model.getAsteroids();
  for (size_t i = 0; i < asteroids.size(); i++) {
    Asteroid asteroid = asteroids[i];
    asteroid.setSprite(asteroid_texture);
    window.draw(asteroid.getSprite());
  }

  if (model.getState() == GameState::Playing) {
    Ship ship = model.getShip();
    ship.setSprite(ship_texture);
    window.draw(ship.getSprite());
  }

  drawHUD(window, model);

  if (model.getState() == GameState::GameOver) drawGameOver(window, model);

  window.display();
}

void GameView::drawBackground(sf::RenderWindow& window) {
  window.draw(background_sprite);
}

void GameView::drawHUD(sf::RenderWindow& window, GameModel& model) {
  sf::Text score_text;
  score_text.setFont(font);
  score_text.setString("Score: " + std::to_string(model.getScore()));
  score_text.setCharacterSize(HUD_TEXT_SIZE);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(HUD_SCORE_X, HUD_Y);
  window.draw(score_text);

  sf::Text lives_text;
  lives_text.setFont(font);
  lives_text.setString("Lives: " + std::to_string(model.getLives()));
  lives_text.setCharacterSize(HUD_TEXT_SIZE);
  lives_text.setFillColor(sf::Color::White);
  lives_text.setPosition(screen_width - HUD_LIVES_OFFSET_X, HUD_Y);
  window.draw(lives_text);
}

void GameView::drawGameOver(sf::RenderWindow& window, GameModel& model) {
  sf::RectangleShape overlay(sf::Vector2f(screen_width, screen_height));
  overlay.setFillColor(sf::Color(0, 0, 0, OVERLAY_ALPHA));
  window.draw(overlay);

  sf::Text game_over_text;
  game_over_text.setFont(font);
  game_over_text.setString("GAME OVER");
  game_over_text.setCharacterSize(GAMEOVER_TEXT_SIZE);
  game_over_text.setFillColor(
      sf::Color(GAMEOVER_COLOR_R, GAMEOVER_COLOR_G, GAMEOVER_COLOR_B));
  sf::FloatRect go_bounds = game_over_text.getLocalBounds();
  game_over_text.setOrigin(go_bounds.width / 2.f, go_bounds.height / 2.f);
  game_over_text.setPosition(screen_width / 2.f,
                             screen_height / 2.f - GAMEOVER_Y_OFFSET);
  window.draw(game_over_text);

  sf::Text final_score;
  final_score.setFont(font);
  final_score.setString("Final Score: " + std::to_string(model.getScore()));
  final_score.setCharacterSize(FINAL_SCORE_TEXT_SIZE);
  final_score.setFillColor(sf::Color::White);
  sf::FloatRect fs_bounds = final_score.getLocalBounds();
  final_score.setOrigin(fs_bounds.width / 2.f, fs_bounds.height / 2.f);
  final_score.setPosition(screen_width / 2.f,
                          screen_height / 2.f + FINAL_SCORE_Y_OFFSET);
  window.draw(final_score);
}
