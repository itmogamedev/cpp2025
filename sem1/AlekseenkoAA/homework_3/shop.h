#pragma once

#include <memory>
#include <string>
#include <vector>

#include "magic_item.h"

class Shop {
 public:
  Shop(const std::string& name);

  void addItem(std::unique_ptr<MagicItem> items);

  void printReport() const;

 private:
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;

  double averagePrice() const;
  double averageWeight() const;

  void printTypeStats() const;
};
