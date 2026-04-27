#include "game_manager.h"

void GameManager::initialize() {
  for (int i = 0; i < max_circles; i++) {
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Green);
    circle.setRadius(50);
    circle.setPosition(Utility::newCirclePosition());
    circles.emplace_back(circle);
  }

  timer_font.loadFromFile("fonts/165-font.ttf");
  score_font.loadFromFile("fonts/Schiffbauer-Regular.otf");

  timer_text.setFont(timer_font);
  timer_text.setScale(2, 2);
  timer_text.setPosition(SCREEN_WIDTH / 2, 20);

  score_text.setFont(score_font);
  score_text.setScale(2, 2);
  sf::FloatRect textBounds = score_text.getLocalBounds();
  score_text.setOrigin(textBounds.left + textBounds.width / 2,
                       textBounds.top + textBounds.height / 2);
  score_text.setString("SCORE: " + std::to_string(score));
  score_text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);

  enum class GameState { RUNNING, GAMEOVER };
  GameState state = GameState::RUNNING;

  hit_buffer.loadFromFile("audio/hit.wav");

  hit_sound.setBuffer(hit_buffer);
}
void GameManager::startGame() {
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                          "OSU - made at home");
  state = GameState::RUNNING;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        bool is_found = false;
        for (sf::CircleShape &circle : circles) {
          if (circle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            circle.setPosition(Utility::newCirclePosition());
            score++;
            score_text.setString("SCORE: " + std::to_string(score));
            hit_sound.play();
            is_found = true;
          }
        }
        if (!is_found) {
          time_left -= loose_points;
          int_timer -= loose_points;
          timer_text.setFillColor(sf::Color::Red);
        }
      }

      float deltaTime = gameTimer.restart().asSeconds();
      time_left -= deltaTime;
      if (time_left <= 0) {
        state = GameState::GAMEOVER;
        score_text.setPosition(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);
        break;
      }
      if (int_timer - (int)time_left >= 1) {
        int_timer--;
        timer_text.setString(std::to_string(int_timer));
        timer_text.setFillColor(sf::Color::White);
      }
    }

    window.clear();
    if (state == GameState::RUNNING) {
      for (sf::CircleShape circle : circles) window.draw(circle);
      window.draw(timer_text);
      window.draw(score_text);
    }
    if (state == GameState::GAMEOVER) {
      window.draw(score_text);
    }
    window.display();
  }
}
