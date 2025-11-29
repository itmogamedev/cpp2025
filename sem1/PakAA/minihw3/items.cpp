#include "items.h"

// Weapon
Weapon::Weapon(const std::string& item_name, int item_price,
    double item_weight, int item_damage)
    : MagicItem(item_name, item_price, item_weight), damage(item_damage) {
}

std::variant<int, double, std::string> Weapon::getSpecParam() const {
    return damage;
}

// Armor
Armor::Armor(const std::string& item_name, int item_price,
    double item_weight, int item_defense)
    : MagicItem(item_name, item_price, item_weight), defense(item_defense) {
}

std::variant<int, double, std::string> Armor::getSpecParam() const {
    return defense;
}

// Potion
Potion::Potion(const std::string& item_name, int item_price,
    double item_weight, double item_duration)
    : MagicItem(item_name, item_price, item_weight), duration(item_duration) {
}

std::variant<int, double, std::string> Potion::getSpecParam() const {
    return duration;
}

// Scroll
Scroll::Scroll(const std::string& item_name, int item_price,
    double item_weight, const std::string& item_effect)
    : MagicItem(item_name, item_price, item_weight), effect(item_effect) {
}

std::variant<int, double, std::string> Scroll::getSpecParam() const {
    return effect;
}