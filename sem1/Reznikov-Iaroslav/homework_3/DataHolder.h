#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "MagicItem.h"
#include "Shop.h"

class DataHolder {
 public:
  DataHolder(const std::string&);
  const std::vector<std::unique_ptr<Shop>>& getShops() const { return shops; };

 private:
  void loadFromFile(const std::string&);
  std::vector<std::unique_ptr<Shop>> shops;
  std::string WEAPON_STR = "Weapon";
  std::string ARMOR_STR = "Armor";
  std::string POTION_STR = "Potion";
  std::string SCROLL_STR = "Scroll";
};
