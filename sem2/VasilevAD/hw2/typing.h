#pragma once
#include <string>

class Typing {
 public:
  Typing(std::string pool);

  void Update(float dt);
  bool CheckInput(uint32_t unicode);

  char GetCurrentTarget() const { return target; }
  int GetScore() const { return score; }
  float GetTime() const { return timeLeft; }
  bool Win() const { return win; }
  bool Lose() const { return lose; }

 private:
  void GenerateNewTarget();

  std::string pool;
  char target;
  int score = 0;
  float timeLeft = 30.0f;
  bool win = false;
  bool lose = false;
};