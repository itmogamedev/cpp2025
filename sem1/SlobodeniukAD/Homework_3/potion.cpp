//реализаци€ конструктора potion и виртуальных функций специфического параметра и типа предмета
#include "potion.h"
#include <iostream>
#include <iomanip>

Potion::Potion(std::string name, int price, double weight, double duration)
    : MagicItem(std::move(name), price, weight), duration(duration) {
}

void Potion::printSpecParam(std::ostream& os) const {
    os << "средн€€ длительность = " << std::fixed << std::setprecision(1) << duration;
}

const char* Potion::getTypeName() const {
    return "Potion";
}