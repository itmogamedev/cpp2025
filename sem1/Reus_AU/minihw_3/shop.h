#pragma once

#include <memory>
#include <string>
#include <vector>

#include "magic_item.h"

class Shop {
 private:
  std::string name;
  std::vector<std::shared_ptr<MagicItem>> items;

  void analyzeWeapons() const;
  void analyzeArmor() const;
  void analyzePotions() const;
  void analyzeScrolls() const;

 public:
  explicit Shop(const std::string& n);
  void addItem(std::shared_ptr<MagicItem> item);
  void analyze() const;
};
