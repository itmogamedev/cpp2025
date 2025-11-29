#include "Weapon.h"

Weapon::Weapon(const std::string& name, int price, double weight, int weaponDamage)
    : MagicItem(name, price, weight), damage(weaponDamage) {
}

std::string Weapon::getType() const {
    return "Weapon";
}

int Weapon::getIntParam() const {
    return damage;
}

double Weapon::getDoubleParam() const {
    return 0.0;
}

std::string Weapon::getStringParam() const {
    return "";
}

int Weapon::getDamage() const {
    return damage;
}