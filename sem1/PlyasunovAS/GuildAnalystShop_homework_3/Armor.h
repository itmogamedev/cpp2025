#ifndef ARMOR_H
#define ARMOR_H

#include "MagicItem.h"

class Armor : public MagicItem {
private:
    int defense;

public:
    Armor(const std::string& armorName, int armorPrice,
        double armorWeight, int armorDefense);
    std::string getSpecParam() const override;
    int getDefense() const;
};

#endif