#ifndef FILEREADER_H
#define FILEREADER_H

#include "Shop.h"
#include <vector>
#include <string>

MagicItem* createItem(const std::string& type, const std::string& name,
                      int price, double weight, const std::string& specParam);

std::vector<Shop*> readShopsFromFile(const std::string& filename);

#endif