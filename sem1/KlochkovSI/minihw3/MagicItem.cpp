#include "MagicItem.h"

MagicItem::MagicItem(const std::string& n, int p, double w)
    : name(n), price(p), weight(w) {}

int MagicItem::getPrice() const { return price; }
double MagicItem::getWeight() const { return weight; }
