#include "Constants.h"
#include "Game.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

Game::Game() : score(0), timing(TIME), gameOver(false) {
  if (!font.loadFromFile("SuperStarfish.ttf")) {
    std::exit(1);
  }
  textForScore.setFont(font);
  textForScore.setCharacterSize(FONT_SIZE);
  textForScore.setFillColor(sf::Color::Black);
  textForScore.setPosition(TEXT_POSITION_UP, TEXT_POSITION_UP);

  textForTimer.setFont(font);
  textForTimer.setCharacterSize(FONT_SIZE);
  textForTimer.setFillColor(sf::Color::Black);
  textForTimer.setPosition(TEXT_POSITION_UP, TEXT_POSITION_DOWN);

  textForGameOver.setFont(font);
  textForGameOver.setCharacterSize(FONT_SIZE);
  textForGameOver.setFillColor(sf::Color::Red);
  textForGameOver.setPosition(WINDOW_WIDTH / WINDOW_DIVIDE, WINDOW_HEIGHT / WINDOW_DIVIDE);

  objects.clear();
  for (int i = 0; i < CIRCLES_NUM; i++) {
    Object circle(CIRCLE_SIZE, randPosition());
    objects.push_back(circle);

  }
}

void Game::start() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "=-=-=-we already have OSU at home-=-=-=");

  sf::Clock clock;
  while (window.isOpen()) {
    float frame = clock.restart().asSeconds();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if ((event.type == sf::Event::MouseButtonPressed) and
          (event.mouseButton.button == sf::Mouse::Left) and (!gameOver)) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        bool success = false;
        for (Object& circle : objects) {
          if (circle.nearCursor(mousePos)) {
            score++;
            circle.setPos(randPosition());
            success = true;
            break;
          }
        }
        if (!success) {
          timing -= WRONG_ANSWER;
          if (timing <= 0) gameOver = true;
        }
      }
    }
    if (!gameOver) {
      timing -= frame;
      if (timing <= 0) {
        timing = 0;
        gameOver = true;
      }
      for (Object& circle : objects) {
        circle.updatePos(frame);
      }
    }
    window.clear(sf::Color::Blue);
    for (Object& circle : objects) {
      circle.draw(window);
    }
    textForScore.setString("SCORE: " + std::to_string(score));
    textForTimer.setString("TIME REMAINING: " + std::to_string((int)timing));
    window.draw(textForScore);
    window.draw(textForTimer);

    if (gameOver) {
      textForGameOver.setString("GAME OVER. YOUR SCORE: " +
                                std::to_string(score));
      window.draw(textForGameOver);
    }
    window.display();
  }
}

sf::Vector2f Game::randPosition() {
  float randX = std::rand() % (WINDOW_WIDTH - 2 * (int)CIRCLE_SIZE) + CIRCLE_SIZE;
  float randY = std::rand() % (WINDOW_HEIGHT - 2 * (int)CIRCLE_SIZE) + CIRCLE_SIZE;
  return sf::Vector2f(randX, randY);
}
