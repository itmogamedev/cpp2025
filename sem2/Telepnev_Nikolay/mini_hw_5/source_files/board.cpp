#include "board.h"
#include <algorithm>
#include <random>
#include <vector>

Board::Board() : mv_(0), err_(0), left_(8) {
  std::vector<char> syms;
  for (char c = 'A'; c <= 'H'; ++c) {
    syms.push_back(c);
    syms.push_back(c);
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(syms.begin(), syms.end(), gen);

  int idx = 0;
  for (int i = 0; i < kSize; ++i) {
    for (int j = 0; j < kSize; ++j) {
      g_[i][j].sym = syms[idx++];
      g_[i][j].mtch = false;
      g_[i][j].fup = false;
    }
  }
}

bool Board::allDone() const { return left_ == 0; }

bool Board::cellDone(int r, int c) const { return g_[r][c].mtch; }

char Board::symAt(int r, int c) const { return g_[r][c].sym; }

bool Board::isUp(int r, int c) const { return g_[r][c].fup; }

bool Board::open(int r, int c) {
  if (g_[r][c].mtch || g_[r][c].fup) return false;
  g_[r][c].fup = true;
  return true;
}

void Board::hideAll() {
  for (int i = 0; i < kSize; ++i) {
    for (int j = 0; j < kSize; ++j) {
      if (!g_[i][j].mtch) g_[i][j].fup = false;
    }
  }
}

bool Board::match(int r1, int c1, int r2, int c2) {
  if (g_[r1][c1].sym == g_[r2][c2].sym) {
    g_[r1][c1].mtch = true;
    g_[r2][c2].mtch = true;
    g_[r1][c1].fup = false;
    g_[r2][c2].fup = false;
    --left_;
    return true;
  }
  return false;
}

void Board::shuffle() {
  std::vector<std::pair<int, int>> pos;
  std::vector<char> syms;

  for (int i = 0; i < kSize; ++i) {
    for (int j = 0; j < kSize; ++j) {
      if (!g_[i][j].mtch) {
        pos.emplace_back(i, j);
        syms.push_back(g_[i][j].sym);
      }
    }
  }

  if (pos.empty()) return;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(syms.begin(), syms.end(), gen);

  for (size_t k = 0; k < pos.size(); ++k) {
    int i = pos[k].first;
    int j = pos[k].second;
    g_[i][j].sym = syms[k];
  }
}