#include "MagicItem.h"

#include <sstream>

MagicItem::MagicItem(std::stringstream& ss) {
  ss >> name;
  ss >> price;
  ss >> weight;
}
