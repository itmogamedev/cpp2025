#include "Scroll.h"
Scroll::Scroll(std::string name, int price, double weight, std::string effect)
    : MagicItem(name, price, weight), effect(effect) {}
