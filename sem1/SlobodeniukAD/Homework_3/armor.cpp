//реализация конструктора armor и виртуальных функций специфического параметра и типа предмета
#include "armor.h"
#include <iostream>

Armor::Armor(std::string name, int price, double weight, int defense)
    : MagicItem(std::move(name), price, weight), defense(defense) {
}

void Armor::printSpecParam(std::ostream& os) const {
    os << "средняя защита = " << defense;
}

const char* Armor::getTypeName() const {
    return "Armor";
}