#pragma once

#include <SFML/Graphics.hpp>

struct MovingCircle {
  sf::CircleShape shape;
  sf::Vector2f velocity;
};

const int circle_count = 5;
const float circle_radius = 40.f;
const float circle_speed = 250.f;
const float init_time = 30.f;
const float miss_penalty = 1.5f;
const float hit_reward = 0.5f;


const float screen_width = 800.f;
const float screen_height = 600.f;
const int int_screen_width = static_cast<int>(screen_width);
const int int_screen_height = static_cast<int>(screen_height);


MovingCircle createCircle();

void game();
