#include <SFML/Graphics.hpp>
#include <iostream>

#include "entity.h"
#include "randomSystem.h"

#define WINDOW_SIZE 1024
#define MAX_SIZE_RATIO 6
#define COUNT_OF_BALLS 5

Entity* checkHitCircle(std::vector<Entity>& entities, sf::Vector2i click_pos) {
  for (Entity& entity : entities) {
    sf::Vector2f scale = entity.getScale();

    float radius = scale.x * 0.5f;
    sf::Vector2f center = entity.getPosition() + sf::Vector2f(radius, radius);

    float dx = static_cast<float>(click_pos.x) - center.x;
    float dy = static_cast<float>(click_pos.y) - center.y;

    if (dx * dx + dy * dy <= radius * radius) {
      return &entity;
    }
  }
  return nullptr;
}

void mainLoop() {
  sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}),
                          "MiniHomework 2 works!");
  Randomizer random_engine = Randomizer();

  std::vector<Entity> entity_list;
  std::vector<const sf::Drawable*> draw_list;
  std::vector<sf::Vector2f> velocity_list;

  entity_list.reserve(COUNT_OF_BALLS);
  velocity_list.reserve(COUNT_OF_BALLS);

  for (int i = 0; i < COUNT_OF_BALLS; i++) {
    Entity new_entity = Entity();
    float size = random_engine.random(15, WINDOW_SIZE / MAX_SIZE_RATIO);
    new_entity.setShape(sf::CircleShape(.5f));
    new_entity.setScale(sf::Vector2(size, size));
    new_entity.setPosition(sf::Vector2f(
        random_engine.random(
            std::max(0.f, random_engine.random(0, WINDOW_SIZE) - size),
            WINDOW_SIZE - size),
        random_engine.random(0, WINDOW_SIZE - size)));
    new_entity.setColor(random_engine.randomColor());

    entity_list.push_back(std::move(new_entity));
    draw_list.push_back(&entity_list.back().getShape());

    sf::Vector2f velocity(random_engine.random(120.f, 260.f),
                          random_engine.random(120.f, 260.f));

    if (random_engine.random(0, 1) == 0) {
      velocity.x = -velocity.x;
    }

    if (random_engine.random(0, 1) == 0) {
      velocity.y = -velocity.y;
    }

    velocity_list.push_back(velocity);
  }

  unsigned int total_points = 0;

  sf::Font font("C:\\Windows\\Fonts\\arial.ttf");
  sf::Text text(font);
  text.setString("Total Points: " + std::to_string(total_points));
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  text.setPosition(sf::Vector2f(10.f, 10.f));

  sf::Text timer_text(font);
  float remaining_time = 30.f;
  timer_text.setString("Time Left: " +
                       std::to_string(static_cast<int>(remaining_time)));
  timer_text.setCharacterSize(24);
  timer_text.setFillColor(sf::Color::White);
  timer_text.setStyle(sf::Text::Bold);
  timer_text.setPosition(sf::Vector2f(10.f, 45.f));

  sf::Text game_over_text(font);
  game_over_text.setString("");
  game_over_text.setCharacterSize(48);
  game_over_text.setFillColor(sf::Color::Red);
  game_over_text.setStyle(sf::Text::Bold);
  game_over_text.setPosition(sf::Vector2f(320.f, 480.f));

  bool game_over = false;
  sf::Clock delta_clock;

  draw_list.push_back(&text);
  draw_list.push_back(&timer_text);
  draw_list.push_back(&game_over_text);

  while (window.isOpen()) {
    float delta_time = delta_clock.restart().asSeconds();

    if (!game_over) {
      remaining_time -= delta_time;
      if (remaining_time <= 0.f) {
        remaining_time = 0.f;
        game_over = true;
        game_over_text.setString("GAME OVER");
      }

      timer_text.setString("Time Left: " +
                           std::to_string(static_cast<int>(remaining_time)));

      for (std::size_t i = 0; i < entity_list.size(); i++) {
        sf::Vector2f position = entity_list[i].getPosition();
        sf::Vector2f scale = entity_list[i].getScale();

        position.x += velocity_list[i].x * delta_time;
        position.y += velocity_list[i].y * delta_time;

        if (position.x <= 0.f) {
          position.x = 0.f;
          velocity_list[i].x = -velocity_list[i].x;
        } else if (position.x >= WINDOW_SIZE - scale.x) {
          position.x = WINDOW_SIZE - scale.x;
          velocity_list[i].x = -velocity_list[i].x;
        }

        if (position.y <= 0.f) {
          position.y = 0.f;
          velocity_list[i].y = -velocity_list[i].y;
        } else if (position.y >= WINDOW_SIZE - scale.y) {
          position.y = WINDOW_SIZE - scale.y;
          velocity_list[i].y = -velocity_list[i].y;
        }

        entity_list[i].setPosition(position);
      }
    }

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto* mouse_button_pressed =
                     event->getIf<sf::Event::MouseButtonPressed>()) {
        if (!game_over &&
            mouse_button_pressed->button == sf::Mouse::Button::Left) {
          Entity* founded_entity =
              checkHitCircle(entity_list, mouse_button_pressed->position);
          if (founded_entity != nullptr) {
            total_points += 1;
            text.setString("Total Points: " + std::to_string(total_points));
            float size = random_engine.random(15, WINDOW_SIZE / MAX_SIZE_RATIO);
            founded_entity->setScale(sf::Vector2(size, size));
            founded_entity->setPosition(sf::Vector2f(
                random_engine.random(
                    std::max(0.f, random_engine.random(0, WINDOW_SIZE) -
                                      founded_entity->getScale().x),
                    WINDOW_SIZE - founded_entity->getScale().x),
                random_engine.random(
                    0, WINDOW_SIZE - founded_entity->getScale().x)));
          } else {
            remaining_time -= 2.f;
            if (remaining_time <= 0.f) {
              remaining_time = 0.f;
              game_over = true;
              game_over_text.setString("GAME OVER");
            }
            timer_text.setString(
                "Time Left: " +
                std::to_string(static_cast<int>(remaining_time)));
          }
        }
      }
    }

    window.clear();
    for (const sf::Drawable* object : draw_list) {
      window.draw(*object);
    }
    window.display();
  }
}

int main() { mainLoop(); }