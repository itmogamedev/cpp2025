#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "CircleTarget.h"

class Game {
 private:
  const unsigned int windowWidth = 1000;
  const unsigned int windowHeight = 700;
  const int circleCount = 5;
  const float radius = 35.f;

  sf::RenderWindow window;
  sf::Font font;
  sf::Text scoreText;
  sf::Text timerText;
  sf::Text endText;

  std::vector<CircleTarget> circles;

  int score = 0;
  float timeLeft = 20.f;
  bool gameOver = false;

  sf::Clock deltaClock;

 private:
  void InitWindow();
  bool InitFont();
  void InitText();
  void InitCircles();

  void ProcessEvents();
  void HandleMouseClick(sf::Vector2f mousePos);

  void Update(float deltaTime);
  void UpdateCircles(float deltaTime);
  void UpdateText();

  void Render();

 public:
  Game();
  void Run();
};