#pragma once
#include <iostream>

#include "MagicItem.h"

class Weapon : public MagicItem {
 public:
  Weapon(std::stringstream&);
  std::variant<std::string, int, double> getSpecParam() const override;
  void introduceSelf() const override;
};
