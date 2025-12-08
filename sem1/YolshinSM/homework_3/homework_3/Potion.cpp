#include "Potion.h"
Potion::Potion(std::string name, int price, double weight, double duration)
    : MagicItem(name, price, weight), duration(duration) {}
