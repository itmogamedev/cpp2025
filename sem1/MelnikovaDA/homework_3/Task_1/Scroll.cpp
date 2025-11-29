#include "Scroll.h"

Scroll::Scroll(const std::string& name, int price, double weight,
               const std::string& scrollEffect)
    : MagicItem(name, price, weight), effect(scrollEffect) {}

std::string Scroll::getType() const { return "Scroll"; }

int Scroll::getIntParam() const { return 0; }

double Scroll::getDoubleParam() const { return 0.0; }

std::string Scroll::getStringParam() const { return effect; }

std::string Scroll::getEffect() const { return effect; }
