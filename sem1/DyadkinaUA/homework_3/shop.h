#ifndef SHOP_H
#define SHOP_H

#include <memory>
#include <string>
#include <vector>

#include "magic_item.h"

class Shop {
 public:
  explicit Shop(const std::string& name) : name(name) {}

  const std::string& getName() const { return name; }

  void addItem(std::unique_ptr<MagicItem> item);

  int getItemCount() const;

  double getAveragePrice() const;
  double getAverageWeight() const;

  void printStats() const;

 private:
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;
};

#endif  // SHOP_H
