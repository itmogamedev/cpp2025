#include "GameSession.h"

#include <cmath>
#include <cstdlib>
#include <string>

#include "config.h"

GameSession::GameSession()
    : mainWindow_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Click the circles!"),
    currentScore_(0),
    remainingTime_(INITIAL_TIME),
    isActive_(true) {
    uiFont_.loadFromFile("C:/Windows/Fonts/arial.ttf");

    scoreDisplay_.setFont(uiFont_);
    scoreDisplay_.setCharacterSize(UI_FONT_SIZE);
    scoreDisplay_.setPosition(10.0f, 10.0f);
    scoreDisplay_.setFillColor(sf::Color::White);
    scoreDisplay_.setString("Score: 0");

    timerDisplay_.setFont(uiFont_);
    timerDisplay_.setCharacterSize(UI_FONT_SIZE);
    timerDisplay_.setPosition(10.0f, 45.0f);
    timerDisplay_.setFillColor(sf::Color::White);
    timerDisplay_.setString("Time: 30");

    gameoverDisplay_.setFont(uiFont_);
    gameoverDisplay_.setCharacterSize(GAMEOVER_FONT_SIZE);
    gameoverDisplay_.setPosition(150.0f, 250.0f);
    gameoverDisplay_.setFillColor(sf::Color::White);

    spawnInitialBalls();
}

void GameSession::spawnInitialBalls() {
    balls_.clear();
    for (int i = 0; i < BALLS_COUNT; ++i) {
        Ball newBall(BALL_RADIUS);
        newBall.setRandomSpawn(WINDOW_WIDTH, WINDOW_HEIGHT);
        newBall.setRandomMovement(MIN_VELOCITY, MAX_VELOCITY);
        balls_.push_back(newBall);
    }
}

void GameSession::launch() {
    while (mainWindow_.isOpen()) {
        float deltaSeconds = frameClock_.restart().asSeconds();
        if (deltaSeconds > 0.033f) {
            deltaSeconds = 0.033f;
        }
        pollInput();
        advance(deltaSeconds);
        drawFrame();
    }
}

void GameSession::pollInput() {
    sf::Event event;
    while (mainWindow_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mainWindow_.close();
        }

        if (isActive_ && event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                processClick(sf::Mouse::getPosition(mainWindow_));
            }
        }
    }
}

void GameSession::processClick(sf::Vector2i mouseCoord) {
    bool hitSomething = false;

    for (auto& ball : balls_) {
        if (ball.containsPoint(mouseCoord)) {
            currentScore_ += SCORE_PER_HIT;
            ball.setRandomSpawn(WINDOW_WIDTH, WINDOW_HEIGHT);
            ball.setRandomMovement(MIN_VELOCITY, MAX_VELOCITY);
            hitSomething = true;
            break;
        }
    }

    if (!hitSomething) {
        remainingTime_ -= MISS_PENALTY;
        if (remainingTime_ < 0.0f) {
            remainingTime_ = 0.0f;
        }
    }
}

void GameSession::advance(float deltaTime) {
    if (!isActive_) {
        return;
    }

    remainingTime_ -= deltaTime;

    for (auto& ball : balls_) {
        ball.move(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    if (remainingTime_ <= 0.0f) {
        isActive_ = false;
        remainingTime_ = 0.0f;
        gameoverDisplay_.setString("Game over!\nYour score: " +
            std::to_string(currentScore_));
    }

    updateDisplayTexts();
}

void GameSession::updateDisplayTexts() {
    scoreDisplay_.setString("Score: " + std::to_string(currentScore_));
    timerDisplay_.setString("Time: " +
        std::to_string(static_cast<int>(std::floor(remainingTime_))));
}

void GameSession::drawFrame() {
    mainWindow_.clear(sf::Color(30, 30, 45));

    for (auto& ball : balls_) {
        ball.draw(mainWindow_);
    }

    mainWindow_.draw(scoreDisplay_);
    mainWindow_.draw(timerDisplay_);

    if (!isActive_) {
        mainWindow_.draw(gameoverDisplay_);
    }

    mainWindow_.display();
}