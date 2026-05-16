#include "Game.h"

#include <algorithm>
#include <iostream>

const int kMaxTime = 60;

Game::Game() {
  font.openFromFile("Note this.ttf");
  time = kMaxTime;
  points = 0;
  randomizeKey();
}

void Game::randomizeKey() {
  current_key = rand() % ('v' - 'A' + 1) + 'A';
  if (current_key == '^') current_key = 'z';
  if (current_key == '<') current_key = 'y';
  if (current_key == '=') current_key = 'x';
  if (current_key == '>') current_key = 'w';
}

void Game::turn(char key) {
  if (!(std::max(0, time - int(clock.getElapsedTime().asSeconds())))) return;
  if (key == current_key ||
      (key >= 'A' && key <= 'Z' && current_key >= 'a' && current_key <= 'z' &&
       key == current_key - ('a' - 'A')) ||
      (current_key >= 'A' && current_key <= 'Z' && key >= 'a' && key <= 'z' &&
       current_key == key - ('a' - 'A'))) {
    ++points;
    randomizeKey();
  } else
    time = std::max(0, time - 5);
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Text text(font);
  if (!(std::max(0, time - int(clock.getElapsedTime().asSeconds())))) {
    text.setCharacterSize(70);
    text.setPosition({50, 150});
    text.setString("GAME OVER\n" + std::to_string(points) + " POINTS");
    target.draw(text);
    return;
  }
  text.setString(std::to_string(std::max(
                     0, time - int(clock.getElapsedTime().asSeconds()))) +
                 " time left");
  text.setCharacterSize(52);
  text.setFillColor(sf::Color::White);
  target.draw(text);

  text.setCharacterSize(52);
  text.setPosition({300, 0});
  text.setString(std::to_string(points) + " POINTS");
  target.draw(text);

  sf::CircleShape shape;
  shape.setRadius(100);
  shape.setFillColor(sf::Color::Cyan);
  shape.setPosition({150, 150});
  target.draw(shape);

  text.setString(current_key);
  text.setPosition({215, 190});
  text.setFillColor(sf::Color::Blue);
  text.setCharacterSize(100);
  target.draw(text);
}
