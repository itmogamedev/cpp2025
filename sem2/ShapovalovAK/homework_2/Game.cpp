#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

#include "MovingCircle.h"
#include "RandomGenerator.h"

void runGame(const GameConfig& cfg) {
  sf::RenderWindow window(sf::VideoMode{sf::Vector2u{cfg.w, cfg.h}},
                          "SFML Click Circles - minimal example");
  window.setFramerateLimit(60);
  RandomGenerator randGen(static_cast<float>(cfg.w), static_cast<float>(cfg.h));

  std::vector<MovingCircle> circles;
  circles.reserve(cfg.n);

  for (int i = 0; i < cfg.n; ++i) {
    sf::Vector2f v(randGen.randomVelocity(), randGen.randomVelocity());
    float x =
        std::clamp(randGen.randomX(), cfg.r, static_cast<float>(cfg.w) - cfg.r);
    float y =
        std::clamp(randGen.randomY(), cfg.r, static_cast<float>(cfg.h) - cfg.r);
    MovingCircle c(
        x, y, v,
        sf::Vector2f(static_cast<float>(cfg.w), static_cast<float>(cfg.h)),
        cfg.r);
    circles.push_back(c);
  }
  float timeLeft = cfg.time_limit;
  const float missPenalty = cfg.miss_penalty;
  int score = 0;

  sf::Font font;
  bool haveFont = font.openFromFile("Sansation.ttf");
  std::optional<sf::Text> hud;
  if (haveFont) {
    hud.emplace(font, "", 20);
    hud->setFillColor(sf::Color::White);
    hud->setPosition(sf::Vector2f(8.f, 8.f));
  }

  sf::Clock clock;
  bool gameOver = false;

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();

      if (!gameOver && event->is<sf::Event::MouseButtonPressed>()) {
        const auto* mb = event->getIf<sf::Event::MouseButtonPressed>();
        if (mb && mb->button == sf::Mouse::Button::Left) {
          sf::Vector2i pix = mb->position;
          sf::Vector2f mp = window.mapPixelToCoords(pix);

          bool hit = false;
          for (auto& c : circles) {
            if (c.teleportIfHit(mp, randGen)) {
              ++score;
              hit = true;
              break;
            }
          }

          if (!hit) {
            timeLeft -= missPenalty;
            if (timeLeft < 0) timeLeft = 0;
          }
        }
      }
    }

    float dt = clock.restart().asSeconds();
    if (!gameOver) {
      timeLeft -= dt;
      if (timeLeft <= 0.f) {
        timeLeft = 0.f;
        gameOver = true;
      }
    }

    for (auto& c : circles) c.move(dt);

    char title[128];
    std::snprintf(title, sizeof(title), "Time: %.1fs  Score: %d", timeLeft,
                  score);
    window.setTitle(title);
    if (haveFont) {
      std::string s = "Time: ";
      s += std::to_string(static_cast<int>(timeLeft));
      s += "  Score: ";
      s += std::to_string(score);
      if (gameOver) s += "  [GAME OVER]";
      hud->setString(s);
    }

    window.clear(sf::Color(30, 30, 40));
    for (auto& c : circles) window.draw(c.getShape());
    if (haveFont) window.draw(*hud);

    if (gameOver) {
      if (haveFont) {
        sf::Text endt(font, "Time's up! Final score: " + std::to_string(score),
                      30);
        endt.setFillColor(sf::Color::Yellow);
        sf::FloatRect r = endt.getLocalBounds();
        endt.setOrigin(sf::Vector2f(r.size.x / 2.f, r.size.y / 2.f));
        endt.setPosition(sf::Vector2f(cfg.w / 2.f, cfg.h / 2.f));
        window.draw(endt);
      }
    }

    window.display();
  }
}
