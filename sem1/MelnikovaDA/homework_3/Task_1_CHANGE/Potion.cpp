#include "Potion.h"

potion::potion(const std::string& name, int price, double weight,
               double potion_Duration)
    : magicItem(name, price, weight), duration(potion_Duration) {}

std::string potion::getType() const { return "Potion"; }

int potion::getIntParam() const { return 0; }

double potion::getDoubleParam() const { return duration; }

std::string potion::getStringParam() const { return ""; }

double potion::getDuration() const { return duration; }
