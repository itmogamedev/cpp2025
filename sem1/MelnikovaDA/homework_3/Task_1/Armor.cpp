#include "Armor.h"

armor::armor(const std::string& name, int price, double weight,
             int armor_Defense)
    : magicItem(name, price, weight), defense(armor_Defense) {}

std::string armor::getType() const { return "Armor"; }

int armor::getIntParam() const { return defense; }

double armor::getDoubleParam() const { return 0.0; }

std::string armor::getStringParam() const { return ""; }

int armor::getDefense() const { return defense; }
