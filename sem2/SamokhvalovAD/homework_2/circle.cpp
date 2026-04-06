#include "main.h"
#include "circle.h"


Circle::Circle() {
    radius = RANDOM_FLOAT(CIRCLE_RADIUS_MIN, CIRCLE_RADIUS_MAX);
    x = RANDOM_NUMBER(0, WINDOW_WIDTH - ((int)radius * 2));
    y = RANDOM_NUMBER(0, WINDOW_HEIGHT - ((int)radius * 2));
    speed = RANDOM_FLOAT(CIRCLE_SPEED_MIN, CIRCLE_SPEED_MAX);
    velocity = sf::Vector2f(RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1));
    color = sf::Color(MAX_COLOR_VALUE - MAX_COLOR_VALUE / CIRCLE_RADIUS_MIN * radius, MAX_COLOR_VALUE / CIRCLE_RADIUS_MIN * radius, 0);
    circle = sf::CircleShape(radius);
    circle.setPosition(sf::Vector2f(x, y));
    circle.setFillColor(color);
}


bool Circle::checksCollision(int mouseX, int mouseY) {
    return circle.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY));
}


void Circle::move() {
    std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
    if (x < 0) {
        velocity.x = -velocity.x;
        x = 1;
    } if (x >= WINDOW_WIDTH - radius * 2) {
        velocity.x = -velocity.x;
        x = WINDOW_WIDTH - radius * 2 - 1;
    }
    if (y < 0) {
        velocity.y = -velocity.y;
        y = 1;
    } if (y >= WINDOW_HEIGHT - radius * 2) {
        velocity.y = -velocity.y;
        y = WINDOW_HEIGHT - radius * 2 - 1;
    }
    x += velocity.x * speed;
    y += velocity.y * speed;
    circle.move(velocity * speed);
}