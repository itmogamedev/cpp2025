#include "Scroll.h"

scroll::scroll(const std::string& name, int price, double weight,
               const std::string& scroll_Effect)
    : magicItem(name, price, weight), effect(scroll_Effect) {}

std::string scroll::getType() const { return "Scroll"; }

int scroll::getIntParam() const { return 0; }

double scroll::getDoubleParam() const { return 0.0; }

std::string scroll::getStringParam() const { return effect; }

std::string scroll::getEffect() const { return effect; }
