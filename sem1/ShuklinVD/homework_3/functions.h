#pragma once
#include <string>
#include <vector>

#include "MagicItems.h"

void readFile(std::string filename);
std::string averangeCost(std::vector<MagicItem*> items);
std::string averangeWeight(std::vector<MagicItem*> items);
std::string averangeAtack(std::vector<MagicItem*> items);
std::string averangeDefense(std::vector<MagicItem*> items);
std::string averangeDuration(std::vector<MagicItem*> items);
std::string mostCommonEfect(std::vector<MagicItem*> items);
