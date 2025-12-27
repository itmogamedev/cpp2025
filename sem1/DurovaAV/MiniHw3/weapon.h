#pragma once

#include "MagicItem.h"

class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(const std::string& name, int price, double weight, int damage);
  std::variant<int, double, std::string> getSpecParam() const override;
};
