#pragma once

#include "magic_item.h"

class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& eff);
  std::variant<int, double, std::string> getSpecParam() const override;
  std::string getType() const override;
};
