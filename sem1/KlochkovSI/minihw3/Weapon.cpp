#include "Weapon.h"

Weapon::Weapon(const std::string& n, int p, double w, int dmg)
    : MagicItem(n, p, w), damage(dmg) {}

MagicItem::Type Weapon::getType() const { return Type::Weapon; }
std::variant<int, double, std::string> Weapon::getSpecParam() const {
  return damage;
}
