//объ€вление класса armor
#pragma once
#include "item.h"

class Armor : public MagicItem {
public:
    Armor(std::string name, int price, double weight, int defense);
    void printSpecParam(std::ostream& os) const;
    const char* getTypeName() const;
    int getDefense() const { return defense; }

private:
    int defense;
};