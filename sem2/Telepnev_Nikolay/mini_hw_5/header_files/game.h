#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "board.h"

class Game {
public:
  void run();

private:
  Board brd_;

  void draw() const;
  void cls() const;
  void wait(int ms) const;
  bool pick(int& row, int& col, int exRow = -1, int exCol = -1) const;
};

#endif  