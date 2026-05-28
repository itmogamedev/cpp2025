#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <vector>

class Game {
 public:
  Game();
  void Run();

 private:
  struct Card {
    sf::RectangleShape shape;
    int symbol_id;
    bool is_matched;
    bool is_revealed;
  };

  void InitializeCards();
  void ShuffleRemainingCards();
  void HandleMouseClick(const sf::Vector2i& mouse_position);
  void UpdateCardVisuals();
  void DrawGame();
  void CheckMatch();
  void ResetSelection();

  static constexpr int kGridSize = 4;
  static constexpr float kCardWidth = 100.0f;
  static constexpr float kCardHeight = 140.0f;
  static constexpr float kCardSpacing = 20.0f;
  static constexpr float kOffsetX = 100.0f;
  static constexpr float kOffsetY = 100.0f;
  static constexpr float kRevealDelay = 0.5f;
  static constexpr int kTotalPairs = 8;

  sf::RenderWindow window_;
  std::array<std::array<Card, kGridSize>, kGridSize> cards_;
  std::mt19937 rng_;

  int first_selected_row_;
  int first_selected_col_;
  int second_selected_row_;
  int second_selected_col_;
  bool waiting_for_second_;
  bool waiting_for_flip_back_;
  int consecutive_mistakes_;
  int moves_count_;
  int pairs_found_;
  bool pending_shuffle_;  // flag to shuffle after flip-back delay
  sf::Clock flip_back_clock_;

  sf::Font font_;
  sf::Text moves_text_;
  sf::Text points_text_;  // NEW: score counter
  sf::Text end_game_text_;
  bool game_over_;
};

#endif  // GAME_H_
