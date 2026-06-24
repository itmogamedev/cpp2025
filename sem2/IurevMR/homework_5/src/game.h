#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>

#include <array>
#include <random>
#include <vector>

namespace constants {

inline constexpr int kGridSize = 4;
inline constexpr int kPairCount = 8;
inline constexpr int kCardCount = kGridSize * kGridSize;

inline constexpr unsigned int kWindowWidth = 540;
inline constexpr unsigned int kWindowHeight = 640;

inline constexpr float kCardSize = 96.0f;
inline constexpr float kCardGap = 14.0f;
inline constexpr float kBoardLeft = 49.0f;
inline constexpr float kBoardTop = 120.0f;
inline constexpr float kRevealDelaySeconds = 0.85f;

inline const sf::Color kBackgroundColor(18, 20, 28);
inline const sf::Color kCardBackColor(45, 88, 160);
inline const sf::Color kCardBackPatternColor(87, 132, 210);
inline const sf::Color kCardFaceColor(235, 232, 220);
inline const sf::Color kCardOutlineColor(250, 250, 250);
inline const sf::Color kHudMutedColor(75, 80, 95);
inline const sf::Color kHudActiveColor(245, 218, 105);
inline const sf::Color kErrorColor(230, 80, 80);

}  // namespace constants


namespace drawing {

float GetNumberWidth(int number, float unit);

void DrawRectangle(sf::RenderWindow& window,
                   sf::Vector2f position,
                   sf::Vector2f size,
                   sf::Color color);

void DrawNumber(sf::RenderWindow& window,
                int number,
                sf::Vector2f position,
                float unit,
                sf::Color color);

void DrawSymbol(sf::RenderWindow& window,
                int pair_id,
                sf::Vector2f card_position);

}  // namespace drawing

struct Card {
  int pair_id = 0;
  bool is_open = false;
  bool is_matched = false;
};

class MemoryGame {
 public:
  MemoryGame();

  void Run();

 private:
  enum class GameState {
    kPlaying,
    kCheckingPair,
    kWon,
  };

  void Reset();
  void HandleEvent(const sf::Event& event);
  void HandleClick(sf::Vector2f mouse_position);
  void Update();
  void Draw();

  sf::Vector2f CardPosition(int index) const;
  int CardIndexAt(sf::Vector2f position) const;

  void DrawHud();
  void DrawCardBack(int index);
  void DrawCardFace(int index);
  void DrawWinOverlay();
  void DrawTrophy(sf::Vector2f center);

  void ShuffleHiddenCards();

  sf::RenderWindow window_;
  std::array<Card, constants::kCardCount> cards_;
  std::vector<int> open_cards_;
  sf::Clock check_clock_;
  std::mt19937 random_engine_;

  GameState state_ = GameState::kPlaying;
  int moves_ = 0;
  int score_ = 0;
  int consecutive_errors_ = 0;
};

#endif  // GAME_H_
