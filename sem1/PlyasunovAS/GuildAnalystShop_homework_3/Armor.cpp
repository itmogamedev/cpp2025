#include "Armor.h"
#include <sstream>

Armor::Armor(const std::string& armorName, int armorPrice,
    double armorWeight, int armorDefense)
    : MagicItem(armorName, armorPrice, armorWeight), defense(armorDefense) {
}

std::string Armor::getSpecParam() const {
    return std::to_string(defense);
}

int Armor::getDefense() const {
    return defense;
}