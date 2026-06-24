#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Board {
 public:
  Board(float startX, float startY, float cardWidth, float cardHeight,
        float spacing);
  void setFont(sf::Font& font);
  void handleClick(sf::Vector2i mousePos);
  void update(float deltaTime);
  void draw(sf::RenderWindow& window);
  bool isFinished() const;
  int getScore() const;
  int getMoves() const;
  void reset();

 private:
  static constexpr int SIZE = 4;
  static constexpr int PAIRS = 8;

  enum CardState { HIDDEN, REVEALED, MATCHED };

  struct Card {
    char symbol;
    CardState state;
    sf::RectangleShape shape;
    sf::Text text;
  };

  Card cards_[SIZE][SIZE];
  sf::Font* font_;
  float card_width_;
  float card_height_;
  float spacing_;
  float start_x_;
  float start_y_;

  int first_revealed_row_;
  int first_revealed_col_;
  int second_revealed_row_;
  int second_revealed_col_;
  bool waiting_for_delay_;
  sf::Clock delay_clock_;
  float delay_duration_;

  int consecutive_mistakes_;
  int score_;
  int moves_;

  void initCards();
  void shuffleRemainingCards();
  void resetRevealed();
  bool checkMatchAndUpdate();
  void hideNonMatched();
  void revealCard(int row, int col);
  bool isCardClickable(int row, int col) const;
  void updateCardAppearance(int row, int col);
  void setCardSymbolAndText(int row, int col, char symbol);
};

#endif
