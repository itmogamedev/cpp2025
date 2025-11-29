//реализация конструктора weapon и виртуальных функций специфического параметра и типа предмета
#include "weapon.h"
#include <iostream>

Weapon::Weapon(std::string name, int price, double weight, int damage)
    : MagicItem(std::move(name), price, weight), damage(damage) {
}

void Weapon::printSpecParam(std::ostream& os) const {
    os << "средний урон = " << damage;
}

const char* Weapon::getTypeName() const {
    return "Weapon";
}