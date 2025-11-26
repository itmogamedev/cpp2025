#pragma once

#include "magic_item.h"

class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int d);
  std::variant<int, double, std::string> getSpecParam() const override;
  std::string getType() const override;
};
