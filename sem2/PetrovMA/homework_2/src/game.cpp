#include "game.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <random>
#include <string>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Time.hpp"
#include "circle.h"

void Game::update(sf::RenderTarget &tgt) {
  this->dt = clock.restart().asSeconds();

  int64_t now =
      std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
          .count();

  if (font_loaded) {
    int64_t remaining_ms = end_time - now;
    if (remaining_ms < 0)
      remaining_ms = 0;
    int remaining_secs = static_cast<int>(remaining_ms / 1000);

    sf::Text score_text(font, "Score: " + std::to_string(score), 24);
    score_text.setPosition({10.f, 10.f});
    score_text.setFillColor(sf::Color::White);
    tgt.draw(score_text);

    sf::Text time_text(font, "Time: " + std::to_string(remaining_secs) + "s", 24);
    time_text.setPosition({650.f, 10.f});
    time_text.setFillColor(sf::Color::White);
    tgt.draw(time_text);
  }

  if (isGameOver()) {
    circles.clear();
    if (font_loaded) {
      sf::Text gameover_text(font, "Game Over!", 48);
      gameover_text.setPosition({250.f, 220.f});
      gameover_text.setFillColor(sf::Color::Red);
      tgt.draw(gameover_text);

      sf::Text final_score(font, "Final Score: " + std::to_string(score), 32);
      final_score.setPosition({270.f, 290.f});
      final_score.setFillColor(sf::Color::White);
      tgt.draw(final_score);
    }
    return;
  }

  auto i = 0;
  while (i < circles.size()) {
    if (circles[i].frameTick(this)) // all fine
    {
      tgt.draw(circles[i].shape);
      i++;
    } else {
      circles.erase(circles.begin() + i); // removing current circle
    }
  }

  // spawn so its 5 always
  while (circles.size() < 5) {
    float radius = 50.f;
    Circle new_circle{{static_cast<float>(rand() % 701 + 50), static_cast<float>(rand() % 501 + 50)}, radius};
    new_circle.spawn_time = now;
    std::cout << "CREATED" << std::endl;
    circles.push_back(new_circle);
  }
}
void Game::run() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Circle Click Game");

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      else if (!isGameOver() && event->is<sf::Event::MouseButtonReleased>()) {
        auto pos = sf::Mouse::getPosition(window);
        bool hit_circle = false;
        std::vector<int> circles_to_remove{};

        for (auto i = 0; i < circles.size(); ++i) {
          auto circle = &circles[i];
          if (circle->wasClicked(pos)) {
            score += 10;
            hit_circle = true;
            circles_to_remove.push_back(i);
          }
        }

        if (!hit_circle) {
          end_time -= 5 * 1000L;
        } else {
          for (auto it = circles_to_remove.rbegin(); it != circles_to_remove.rend(); ++it) {
            circles.erase(circles.begin() + *it);
          }
        }
      }
    }

    window.clear();
    update(window);
    window.display();
  }
}
