#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include "magic_item.h"

class Weapon : public MagicItem {
public:
    Weapon(const std::string& item_name, int item_price, double item_weight,
        int item_damage);
    std::string getSpecialParam() const override;

private:
    int damage_;
};

class Armor : public MagicItem {
public:
    Armor(const std::string& item_name, int item_price, double item_weight,
        int item_defense);
    std::string getSpecialParam() const override;

private:
    int defense_;
};

class Potion : public MagicItem {
public:
    Potion(const std::string& item_name, int item_price, double item_weight,
        double item_duration);
    std::string getSpecialParam() const override;

private:
    double duration_;
};

class Scroll : public MagicItem {
public:
    Scroll(const std::string& item_name, int item_price, double item_weight,
        const std::string& item_effect);
    std::string getSpecialParam() const override;

private:
    std::string effect_;
};

#endif  // ITEMS_H