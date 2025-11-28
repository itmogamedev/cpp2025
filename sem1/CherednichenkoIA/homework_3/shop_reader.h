#pragma once


#include "magic_item.h"
#include <vector>
#include <string>

struct Shop {
    std::string name;
    std::vector<std::unique_ptr<MagicItem>> items;
};

std::vector<Shop> readShopsFromFile(const std::string& filename);

