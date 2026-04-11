#include "Ball.h"

#include <cstdlib>

static float randomRange(float low, float high) {
    return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
        (high - low);
}

Ball::Ball(float radius) {
    body_.setRadius(radius);
    body_.setFillColor(sf::Color(64, 224, 208));
    body_.setOutlineColor(sf::Color::White);
    body_.setOutlineThickness(2.0f);
}

void Ball::setRandomSpawn(int maxWidth, int maxHeight) {
    float radius = body_.getRadius();
    float diameter = radius * 2.0f;
    float x = static_cast<float>(rand() % (maxWidth - static_cast<int>(diameter)));
    float y = static_cast<float>(rand() % (maxHeight - static_cast<int>(diameter)));
    body_.setPosition(x, y);
}

void Ball::setRandomMovement(float minSpeed, float maxSpeed) {
    float vx = randomRange(minSpeed, maxSpeed);
    float vy = randomRange(minSpeed, maxSpeed);

    if (rand() % 2) vx = -vx;
    if (rand() % 2) vy = -vy;

    velocity_ = { vx, vy };
}

void Ball::move(float deltaTime, int boundaryX, int boundaryY) {
    body_.move(velocity_ * deltaTime);

    sf::Vector2f pos = body_.getPosition();
    float radius = body_.getRadius();
    float diameter = radius * 2.0f;

    if (pos.x <= 0.0f) {
        pos.x = 0.0f;
        velocity_.x = -velocity_.x;
    }
    else if (pos.x + diameter >= static_cast<float>(boundaryX)) {
        pos.x = static_cast<float>(boundaryX) - diameter;
        velocity_.x = -velocity_.x;
    }

    if (pos.y <= 0.0f) {
        pos.y = 0.0f;
        velocity_.y = -velocity_.y;
    }
    else if (pos.y + diameter >= static_cast<float>(boundaryY)) {
        pos.y = static_cast<float>(boundaryY) - diameter;
        velocity_.y = -velocity_.y;
    }

    body_.setPosition(pos);
}

void Ball::draw(sf::RenderWindow& target) {
    target.draw(body_);
}

bool Ball::containsPoint(sf::Vector2i point) {
    return body_.getGlobalBounds().contains(
        static_cast<float>(point.x),
        static_cast<float>(point.y));
}