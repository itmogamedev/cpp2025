#include "GameCycle.h"

#include <ctime>
#include <iostream>
#include <optional>

#include "BouncingCircleShape.h"
#include "Constants.h"
#include "Timer.h"

// ===== Shortenings
namespace SCREEN = Constants::SCREEN;
namespace TIMER = Constants::TIMER;
namespace TEXT = Constants::TEXT;
namespace TEXT_POS = Constants::TEXT::POSITIONS;
namespace NUMS = Constants::NUMS;

namespace LOOP_REQ = GameLoopRequirements;
// =====

// ===== Global variables
bool isMainScreenRunning = false;

sf::RenderWindow wn(SCREEN::videoMode, SCREEN::title, sf::State::Windowed);

Timer timer(TIMER::seconds);

std::vector<BouncingCircleShape> bouncingShapes;

int score = 0;
sf::Text scoreText(TEXT::font, TEXT::scoreWith0);
// =====

// ===== Helper functions
void LOOP_REQ::centerText(sf::Text& text, const sf::Vector2f& position) {
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(sf::Vector2f(bounds.size.x / SCREEN::centerDivider,
                              bounds.size.y / SCREEN::centerDivider));
  text.setPosition(position);
}

void LOOP_REQ::handleMouseClick(const sf::Vector2i& clickPos) {
  bool hitDetected = false;

  for (auto it = bouncingShapes.begin(); it != bouncingShapes.end();) {
    sf::FloatRect bounds = it->getGlobalBounds();
    if (bounds.contains(sf::Vector2f(clickPos.x, clickPos.y))) {
      score++;
      scoreText.setString(TEXT::score + std::to_string(score));
      it = bouncingShapes.erase(it);
      hitDetected = true;
      break;
    } else {
      ++it;
    }
  }

  for (auto& sh : bouncingShapes) {
    sh.increaseSpeedXY(NUMS::speedIncreaser);
  }

  if (!hitDetected) {
    timer -= TIMER::penalty;
  }
}

void LOOP_REQ::handleRestart() {
  isMainScreenRunning = true;
  bouncingShapes.clear();
  generateCircleShapes(bouncingShapes);
  timer = Timer(TIMER::seconds);
  score = 0;
  scoreText.setString(TEXT::scoreWith0);
  scoreText.setPosition(sf::Vector2f(wn.getSize().x - TEXT_POS::scoreTopRight.x,
                                     TEXT_POS::scoreTopRight.y));
}

void LOOP_REQ::handleGameOver() {
  timer.stop();
  wn.clear(sf::Color::Green);

  sf::Vector2u wnSize = wn.getSize();
  sf::Vector2f centerPos(wnSize.x / SCREEN::centerDivider,
                         wnSize.y / SCREEN::centerDivider);

  int32_t passedTimeMs =
      TIMER::seconds.asMilliseconds() - timer.getRemainingTimeAsMilliseconds();
  int seconds = passedTimeMs / TIMER::intPrecision;
  int hundredths = (passedTimeMs % TIMER::intPrecision) / 10;

  std::string timeStr = std::to_string(seconds);
  if (hundredths != 0) {
    timeStr += "." + std::string(hundredths < 10 ? "0" : "") +
               std::to_string(hundredths);
  }

  // Create texts
  sf::Text timeInGameText(TEXT::font, TEXT::yourTime + timeStr);
  timeInGameText.setFillColor(sf::Color::Black);

  sf::Text playAgainText(TEXT::font, TEXT::playAgain);
  playAgainText.setFillColor(sf::Color::Magenta);

  // Create temporary score text for game over screen
  sf::Text gameOverScoreText(TEXT::font, TEXT::score + std::to_string(score));
  gameOverScoreText.setFillColor(sf::Color::Black);

  // Center all texts
  centerText(timeInGameText, centerPos);
  centerText(gameOverScoreText, centerPos + TEXT_POS::scoreCenter);
  centerText(playAgainText, centerPos + TEXT_POS::playAgainCenter);

  // Draw
  wn.draw(gameOverScoreText);
  wn.draw(timeInGameText);
  wn.draw(playAgainText);
  wn.display();
}

// ===== Main game loop functions
void invokeLoop() {
  isMainScreenRunning = true;
  srand(time(nullptr));

  LOOP_REQ::generateCircleShapes(bouncingShapes);

  // Score text settings
  scoreText.setPosition(sf::Vector2f(wn.getSize().x - TEXT_POS::scoreTopRight.x,
                                     TEXT_POS::scoreTopRight.y));
  scoreText.setFillColor(sf::Color::Black);

  while (wn.isOpen()) {
    // Event handling
    while (std::optional evt = wn.pollEvent()) {
      if (evt->is<sf::Event::Closed>()) {
        wn.close();
      }

      if (const auto* mouseClick =
              evt->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseClick->button == sf::Mouse::Button::Left) {
          if (isMainScreenRunning) {
            LOOP_REQ::handleMouseClick(mouseClick->position);
          } else {
            LOOP_REQ::handleRestart();
          }
        }
      }
    }

    // Check game end conditions
    if (isMainScreenRunning && (bouncingShapes.empty() ||
                                timer.getRemainingTimeAsMilliseconds() <= 0)) {
      isMainScreenRunning = false;
    }

    // Update and draw
    if (isMainScreenRunning) {
      LOOP_REQ::update();
      LOOP_REQ::draw();
      wn.draw(scoreText);
      wn.display();
    } else {
      LOOP_REQ::handleGameOver();
    }
  }
}

// ===== Game loop requirements implementations
void LOOP_REQ::update() {
  for (BouncingCircleShape& sh : bouncingShapes) {
    sh.update(wn);
  }
}

void LOOP_REQ::draw() {
  wn.clear(sf::Color::Green);
  timer.draw(wn);

  for (BouncingCircleShape& sh : bouncingShapes) {
    sh.draw(wn);
  }
}

void LOOP_REQ::generateCircleShapes(std::vector<BouncingCircleShape>& sh) {
  for (int i = 0; i < NUMS::shapesCnt; i++) {
    int r = rand() % NUMS::modR + NUMS::minR;
    sh.push_back(BouncingCircleShape(r, NUMS::points));
  }
}
