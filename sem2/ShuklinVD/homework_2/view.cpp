#include "view.h"

#include <cmath>
#include <string>

View::View() : score_text(font), timer_text(font), final_text(font) {
  window.create(sf::VideoMode({WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW}),
                "OSU premium edition");
  font.openFromFile("C:/Windows/Fonts/arial.ttf");
  score_text.setCharacterSize(ACTION_TEXT_SIZE);
  timer_text.setCharacterSize(ACTION_TEXT_SIZE);
  final_text.setCharacterSize(FINAL_TEXT_SIZE);
  score_text.setString("score: 0");
  timer_text.setString("time: ");
  timer_text.setPosition(sf::Vector2f(WIDTH_OF_WINDOW - 100, 10));
}

void View::updateScoreText(GameModel& game) {
  score_text.setString("score: " + std::to_string(game.getScore()));
}

void View::updateTimeText(GameModel& game) {
  timer_text.setString(
      "time: " + std::to_string(static_cast<int>(std::floor(game.getTime()))));
}

void View::setFinalText(GameModel& game) {
  final_text.setString("Thank you for game!\n Your score: " +
                       std::to_string(game.getScore()));
}

void View::render(GameModel& game) {
  window.clear(sf::Color::Black);
  if (game.getIsGameRunning()) {
    for (int i = 0; i < game.getCircles().size(); i++) {
      window.draw(game.getCircles()[i].getShape());
    }
    updateTimeText(game);
    window.draw(score_text);
    window.draw(timer_text);
  } else {
    setFinalText(game);
    window.draw(final_text);
  }
  window.display();
}

bool View::isOpen() const { return window.isOpen(); }

void View::close() { window.close(); }

sf::RenderWindow& View::getWindow() { return window; }
