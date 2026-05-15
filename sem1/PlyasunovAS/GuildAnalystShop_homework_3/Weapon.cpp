#include "Weapon.h"
#include <sstream>

Weapon::Weapon(const std::string& weaponName, int weaponPrice,
    double weaponWeight, int weaponDamage)
    : MagicItem(weaponName, weaponPrice, weaponWeight), damage(weaponDamage) {
}

std::string Weapon::getSpecParam() const {
    return std::to_string(damage);
}

int Weapon::getDamage() const {
    return damage;
}