#include "Potion.h"

Potion::Potion(const std::string& n, int p, double w, double d)
    : MagicItem(n, p, w), duration(d) {}

MagicItem::Type Potion::getType() const { return Type::Potion; }
std::variant<int, double, std::string> Potion::getSpecParam() const {
  return duration;
}
