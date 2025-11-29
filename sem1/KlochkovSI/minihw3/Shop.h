#ifndef SHOP_H
#define SHOP_H

#include <memory>
#include <string>
#include <vector>

#include "MagicItem.h"

struct Shop {
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;
};

#endif
