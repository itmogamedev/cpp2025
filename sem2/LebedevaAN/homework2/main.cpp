#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <string>
#include <vector>

const int kCircles = 5;
const int kFramRate = 60;
const float kTimeLimit = 60.0;
const float kMissPenalty = 2.0;
const int kWindowsX = 800;
const int kWindowsY = 600;
const float kScoreX = 10.0;
const float kScoreY = 10.0;
const float kTimerX = 10.0;
const float kTimerY = 40.0;
const float kGameOverX = 150.0;
const float kGameOverY = 250.0;
const float kFinalScoreX = 150.0;
const float kFinalScoreY = 200.0;

const float kRadiusMin = 20.0;
const float kRadiusMax = 40.0;
const float kSpeedMin = 1.0;
const float kSpeedMax = 6.0;
const float kColorMin = 0.0;
const float kColorMax = 255.0;
const float kPositionMin = 0.0;

int main() {
  sf::RenderWindow window(sf::VideoMode({kWindowsX, kWindowsY}), "OSUjdau");
  window.setFramerateLimit(kFramRate);
  sf::Font font;
  if (!font.openFromFile("arial.ttf")) {
    return EXIT_FAILURE;
  }

  sf::Text scoreText(font);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({kScoreX, kScoreY});

  sf::Text timerText(font);
  timerText.setFillColor(sf::Color::White);
  timerText.setPosition({kTimerX, kTimerY});

  sf::Text gameOverText(font);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setPosition({kGameOverX, kGameOverY});
  gameOverText.setString("Game Over!\nPress R to restart or ESC to quit.");

  int score = 0;
  sf::Clock clock;
  sf::Time timeLeft = sf::seconds(kTimeLimit);
  bool gameOver = false;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> radiusDist(kRadiusMin, kRadiusMax);
  std::uniform_real_distribution<float> speedDist(kSpeedMin, kSpeedMax);
  std::uniform_real_distribution<float> colorDist(kColorMin, kColorMax);
  std::uniform_real_distribution<float> posXDist(kPositionMin, kWindowsX);
  std::uniform_real_distribution<float> posYDist(kPositionMin, kWindowsY);

  std::vector<sf::CircleShape> circles;
  std::vector<sf::Vector2f> velocities;

  for (int i = 0; i < kCircles; ++i) {
    sf::CircleShape circle(radiusDist(gen));
    circle.setFillColor(
        sf::Color(colorDist(gen), colorDist(gen), colorDist(gen)));
    circle.setPosition({posXDist(gen), posYDist(gen)});
    circles.push_back(circle);
    velocities.emplace_back(speedDist(gen), speedDist(gen));
  }

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto* mouseButton =
                     event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
          if (!gameOver) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            bool hit = false;

            for (size_t i = 0; i < circles.size(); ++i) {
              if (circles[i].getGlobalBounds().contains(
                      static_cast<sf::Vector2f>(mousePos))) {
                ++score;
                circles[i].setRadius(radiusDist(gen));
                circles[i].setFillColor(
                    sf::Color(colorDist(gen), colorDist(gen), colorDist(gen)));
                circles[i].setPosition({posXDist(gen), posYDist(gen)});
                velocities[i] = {speedDist(gen), speedDist(gen)};
                hit = true;
                break;
              }
            }

            if (!hit) {
              timeLeft -= sf::seconds(kMissPenalty);
              if (timeLeft < sf::Time::Zero) timeLeft = sf::Time::Zero;
            }
          }
        }
      }

      else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
        if (gameOver && key->code == sf::Keyboard::Key::R) {
          score = 0;
          timeLeft = sf::seconds(kTimeLimit);
          gameOver = false;
          clock.restart();
          for (size_t i = 0; i < circles.size(); ++i) {
            circles[i].setRadius(radiusDist(gen));
            circles[i].setFillColor(
                sf::Color(colorDist(gen), colorDist(gen), colorDist(gen)));
            circles[i].setPosition({posXDist(gen), posYDist(gen)});
            velocities[i] = {speedDist(gen), speedDist(gen)};
          }
        } else if (key->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }

    if (!gameOver) {
      timeLeft -= clock.restart();
      if (timeLeft <= sf::Time::Zero) {
        timeLeft = sf::Time::Zero;
        gameOver = true;
      }

      for (size_t i = 0; i < circles.size(); ++i) {
        circles[i].move(velocities[i]);

        sf::Vector2f pos = circles[i].getPosition();
        float radius = circles[i].getRadius();

        if (pos.x - radius < 0) {
          pos.x = radius;
          velocities[i].x = -velocities[i].x;
        } else if (pos.x + radius > window.getSize().x) {
          pos.x = window.getSize().x - radius;
          velocities[i].x = -velocities[i].x;
        }

        if (pos.y - radius < 0) {
          pos.y = radius;
          velocities[i].y = -velocities[i].y;
        } else if (pos.y + radius > window.getSize().y) {
          pos.y = window.getSize().y - radius;
          velocities[i].y = -velocities[i].y;
        }

        circles[i].setPosition(pos);
      }

      scoreText.setString("Score: " + std::to_string(score));
      timerText.setString(
          "Time: " + std::to_string(static_cast<int>(timeLeft.asSeconds())) +
          "s");
    }

    window.clear(sf::Color::Black);
    for (const auto& circle : circles) {
      window.draw(circle);
    }

    window.draw(scoreText);
    window.draw(timerText);

    if (gameOver) {
      sf::Text finalScoreText(font);
      finalScoreText.setFillColor(sf::Color::Yellow);
      finalScoreText.setPosition({kFinalScoreX, kFinalScoreY});
      finalScoreText.setString("Final Score: " + std::to_string(score));
      window.draw(finalScoreText);
      window.draw(gameOverText);
    }

    window.display();
  }

  return EXIT_SUCCESS;
}
