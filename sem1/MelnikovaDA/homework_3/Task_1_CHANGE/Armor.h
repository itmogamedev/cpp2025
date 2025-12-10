#ifndef ARMOR_H
#define ARMOR_H

#include "MagicItem.h"

class armor : public magicItem {
private:
    int defense;

public:
    armor(const std::string& name, int price, double weight, int armor_Defense);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    int getDefense() const;
};

#endif