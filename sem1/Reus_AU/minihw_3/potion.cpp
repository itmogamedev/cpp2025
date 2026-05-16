#include "potion.h"

Potion::Potion(const std::string& n, int p, double w, double dur)
    : MagicItem(n, p, w), duration(dur) {}

std::variant<int, double, std::string> Potion::getSpecParam() const {
  return duration;
}

std::string Potion::getType() const { return "Potion"; }
