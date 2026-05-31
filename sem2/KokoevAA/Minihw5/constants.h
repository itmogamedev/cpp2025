#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace constants {

constexpr unsigned int kWindowWidth = 900;
constexpr unsigned int kWindowHeight = 700;

constexpr float kPlayerSpeed = 840.0F;
constexpr float kBulletSpeed = 620.0F;
constexpr float kAsteroidBaseSpeed = 120.0F;
constexpr float kAsteroidSpeedGrowth = 20.0F;

constexpr float kPlayerRadius = 24.0F;
constexpr float kBulletRadius = 5.0F;
constexpr float kAsteroidMinRadius = 18.0F;
constexpr float kAsteroidMaxRadius = 42.0F;

constexpr int kStartLives = 3;

}  // namespace constants

#endif  // CONSTANTS_H_
