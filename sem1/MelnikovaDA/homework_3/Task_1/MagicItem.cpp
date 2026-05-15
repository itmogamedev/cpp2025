#include "MagicItem.h"

magicItem::magicItem(const std::string& item_Name, int item_Price, double item_Weight)
    : name(item_Name), price(item_Price), weight(item_Weight) {
}

std::string magicItem::getName() const {
    return name;
}

int magicItem::getPrice() const {
    return price;
}

double magicItem::getWeight() const {
    return weight;
}