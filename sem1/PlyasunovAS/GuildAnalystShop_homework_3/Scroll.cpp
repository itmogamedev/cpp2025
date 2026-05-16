#include "Scroll.h"

Scroll::Scroll(const std::string& scrollName, int scrollPrice,
    double scrollWeight, const std::string& scrollEffect)
    : MagicItem(scrollName, scrollPrice, scrollWeight), effect(scrollEffect) {
}

std::string Scroll::getSpecParam() const {
    return effect;
}

std::string Scroll::getEffect() const {
    return effect;
}