#include "Weapon.h"

weapon::weapon(const std::string& name, int price, double weight,
               int weaponDamage)
    : magicItem(name, price, weight), damage(weaponDamage) {}

std::string weapon::getType() const { return "Weapon"; }

int weapon::getIntParam() const { return damage; }

double weapon::getDoubleParam() const { return 0.0; }

std::string weapon::getStringParam() const { return ""; }

int weapon::getDamage() const { return damage; }
