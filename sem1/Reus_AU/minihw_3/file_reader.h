#pragma once

#include <string>
#include <vector>

#include "shop.h"

class FileReader {
 public:
  static std::vector<Shop> readFromFile(const std::string& filename);
};
