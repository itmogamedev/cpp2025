#pragma once
#include <iostream>

#include "MagicItem.h"

class Scroll : public MagicItem {
 public:
  Scroll(std::stringstream&);
  std::variant<std::string, int, double> getSpecParam() const override;
  void introduceSelf() const override;
};
