#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>

constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 600;
constexpr const char* kWindowTitle = "SpaceShoot";
constexpr int kFramerateLimit = 60;

constexpr float kPlayerWidth = 60.0f;
constexpr float kPlayerHeight = 40.0f;
constexpr float kPlayerStartX = 400.0f;
constexpr float kPlayerStartY = 550.0f;
constexpr float kPlayerMoveSpeed = 400.0f;
constexpr float kPlayerInvulDuration = 1.5f;
constexpr float kPlayerInitialCooldown = 0.5f;
constexpr sf::Color kPlayerColor = sf::Color::Yellow;

constexpr float kBulletWidth = 5.0f;
constexpr float kBulletHeight = 15.0f;
constexpr float kBulletSpeed = 400.0f;
constexpr sf::Color kBulletColor = sf::Color::Red;

constexpr float kAsteroidMinRadius = 15.0f;
constexpr float kAsteroidMaxRadius = 30.0f;
constexpr sf::Color kAsteroidColor = sf::Color(128, 128, 128);
constexpr float kAsteroidBaseSpeed = 200.0f;
constexpr float kAsteroidSpeedIncrease = 10.0f;
constexpr float kInitialSpawnInterval = 1.5f;
constexpr float kMinSpawnInterval = 0.3f;
constexpr float kSpawnIntervalDecreaseRate = 0.02f;

constexpr float kCooldownMin = 0.1f;
constexpr float kCooldownPerScore = 0.01f;

constexpr int kTextSizeScore = 24;
constexpr int kTextSizeGameOver = 48;
constexpr int kTextSizeFinalScore = 30;
constexpr sf::Color kTextColor = sf::Color::White;
constexpr sf::Color kGameOverColor = sf::Color::Red;
constexpr float kTextMargin = 10.0f;
constexpr float kScoreTextY = 10.0f;
constexpr float kLivesTextY = 40.0f;
constexpr float kGameOverTextX = 400.0f;
constexpr float kGameOverTextY = 250.0f;
constexpr float kFinalScoreTextX = 400.0f;
constexpr float kFinalScoreTextY = 320.0f;

constexpr sf::Color kBackgroundColor = sf::Color(0, 0, 0);

#endif
