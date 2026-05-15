#include "magic_item.h"

MagicItem::MagicItem(const std::string name, int price, double weight)
    : name(name), price(price), weight(weight) {}

const std::string& MagicItem::getName() const { return name; }

int MagicItem::getPrice() const { return price; }

double MagicItem::getWeight() const { return weight; }

Weapon::Weapon(const std::string& name, int price, double weight, int damage)
    : MagicItem(name, price, weight), damage(damage) {}

SpecParam Weapon::getSpecParam() const { return damage; }

std::string Weapon::getTypeName() const { return "Weapon"; }

Armor::Armor(const std::string& name, int price, double weight, int defense)
    : MagicItem(name, price, weight), defense(defense) {}

SpecParam Armor::getSpecParam() const { return defense; }

std::string Armor::getTypeName() const { return "Armor"; }

Potion::Potion(const std::string& name, int price, double weight,
               double duration)
    : MagicItem(name, price, weight), duration(duration) {}

SpecParam Potion::getSpecParam() const { return duration; }

std::string Potion::getTypeName() const { return "Potion"; }

Scroll::Scroll(const std::string& name, int price, double weight,
               const std::string& effect)
    : MagicItem(name, price, weight), effect(effect) {}

SpecParam Scroll::getSpecParam() const { return effect; }

std::string Scroll::getTypeName() const { return "Scroll"; }
