#include "rendering.h"

Rendering::Rendering()
    : mainText(font), scoreText(font), timerText(font) {
  if (!font.openFromFile("Moderustic-Bold.ttf")) {
  }

  SetupText(mainText, {600.f, 180.f}, 100);
  SetupText(scoreText, {20.f, 20.f}, 30);
  SetupText(timerText, {660.f, 20.f}, 30);
}

void Rendering::SetupText(sf::Text& text, sf::Vector2f pos, unsigned int size) {
  text.setCharacterSize(size);
  text.setPosition(pos);
  text.setFillColor(sf::Color::White);
}

void Rendering::Draw(sf::RenderWindow& window, const Typing& logic) {
  scoreText.setString("Score: " + std::to_string(logic.GetScore()));
  timerText.setString("Time: " + std::to_string(static_cast<int>(logic.GetTime())));

  if (logic.Lose()) {
    mainText.setString("You loser!");
    mainText.setPosition({160.f, 150.f});
    window.clear(sf::Color(160, 35, 25));
  } else if (logic.Win()) {
    mainText.setString("You winner!");
    mainText.setPosition({120.f, 150.f});
    window.clear(sf::Color(40, 130, 20));
  } else {
    mainText.setString(std::string(1, logic.GetCurrentTarget()));
    mainText.setPosition({380.f, 150.f});
  }

  window.draw(scoreText);
  window.draw(timerText);
  window.draw(mainText);
}