#include "DerivedItems.h"

Weapon::Weapon(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), damage(d) {}

std::variant<int, double, std::string> Weapon::getSpecParam() const {
  return damage;
}

std::string Weapon::getType() const { return "оружие"; }

Armor::Armor(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), defense(d) {}

std::variant<int, double, std::string> Armor::getSpecParam() const {
  return defense;
}

std::string Armor::getType() const { return "защита"; }

Scroll::Scroll(const std::string& n, int p, double w, const std::string& e)
    : MagicItem(n, p, w), effect(e) {}

std::variant<int, double, std::string> Scroll::getSpecParam() const {
  return effect;
}

std::string Scroll::getType() const { return "скрепы"; }

Mushroom::Mushroom(const std::string& n, int p, double w,
                   const std::string& pot)
    : MagicItem(n, p, w), potency(pot) {}

std::variant<int, double, std::string> Mushroom::getSpecParam() const {
  return potency;
}

std::string Mushroom::getType() const { return "грибы"; }