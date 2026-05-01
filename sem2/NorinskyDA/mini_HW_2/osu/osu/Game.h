#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "UIManager.h"

struct MovingCircle {
  sf::CircleShape shape;
  sf::Vector2f velocity;
};

class Game {
 public:
  Game();
  void run();

 private:
  void initGame();
  void processEvents();
  void update(float deltaTime);
  void render();
  void handleMouseClick(const sf::Vector2i& mousePos);

  sf::RenderWindow window;
  std::vector<MovingCircle> circles;
  UIManager ui;

  // Рандом
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> disX;
  std::uniform_real_distribution<> disY;
  std::uniform_real_distribution<> disSpeed;

  int score;
  float timeLeft;
  bool gameActive;

  sf::Font font;

  sf::Clock clock;

  sf::Vector2f getRandomPosition();
  sf::Vector2f getRandomVelocity();
  void wrapAround(MovingCircle& circle);

  const float radius = 50.0f;
  const int windowWidth = 800;
  const int windowHeight = 600;
};

