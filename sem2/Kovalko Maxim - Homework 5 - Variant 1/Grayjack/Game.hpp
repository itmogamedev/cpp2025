#ifndef GRAYJACK_GAME_HPP_
#define GRAYJACK_GAME_HPP_

#include "Board.hpp"
#include "GameState.hpp"

#include <SFML/Graphics.hpp>

class Game {
 public:
  Game();
  void Run();

 private:
  // font_ объявлен раньше board_ и текстов: sf::Text хранит указатель на шрифт,
  // порядок инициализации членов класса должен это гарантировать.
  sf::RenderWindow window_;
  sf::Font         font_;
  Board            board_;
  sf::Text         hud_text_;
  sf::Text         game_over_text_;

  GameState state_         = GameState::kWaitingFirst;
  int       first_card_    = -1;
  int       second_card_   = -1;
  int       moves_         = 0;
  int       score_         = 0;
  int       consec_misses_ = 0;

  sf::Clock delay_clock_;
  static constexpr float kShowDelay = 1.0f;

  void HandleEvent(const sf::Event& event);
  void Update();
  void Render();
  void OnCardClick(sf::Vector2f pos);
};

#endif  // GRAYJACK_GAME_HPP_
