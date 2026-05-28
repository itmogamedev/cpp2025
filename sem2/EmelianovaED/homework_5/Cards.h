#ifndef CARDS_H
#define CARDS_H
class Card {
  int symbol_card;
  bool opened_card;
  bool matched_cards;

 public:
  Card();
  int getSymbol() const;
  bool isOpened() const;
  bool isMatched() const;
  void setSymbol(int s);
  void setOpened(bool op);
  void setMatched(bool m);
};
#endif  // !CARDS_H
