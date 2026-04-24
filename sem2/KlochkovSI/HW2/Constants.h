#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <SFML/Graphics.hpp>

namespace constants {

const unsigned int kWindowWidth = 1024;
const unsigned int kWindowHeight = 768;
const int kCircleCount = 5;
const float kGameDuration = 30.f;
const float kCircleRadius = 45.f;
const float kMissPenalty = 3.f;
const unsigned int kFrameRateLimit = 60;

const float kMinCircleSpeed = 80.f;
const float kMaxCircleSpeedBonus = 120.f;

const unsigned int kHudFontSize = 32;
const unsigned int kGameOverTitleSize = 72;
const unsigned int kGameOverScoreSize = 48;
const unsigned int kGameOverHintSize = 28;

const float kHudScoreX = 10.f;
const float kHudScoreY = 10.f;
const float kHudTimerPadding = 20.f;
const float kTimerWarningThreshold = 10.f;

const float kGameOverTitleOffsetY = 60.f;
const float kGameOverScoreOffsetY = 20.f;
const float kGameOverHintOffsetY = 100.f;

const float kCircleOutlineThickness = 3.f;

const int kBgColorR = 30;
const int kBgColorG = 30;
const int kBgColorB = 40;

const int kOverlayAlpha = 180;

const sf::Color kCircleColors[kCircleCount] = {
    sf::Color(255, 80, 80),  sf::Color(80, 200, 255),  sf::Color(100, 255, 120),
    sf::Color(255, 200, 60), sf::Color(200, 100, 255),
};

}  // namespace constants

#endif  // CONSTANTS_H_
