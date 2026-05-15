#pragma once
#include <iostream>
#include <variant>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string, int, double);
  virtual std::variant<int, double, std::string> getSpecParam() = 0;
  int getPrice() { return price; };
  double getWeight() { return weight; };
};
