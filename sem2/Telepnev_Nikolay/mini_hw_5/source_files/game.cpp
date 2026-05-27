#include "game.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <thread>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <cstdlib>
#endif

void Game::run() {
  std::cout << "Memory game\n";
  std::cout << "Find all matching pairs.\n\n";

  while (!brd_.allDone()) {
    draw();

    int r1, c1, r2, c2;
    std::cout << "Enter coordinates of the first card (row col, 1-4): ";
    if (!pick(r1, c1)) continue;

    brd_.open(r1, c1);
    draw();

    std::cout << "Enter coordinates of the second card: ";
    if (!pick(r2, c2, r1, c1)) {
      brd_.hideAll();
      std::cout << "Press Enter to continue...";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    brd_.open(r2, c2);
    draw();
    wait(1200);

    brd_.incMv();

    if (brd_.match(r1, c1, r2, c2)) {
      std::cout << "Match! +1 point.\n";
      brd_.rstErr();
    }
    else {
      std::cout << "No match.\n";
      brd_.hideAll();
      brd_.incErr();

      if (brd_.err() == 2) {
        std::cout << "Two errors in a row! Shuffling remaining cards...\n";
        brd_.shuffle();
        brd_.rstErr();
        wait(1000);
      }
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cls();
  }

  std::cout << "Congratulations! You found all pairs in " << brd_.mv() << " moves.\n";
}

void Game::draw() const {
  cls();
  std::cout << "Moves: " << brd_.mv() << "  Consecutive errors: " << brd_.err() << "\n\n";
  std::cout << "   ";
  for (int j = 0; j < Board::kSize; ++j) {
    std::cout << j + 1 << "   ";
  }
  std::cout << "\n";

  for (int i = 0; i < Board::kSize; ++i) {
    std::cout << i + 1 << " ";
    for (int j = 0; j < Board::kSize; ++j) {
      if (brd_.cellDone(i, j)) {
        std::cout << "[ ] ";
      }
      else if (brd_.isUp(i, j)) {
        std::cout << "[" << brd_.symAt(i, j) << "] ";
      }
      else {
        std::cout << "[*] ";
      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void Game::cls() const {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void Game::wait(int ms) const {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool Game::pick(int& row, int& col, int exRow, int exCol) const {
  int r, c;
  while (true) {
    if (!(std::cin >> r >> c)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Enter two numbers (row and col): ";
      continue;
    }

    if (r < 1 || r > Board::kSize || c < 1 || c > Board::kSize) {
      std::cout << "Coordinates must be between 1 and " << Board::kSize
        << ". Try again: ";
      continue;
    }

    int ri = r - 1;
    int ci = c - 1;

    if (brd_.cellDone(ri, ci)) {
      std::cout << "This card is already matched. Choose another: ";
      continue;
    }

    if (exRow != -1 && ri == exRow && ci == exCol) {
      std::cout << "You cannot pick the same card. Try again: ";
      continue;
    }

    row = ri;
    col = ci;
    return true;
  }
}