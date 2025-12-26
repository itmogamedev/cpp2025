#include "Scroll.h"

Scroll::Scroll(const std::string& name, int price, double weight,
    const std::string& effect) {
    this->name = name;
    this->price = price;
    this->weight = weight;
    this->effect = effect;
}

std::variant<int, double, std::string> Scroll::getSpecParam() const {
    return effect;
}