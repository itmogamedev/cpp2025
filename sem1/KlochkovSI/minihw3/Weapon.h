#ifndef WEAPON_H
#define WEAPON_H

#include "MagicItem.h"

class Weapon : public MagicItem {
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int dmg);
  Type getType() const override;
  std::variant<int, double, std::string> getSpecParam() const override;
};

#endif
