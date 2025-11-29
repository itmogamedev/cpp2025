#include "Scroll.h"

Scroll::Scroll(const std::string& n, int p, double w, const std::string& e)
    : MagicItem(n, p, w), effect(e) {}

MagicItem::Type Scroll::getType() const { return Type::Scroll; }
std::variant<int, double, std::string> Scroll::getSpecParam() const {
  return effect;
}
