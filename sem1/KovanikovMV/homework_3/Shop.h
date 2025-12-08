#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "MagicItem.h"
class Shop {
 private:
  std::vector<MagicItem*> items_container;
  std::string name;

 public:
  Shop(const std::string& name) : name(name) {};
  int getItemsAmount() { return items_container.size(); }
  std::string getName() { return name; }

  void addItem(const std::string& type, const std::string& name, int price,
               double weight, const std::string& specParam);
  double avgPrice();
  double avgWeight();

  double avgParam(const std::string& type);

  std::string avgScroll();
};
