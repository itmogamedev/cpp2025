#pragma once
#include <iostream>

#include "MagicItem.h"

class Armor : public MagicItem {
 public:
  Armor(std::stringstream&);
  std::variant<std::string, int, double> getSpecParam() const override;
  void introduceSelf() const override;
};
