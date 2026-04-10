#include "Moving_circle.h"
#include <cmath>

MovingCircle::MovingCircle(float radius, sf::Color color, sf::Vector2f pos, sf::Vector2f vel)
    : shape(radius), velocity(vel) {
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
}

void MovingCircle::update(float dt, unsigned int window_width, unsigned int window_height) {
    sf::Vector2f pos = shape.getPosition();
    pos += velocity * dt;

    float r = shape.getRadius();
    if (pos.x - r < 0) {
        pos.x = r;
        velocity.x = -velocity.x;
    }
    if (pos.x + r > window_width) {
        pos.x = window_width - r;
        velocity.x = -velocity.x;
    }
    if (pos.y - r < 0) {
        pos.y = r;
        velocity.y = -velocity.y;
    }
    if (pos.y + r > window_height) {
        pos.y = window_height - r;
        velocity.y = -velocity.y;
    }

    shape.setPosition(pos);
}

bool MovingCircle::contains(const sf::Vector2f& point) const {
    sf::Vector2f center = shape.getPosition();
    float dx = point.x - center.x;
    float dy = point.y - center.y;
    float r = shape.getRadius();
    return (dx * dx + dy * dy) <= (r * r);
}

sf::Vector2f randomVelocity(std::mt19937& rng) {
    std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * 3.14159f);
    float angle = angle_dist(rng);
    return sf::Vector2f(std::cos(angle), std::sin(angle)) * kCircleSpeed;
}

sf::Vector2f randomPosition(std::mt19937& rng, float radius,
    unsigned int window_width, unsigned int window_height) {
    std::uniform_real_distribution<float> x_dist(radius, window_width - radius);
    std::uniform_real_distribution<float> y_dist(radius, window_height - radius);
    return sf::Vector2f(x_dist(rng), y_dist(rng));
}