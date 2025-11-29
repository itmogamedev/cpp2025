#include "Armor.h"

Armor::Armor(const std::string& name, int price, double weight,
             int armorDefense)
    : MagicItem(name, price, weight), defense(armorDefense) {}

std::string Armor::getType() const { return "Armor"; }

int Armor::getIntParam() const { return defense; }

double Armor::getDoubleParam() const { return 0.0; }

std::string Armor::getStringParam() const { return ""; }

int Armor::getDefense() const { return defense; }
