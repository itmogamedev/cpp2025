//реализация конструктора scroll и виртуальных функций специфического параметра и типа предмета
#include "scroll.h"
#include <iostream>

Scroll::Scroll(std::string name, int price, double weight, std::string effect)
    : MagicItem(std::move(name), price, weight), effect(std::move(effect)) {
}

void Scroll::printSpecParam(std::ostream& os) const {
    os << "самый частый эффект " << effect;
}

const char* Scroll::getTypeName() const {
    return "Scroll";
}