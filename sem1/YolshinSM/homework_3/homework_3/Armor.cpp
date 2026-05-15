#include "Armor.h"

Armor::Armor(std::string name, int price, double weight, int defense)
    : MagicItem(name, price, weight), defense(defense) {}
