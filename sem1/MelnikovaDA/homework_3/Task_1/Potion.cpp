#include "Potion.h"

Potion::Potion(const std::string& name, int price, double weight,
               double potionDuration)
    : MagicItem(name, price, weight), duration(potionDuration) {}

std::string Potion::getType() const { return "Potion"; }

int Potion::getIntParam() const { return 0; }

double Potion::getDoubleParam() const { return duration; }

std::string Potion::getStringParam() const { return ""; }

double Potion::getDuration() const { return duration; }
