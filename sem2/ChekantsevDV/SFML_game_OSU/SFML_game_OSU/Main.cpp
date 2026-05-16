#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "Moving_circle.h"

const unsigned int kWindowWidth = 1920;
const unsigned int kWindowHeight = 1080;
const float kPenaltyTime = 1.0f;
const float kInitialTime = 30.0f;

int main() {
  sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight),
                          "Circle Clicker");
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
    return -1;
  }

  std::random_device rd;
  std::mt19937 rng(rd());

  std::vector<MovingCircle> circles;
  std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::Green,
                                   sf::Color::Blue, sf::Color::Yellow,
                                   sf::Color::Magenta};
  for (int i = 0; i < 5; ++i) {
    sf::Vector2f pos =
        randomPosition(rng, kCircleRadius, kWindowWidth, kWindowHeight);
    sf::Vector2f vel = randomVelocity(rng);
    circles.emplace_back(kCircleRadius, colors[i], pos, vel);
  }

  int score = 0;
  float time_left = kInitialTime;
  bool game_over = false;

  sf::Text score_text;
  score_text.setFont(font);
  score_text.setCharacterSize(24);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(10.f, 10.f);

  sf::Text timer_text;
  timer_text.setFont(font);
  timer_text.setCharacterSize(24);
  timer_text.setFillColor(sf::Color::White);
  timer_text.setPosition(kWindowWidth - 250.f, 10.f);

  sf::Text game_over_text;
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(48);
  game_over_text.setFillColor(sf::Color::Red);
  game_over_text.setString("GAME OVER\nPress R to restart");
  game_over_text.setOrigin(game_over_text.getLocalBounds().width / 2,
                           game_over_text.getLocalBounds().height / 2);
  game_over_text.setPosition(kWindowWidth / 2.f, kWindowHeight / 2.f);

  sf::Text final_score_text;
  final_score_text.setFont(font);
  final_score_text.setCharacterSize(32);
  final_score_text.setFillColor(sf::Color::White);
  final_score_text.setPosition(kWindowWidth / 2.f, kWindowHeight / 2.f + 80.f);

  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (!game_over && event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse_pos =
            window.mapPixelToCoords(sf::Mouse::getPosition(window));
        bool hit = false;

        for (auto& circle : circles) {
          if (circle.contains(mouse_pos)) {
            hit = true;
            ++score;

            circle.shape.setPosition(randomPosition(
                rng, kCircleRadius, kWindowWidth, kWindowHeight));
            circle.velocity = randomVelocity(rng);
            break;
          }
        }

        if (!hit) {
          time_left -= kPenaltyTime;
          if (time_left < 0.f) time_left = 0.f;
        }
      }

      if (game_over && event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::R) {
        score = 0;
        time_left = kInitialTime;
        game_over = false;

        for (auto& circle : circles) {
          circle.shape.setPosition(
              randomPosition(rng, kCircleRadius, kWindowWidth, kWindowHeight));
          circle.velocity = randomVelocity(rng);
        }
      }
    }

    if (!game_over) {
      time_left -= dt;
      if (time_left <= 0.f) {
        time_left = 0.f;
        game_over = true;
        final_score_text.setString("Your score: " + std::to_string(score));
        final_score_text.setOrigin(final_score_text.getLocalBounds().width / 2,
                                   0);
      }

      for (auto& circle : circles) {
        circle.update(dt, kWindowWidth, kWindowHeight);
      }
    }

    {
      std::ostringstream ss;
      ss << "Score: " << score;
      score_text.setString(ss.str());
    }
    {
      std::ostringstream ss;
      ss << "Time: " << std::fixed << std::setprecision(1) << time_left;
      timer_text.setString(ss.str());
    }

    window.clear(sf::Color::Black);

    for (const auto& circle : circles) {
      window.draw(circle.shape);
    }

    window.draw(score_text);
    window.draw(timer_text);

    if (game_over) {
      window.draw(game_over_text);
      window.draw(final_score_text);
    }

    window.display();
  }
}
