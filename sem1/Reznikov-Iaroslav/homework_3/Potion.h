#pragma once
#include <iostream>
#include <sstream>

#include "MagicItem.h"

class Potion : public MagicItem {
 public:
  Potion(std::stringstream& paramLine);
  std::variant<std::string, int, double> getSpecParam() const override;
  void introduceSelf() const override;
};
