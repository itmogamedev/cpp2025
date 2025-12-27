#pragma once

#include "MagicItem.h"

class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(const std::string& name, int price, double weight,
         const std::string& effect);
  std::variant<int, double, std::string> getSpecParam() const override;
};
