#pragma once
#ifndef BOARD_H_
#define BOARD_H_

#include "card.h"
#include <array>

class Board {
public:
  static const int kSize = 4;

  Board();

  bool allDone() const;
  bool cellDone(int r, int c) const;
  char symAt(int r, int c) const;
  bool isUp(int r, int c) const;

  bool open(int r, int c);
  void hideAll();
  bool match(int r1, int c1, int r2, int c2);
  void shuffle();

  int mv() const { return mv_; }
  void incMv() { ++mv_; }
  int err() const { return err_; }
  void incErr() { ++err_; }
  void rstErr() { err_ = 0; }

private:
  std::array<std::array<Card, kSize>, kSize> g_;
  int mv_;
  int err_;
  int left_;
};

#endif  