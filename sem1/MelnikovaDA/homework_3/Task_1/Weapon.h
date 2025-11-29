#ifndef WEAPON_H
#define WEAPON_H

#include "MagicItem.h"

class Weapon : public MagicItem {
private:
    int damage;

public:
    Weapon(const std::string& name, int price, double weight, int weaponDamage);
    std::string getType() const override;
    int getIntParam() const override;
    double getDoubleParam() const override;
    std::string getStringParam() const override;
    int getDamage() const;
};

#endif