#pragma once

#include <iostream>
#include <string>
#include <variant>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  virtual ~MagicItem() = default;
  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
};
