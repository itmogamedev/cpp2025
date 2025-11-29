#include "MagicItem.h"

MagicItem::MagicItem(const std::string& itemName, int itemPrice, double itemWeight)
    : name(itemName), price(itemPrice), weight(itemWeight) {
}

std::string MagicItem::getName() const {
    return name;
}

int MagicItem::getPrice() const {
    return price;
}

double MagicItem::getWeight() const {
    return weight;
}