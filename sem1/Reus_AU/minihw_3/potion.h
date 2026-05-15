#pragma once

#include "magic_item.h"

class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double dur);
  std::variant<int, double, std::string> getSpecParam() const override;
  std::string getType() const override;
};
