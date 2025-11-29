#include "Armor.h"

Armor::Armor(const std::string& n, int p, double w, int def)
    : MagicItem(n, p, w), defense(def) {}

MagicItem::Type Armor::getType() const { return Type::Armor; }
std::variant<int, double, std::string> Armor::getSpecParam() const {
  return defense;
}
