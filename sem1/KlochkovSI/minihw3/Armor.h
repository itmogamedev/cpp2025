#ifndef ARMOR_H
#define ARMOR_H

#include "MagicItem.h"

class Armor : public MagicItem {
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int def);
  Type getType() const override;
  std::variant<int, double, std::string> getSpecParam() const override;
};

#endif
