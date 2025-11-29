#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include "magic_item.h"

class Weapon : public MagicItem {
public:
    Weapon(const std::string& item_name, int item_price, double item_weight,
        int item_damage);
    std::variant<int, double, std::string> getSpecParam() const override;

private:
    int damage;
};

class Armor : public MagicItem {
public:
    Armor(const std::string& item_name, int item_price, double item_weight,
        int item_defense);
    std::variant<int, double, std::string> getSpecParam() const override;

private:
    int defense;
};

class Potion : public MagicItem {
public:
    Potion(const std::string& item_name, int item_price, double item_weight,
        double item_duration);
    std::variant<int, double, std::string> getSpecParam() const override;

private:
    double duration;
};

class Scroll : public MagicItem {
public:
    Scroll(const std::string& item_name, int item_price, double item_weight,
        const std::string& item_effect);
    std::variant<int, double, std::string> getSpecParam() const override;

private:
    std::string effect;
};

#endif  // ITEMS_H