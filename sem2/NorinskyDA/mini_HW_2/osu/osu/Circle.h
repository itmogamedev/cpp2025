#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Circle {
private:
    sf::CircleShape shape;
    float radius;

public:
    Circle(float r);

    void setPosition(float x, float y);

    void draw(sf::RenderWindow& window);

    bool contains(float x, float y);
};
