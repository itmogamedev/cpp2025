// Circle.cpp
// Реализация класса Circle.

#include "Circle.h"

#include <cmath>
#include <random>

namespace {

    constexpr float kTwoPi = 6.28318530718f;

    std::mt19937& rng() {
        static std::mt19937 engine{ std::random_device{}() };
        return engine;
    }

    float randomFloat(float a, float b) {
        std::uniform_real_distribution<float> dist(a, b);
        return dist(rng());
    }

}  // namespace

Circle::Circle(float radius, float field_width, float field_height,
    float top_offset)
    : radius(radius),
    field_width(field_width),
    field_height(field_height),
    top_offset(top_offset),
    x(0.f),
    y(0.f),
    vx(0.f),
    vy(0.f),
    shape(radius),
    texture(nullptr) {
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color(255, 105, 180));
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color::White);
    shape.setPointCount(64);
    randomize();
}

void Circle::randomize() {
    x = randomFloat(radius, field_width - radius);
    y = randomFloat(top_offset + radius, field_height - radius);
    float angle = randomFloat(0.f, kTwoPi);
    float speed = randomFloat(120.f, 220.f);
    vx = std::cos(angle) * speed;
    vy = std::sin(angle) * speed;
}

void Circle::respawn() { randomize(); }

void Circle::setTexture(const sf::Texture* tex) {
    texture = tex;
    applyTexture();
}

void Circle::applyTexture() {
    if (texture == nullptr) {
        shape.setTexture(nullptr);
        shape.setFillColor(sf::Color(255, 105, 180));
        return;
    }
   
    shape.setFillColor(sf::Color::White);
    shape.setTexture(texture, false);
    sf::Vector2u size = texture->getSize();
    int side = static_cast<int>(std::min(size.x, size.y));
    int left = (static_cast<int>(size.x) - side) / 2;
    int top = (static_cast<int>(size.y) - side) / 2;
    shape.setTextureRect(sf::IntRect(left, top, side, side));
}

void Circle::update(float dt) {
    x += vx * dt;
    y += vy * dt;

    if (x - radius < 0.f) {
        x = radius;
        vx = -vx;
    }
    if (x + radius > field_width) {
        x = field_width - radius;
        vx = -vx;
    }
    if (y - radius < top_offset) {
        y = top_offset + radius;
        vy = -vy;
    }
    if (y + radius > field_height) {
        y = field_height - radius;
        vy = -vy;
    }

    shape.setPosition(x, y);
}

void Circle::draw(sf::RenderWindow& window) { window.draw(shape); }

bool Circle::contains(float mx, float my) const {
    float dx = mx - x;
    float dy = my - y;
    return dx * dx + dy * dy <= radius * radius;
}