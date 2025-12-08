#include "DerivedItems.h"

Weapon::Weapon(const std::string& name, int price, double weight, int damage)
    : MagicItem(name, price, weight), damage(damage) {}

std::variant<int, double, std::string> Weapon::getSpecParam() const {
  return damage;
}

std::string Weapon::getType() const { return "оружие"; }

Armor::Armor(const std::string& name, int price, double weight, int defense)
    : MagicItem(name, price, weight), defense(defense) {}

std::variant<int, double, std::string> Armor::getSpecParam() const {
  return defense;
}

std::string Armor::getType() const { return "защита"; }

Brace::Brace(const std::string& name, int price, double weight,
             const std::string& effect)
    : MagicItem(name, price, weight), effect(effect) {}

std::variant<int, double, std::string> Brace::getSpecParam() const {
  return effect;
}

std::string Brace::getType() const { return "скрепы"; }

Mushroom::Mushroom(const std::string& name, int price, double weight,
                   const std::string& roaring)
    : MagicItem(name, price, weight), roaring(roaring) {}

std::variant<int, double, std::string> Mushroom::getSpecParam() const {
  return roaring;
}

std::string Mushroom::getType() const { return "грибы"; }