#pragma once

#include "magic_item.h"

class Armor : public MagicItem {
 private:
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int def);
  std::variant<int, double, std::string> getSpecParam() const override;
  std::string getType() const override;
};
