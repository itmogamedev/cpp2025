#include "items.h"
#include <string>

Weapon::Weapon(const std::string& item_name, int item_price,
    double item_weight, int item_damage)
    : MagicItem(item_name, item_price, item_weight), damage_(item_damage) {
}

std::string Weapon::getSpecialParam() const {
    return std::to_string(damage_);
}

Armor::Armor(const std::string& item_name, int item_price, double item_weight,
    int item_defense)
    : MagicItem(item_name, item_price, item_weight), defense_(item_defense) {
}

std::string Armor::getSpecialParam() const {
    return std::to_string(defense_);
}

Potion::Potion(const std::string& item_name, int item_price,
    double item_weight, double item_duration)
    : MagicItem(item_name, item_price, item_weight), duration_(item_duration) {
}

std::string Potion::getSpecialParam() const {
    return std::to_string(duration_);
}

Scroll::Scroll(const std::string& item_name, int item_price,
    double item_weight, const std::string& item_effect)
    : MagicItem(item_name, item_price, item_weight), effect_(item_effect) {
}

std::string Scroll::getSpecialParam() const {
    return effect_;
}