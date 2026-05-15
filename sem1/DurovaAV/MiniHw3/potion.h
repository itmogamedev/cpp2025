#pragma once

#include "MagicItem.h"

class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(const std::string& name, int price, double weight, double duration);
  std::variant<int, double, std::string> getSpecParam() const override;
};
