#include "scroll.h"

Scroll::Scroll(const std::string& n, int p, double w, const std::string& eff)
    : MagicItem(n, p, w), effect(eff) {}

std::variant<int, double, std::string> Scroll::getSpecParam() const {
  return effect;
}

std::string Scroll::getType() const { return "Scroll"; }
