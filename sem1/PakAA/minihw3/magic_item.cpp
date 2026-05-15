#include "magic_item.h"

MagicItem::MagicItem(const std::string& item_name, int item_price,
    double item_weight)
    : name_(item_name), price_(item_price), weight_(item_weight) {
}

std::string MagicItem::getName() const { return name_; }

int MagicItem::getPrice() const { return price_; }

double MagicItem::getWeight() const { return weight_; }