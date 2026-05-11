#ifndef MOVING_CIRCLE_H
#define MOVING_CIRCLE_H

#include <SFML/Graphics.hpp>
#include <random>

const float kCircleRadius = 30.0f;
const float kCircleSpeed = 200.0f;

struct MovingCircle {
  sf::CircleShape shape;
  sf::Vector2f velocity;

  MovingCircle(float radius, sf::Color color, sf::Vector2f pos,
               sf::Vector2f vel);

  void update(float dt, unsigned int window_width, unsigned int window_height);
  bool contains(const sf::Vector2f& point) const;
};

sf::Vector2f randomVelocity(std::mt19937& rng);
sf::Vector2f randomPosition(std::mt19937& rng, float radius,
                            unsigned int window_width,
                            unsigned int window_height);

#endif
