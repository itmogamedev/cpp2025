#include "MagicItem.h"
std::string MagicItem::getName() { return name; }
int MagicItem::getPrice() { return price; }
int MagicItem::getWeight() { return weight; }
MagicItem::MagicItem(std::string name, int price, int weight) {
  this->name = name;
  this->price = price;
  this->weight = weight;
}

std::string Weapon::getSpecialParm() const { return std::to_string(damage); }
Weapon::Weapon(std::string name, int price, int weight, int special)
    : MagicItem(name, price, weight) {
  damage = special;
}
std::string Armor::getSpecialParm() const { return std::to_string(defense); }
Armor::Armor(std::string name, int price, int weight, int special)
    : MagicItem(name, price, weight) {
  defense = special;
}
std::string Posion::getSpecialParm() const { return std::to_string(duration); }
Posion::Posion(std::string name, int price, int weight, double special)
    : MagicItem(name, price, weight) {
  duration = special;
}
std::string Scroll::getSpecialParm() const { return effect; }
Scroll::Scroll(std::string name, int price, int weight, std::string special)
    : MagicItem(name, price, weight) {
  effect = special;
}
