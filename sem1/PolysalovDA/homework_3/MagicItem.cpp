#include "MagicItem.h"

MagicItem::MagicItem(const std::string& name, int price, double weight)
    : name(name), price(price), weight(weight) {}

std::string MagicItem::getName() const { return name; }

int MagicItem::getPrice() const { return price; }

double MagicItem::getWeight() const { return weight; }