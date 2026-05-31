#ifndef CARD_H
#define CARD_H

class Card {
  int card_symbol;
  bool is_open;
  bool is_matched;

 public:
  Card();
  int getSymbol() const;
  bool isOpened() const;
  bool isMatched() const;
  void setSymbol(int s);
  void setOpened(bool op);
  void setMatched(bool m);
};

#endif