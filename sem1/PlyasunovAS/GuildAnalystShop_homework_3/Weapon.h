#ifndef WEAPON_H
#define WEAPON_H

#include "MagicItem.h"

class Weapon : public MagicItem {
private:
    int damage;

public:
    Weapon(const std::string& weaponName, int weaponPrice,
        double weaponWeight, int weaponDamage);
    std::string getSpecParam() const override;
    int getDamage() const;
};

#endif