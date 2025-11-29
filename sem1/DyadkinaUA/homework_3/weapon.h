#ifndef WEAPON_H
#define WEAPON_H

#include "magic_item.h"

class Weapon : public MagicItem {
 public:
  Weapon(const std::string& name, int price, double weight, int damage)
      : MagicItem(name, price, weight), damage(damage) {}

  int getDamage() const { return damage; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }

  std::string getTypeName() const override { return "Weapon"; }

 private:
  int damage;
};

#endif  // WEAPON_H
