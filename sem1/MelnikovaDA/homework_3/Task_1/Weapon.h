#ifndef WEAPON_H
#define WEAPON_H

#include "MagicItem.h"

class weapon : public magicItem {
private:
    int damage;

public:
    weapon(const std::string& name, int price, double weight, int weapon_Damage);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    int getDamage() const;
};

#endif