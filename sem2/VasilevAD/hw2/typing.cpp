#include "typing.h"

#include <ctime>

Typing::Typing(std::string alph) : pool(alph) {
  srand(static_cast<unsigned int>(time(0)));
  GenerateNewTarget();
}

void Typing::Update(float dt) {
  if (!win && !lose) {
    timeLeft -= dt;
    if (timeLeft <= 0) {
      timeLeft = 0;
      lose = true;
    }
  }
}

bool Typing::CheckInput(uint32_t unicode) {
  if (win || lose) return false;

  if (unicode == static_cast<uint32_t>(target)) {
    score++;
    if (score >= 10)
      win = true;
    else
      GenerateNewTarget();
    return true;
  } else {
    timeLeft -= 2.0f;
    return false;
  }
}

void Typing::GenerateNewTarget() {
  target = pool[rand() % pool.length()];
}