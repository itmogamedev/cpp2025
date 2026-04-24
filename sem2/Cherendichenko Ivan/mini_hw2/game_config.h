#pragma once

#include <string>

namespace GameConfig {

constexpr unsigned int kWindowWidth = 1280;
constexpr unsigned int kWindowHeight = 720;
constexpr unsigned int kFrameRateLimit = 60;

constexpr int kTargetCount = 5;
constexpr float kTargetRadius = 90.f;
constexpr float kGameDuration = 30.f;
constexpr float kMissPenalty = 2.f;
constexpr float kMinSpeed = 80.f;
constexpr float kMaxSpeed = 220.f;

constexpr float kMissFlashDuration = 0.25f;
constexpr sf::Uint8 kMissFlashAlpha = 80;
constexpr sf::Uint8 kOverlayAlpha = 170;

constexpr unsigned int kFontSizeHud = 32;
constexpr unsigned int kFontSizeTitle = 56;
constexpr unsigned int kFontSizeBody = 34;
constexpr float kHudPadding = 14.f;
constexpr float kTextOutline = 2.f;
constexpr float kTitleOutline = 3.5f;
constexpr float kLowTimeWarn = 5.f;

inline const std::string kAssetsFolder = "assets/";
inline const std::string kStickerPrefix = "sticker";
inline const std::string kBackgroundFilename = "background.png";
inline const std::string kFontFilename = "font.ttf";
inline const std::string kWindowTitle = "OSU Home";

}  // namespace GameConfig
