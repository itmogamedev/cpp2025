#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "MagicItem.h"

class Shop {
 public:
  Shop(const std::string& name);

  Shop(const Shop&) = delete;
  Shop& operator=(const Shop&) = delete;

  Shop(Shop&&) = default;
  Shop& operator=(Shop&&) = default;

  void showItems() const;
  void addItem(std::unique_ptr<MagicItem>);
  void calculateStatistics() const;
  void introduceSelf() const;

 private:
  double calculateAveragePrice() const;
  double calculateAverageWeight() const;

  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;
};
