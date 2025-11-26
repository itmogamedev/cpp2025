#include "armor.h"

Armor::Armor(const std::string& n, int p, double w, int def)
    : MagicItem(n, p, w), defense(def) {}

std::variant<int, double, std::string> Armor::getSpecParam() const {
  return defense;
}

std::string Armor::getType() const { return "Armor"; }
