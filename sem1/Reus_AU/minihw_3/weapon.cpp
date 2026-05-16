#include "weapon.h"

Weapon::Weapon(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), damage(d) {}

std::variant<int, double, std::string> Weapon::getSpecParam() const {
  return damage;
}

std::string Weapon::getType() const { return "Weapon"; }
