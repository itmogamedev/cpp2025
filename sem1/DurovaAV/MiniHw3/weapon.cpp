#include "Weapon.h"

Weapon::Weapon(const std::string& name, int price, double weight, int damage) {
  this->name = name;
  this->price = price;
  this->weight = weight;
  this->damage = damage;
}

std::variant<int, double, std::string> Weapon::getSpecParam() const {
  return damage;
}
