#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include <cmath>
#include <sstream>
#include <iomanip>

MovingCircle createCircle()
{
  float border_distance = 5.f;
  int min_color = 55;
  int max_color = 255;
  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<float> posDist(circle_radius + border_distance,
                                                screen_width - circle_radius - border_distance);
  std::uniform_real_distribution<float> velDist(-1.f, 1.f);
  MovingCircle mc;
  mc.shape.setRadius(circle_radius);
  mc.shape.setFillColor(sf::Color(rand() % (max_color - min_color) + min_color,
                                  rand() % (max_color - min_color) + min_color,
                                  rand() % (max_color - min_color) + min_color));
  mc.shape.setOrigin({circle_radius, circle_radius});
  mc.shape.setPosition({posDist(gen), posDist(gen)});

  sf::Vector2f vel(velDist(gen), velDist(gen));
  float len = std::hypot(vel.x, vel.y);
  if (len > 0) vel /= len;
  mc.velocity = vel * circle_speed;
  return mc;
};

void game()
{
  std::vector<MovingCircle> circles;
  int score = 0;
  float timeLeft = init_time;
  sf::Clock gameClock;
  bool gameRunning = true;
  bool gameOver = false;

  ShowWindow(GetConsoleWindow(), SW_HIDE);
  sf::RenderWindow window(sf::VideoMode({800, 600}), "we have osu at home:");
  window.setVerticalSyncEnabled(true);

  sf::Font font;
  if (!font.openFromFile("assets/fonts/Pixel_LCD-7.ttf"))
  {
    std::cerr << "Error loading font" << std::endl;
    return;
  }
  sf::Vector2f scoreTextPos = {20,10};
  sf::Vector2f timeTextPos = {560,10};
  sf::Vector2f gameOverTextPos = {240,150};
  sf::Vector2f finalScoreTextPos = {245,210};
  sf::Vector2f restartTextPos = {220,400};

  sf::Text scoreText(font, "Score: 0", 30);
  scoreText.setPosition(scoreTextPos);
  scoreText.setFillColor(sf::Color::Green);

  sf::Text timeText(font, "Time: 30.00", 30);
  timeText.setPosition(timeTextPos);
  timeText.setFillColor(sf::Color::Green);

  sf::Text gameOverText(font, "GAME OVER", 50);
  gameOverText.setPosition(gameOverTextPos);
  gameOverText.setFillColor(sf::Color::Red);

  sf::Text finalScoreText(font, "", 40);
  finalScoreText.setPosition(finalScoreTextPos);
  finalScoreText.setFillColor(sf::Color::White);

  sf::Text restartText(font, "Press SPACE to restart \n  Press ESC to exit", 24);
  restartText.setPosition(restartTextPos);
  restartText.setFillColor(sf::Color::Yellow);

  for (int i = 0; i < circle_count; ++i)
    circles.push_back(createCircle());

  while (window.isOpen())
  {
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (gameRunning)
      {
        if (const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
          if (mousePressed->button == sf::Mouse::Button::Left)
          {
            sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x),
                                  static_cast<float>(mousePressed->position.y));
            bool hit = false;

            for (auto &circle: circles)
            {
              sf::Vector2f diff = mousePos - circle.shape.getPosition();
              if (diff.x * diff.x + diff.y * diff.y <= circle_radius * circle_radius)
              {
                hit = true;
                score++;
                scoreText.setString("Score: " + std::to_string(score));

                circle = createCircle();

                timeLeft += hit_reward;
                break;
              }
            }

            if (!hit)
            {
              timeLeft -= miss_penalty;
              if (timeLeft < 0.f) timeLeft = 0.f;
            }
          }
        }
      }
      if (gameOver)
      {
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
          if (keyPressed->code == sf::Keyboard::Key::Space)
          {
            score = 0;
            timeLeft = init_time;
            scoreText.setString("Score: 0");
            circles.clear();
            for (int i = 0; i < circle_count; ++i) circles.push_back(createCircle());
            gameRunning = true;
            gameOver = false;
            gameClock.restart();
          } else if (keyPressed->code == sf::Keyboard::Key::Escape)
          {
            window.close();
          }
        }
      }
    }
    if (gameRunning)
    {
      float dt = gameClock.restart().asSeconds();
      timeLeft -= dt;

      if (timeLeft <= 0.f)
      {
        timeLeft = 0.f;
        gameRunning = false;
        gameOver = true;
      }

      for (auto &circle: circles)
      {
        sf::Vector2f pos = circle.shape.getPosition();
        pos += circle.velocity * dt;

        if (pos.x - circle_radius <= 0.f || pos.x + circle_radius >= screen_width)
        {
          circle.velocity.x *= -1;
          pos.x = std::clamp(pos.x, circle_radius, screen_width - circle_radius);
        }
        if (pos.y - circle_radius <= 0.f || pos.y + circle_radius >= screen_height)
        {
          circle.velocity.y *= -1;
          pos.y = std::clamp(pos.y, circle_radius, screen_height - circle_radius);
        }
        circle.shape.setPosition(pos);
      }

      std::ostringstream ss;
      ss << std::fixed << std::setprecision(2) << timeLeft;
      timeText.setString("Time: " + ss.str());
    } else
    {
      gameClock.restart();
      finalScoreText.setString("Final Score\n     " + std::to_string(score));
    }

    window.clear(sf::Color::Black);

    for (const auto &circle: circles)
      window.draw(circle.shape);

    if (gameRunning)
    {
      window.draw(scoreText);
      window.draw(timeText);
    } else
    {
      window.clear();
      window.draw(gameOverText);
      window.draw(finalScoreText);
      window.draw(restartText);
    }

    window.display();
  }
}
