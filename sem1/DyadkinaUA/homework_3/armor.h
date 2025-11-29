#ifndef ARMOR_H
#define ARMOR_H

#include "magic_item.h"

class Armor : public MagicItem {
 public:
  Armor(const std::string& name, int price, double weight, int defense)
      : MagicItem(name, price, weight), defense(defense) {}

  int getDefense() const { return defense; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return defense;
  }

  std::string getTypeName() const override { return "Armor"; }

 private:
  int defense;
};

#endif  // ARMOR_H
