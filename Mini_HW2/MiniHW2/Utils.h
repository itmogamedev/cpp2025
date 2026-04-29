#pragma once
#include <SFML/Graphics.hpp>

float RandomFloat(float min, float max);
sf::Vector2f RandomPosition(float radius, float windowW, float windowH);
bool IsMouseInsideCircle(const sf::CircleShape& circle, sf::Vector2f mousePos);