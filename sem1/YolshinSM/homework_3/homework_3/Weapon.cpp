#include "Weapon.h"

Weapon::Weapon(std::string name, int price, double weight, int damage)
    : MagicItem(name, price, weight), damage(damage) {}
