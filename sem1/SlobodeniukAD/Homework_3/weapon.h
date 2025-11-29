//объ€вление класса weapon
#pragma once
#include "item.h"

class Weapon : public MagicItem {
public:
    Weapon(std::string name, int price, double weight, int damage);
    void printSpecParam(std::ostream& os) const;
    const char* getTypeName() const;
    int getDamage() const { return damage; }

private:
    int damage;
};