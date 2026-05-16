#include "magic_item.h"

MagicItem::MagicItem(std::string name, int price, double weight)
    : name(std::move(name)), price(price), weight(weight) {
}

int MagicItem::getPrice() const {
    return price;
}

double MagicItem::getWeight() const {
    return weight;
}

Weapon::Weapon(std::string name, int price, double weight, int damage)
    : MagicItem(std::move(name), price, weight), damage(damage) {
}

std::variant<int, double, std::string> Weapon::getSpecParam() const {
    return damage;
}

std::string Weapon::getTypeName() const {
    return "Weapon";
}

Armor::Armor(std::string name, int price, double weight, int defense)
    : MagicItem(std::move(name), price, weight), defense(defense) {
}

std::variant<int, double, std::string> Armor::getSpecParam() const {
    return defense;
}

std::string Armor::getTypeName() const {
    return "Armor";
}

Potion::Potion(std::string name, int price, double weight, double duration)
    : MagicItem(std::move(name), price, weight), duration(duration) {
}

std::variant<int, double, std::string> Potion::getSpecParam() const {
    return duration;
}

std::string Potion::getTypeName() const {
    return "Potion";
}

Scroll::Scroll(std::string name, int price, double weight, std::string effect)
    : MagicItem(std::move(name), price, weight), effect(std::move(effect)) {
}

std::variant<int, double, std::string> Scroll::getSpecParam() const {
    return effect;
}

std::string Scroll::getTypeName() const {
    return "Scroll";
}