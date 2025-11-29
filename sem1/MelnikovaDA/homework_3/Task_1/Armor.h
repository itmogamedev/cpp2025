#ifndef ARMOR_H
#define ARMOR_H

#include "MagicItem.h"

class Armor : public MagicItem {
private:
    int defense;

public:
    Armor(const std::string& name, int price, double weight, int armorDefense);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    int getDefense() const;
};

#endif