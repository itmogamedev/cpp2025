//создание объекта и возвращение значений полей
#include "item.h"                           

MagicItem::MagicItem(std::string name, int price, double weight)
    : name(std::move(name)), price(price), weight(weight) {
}

const std::string& MagicItem::getName() const { return name; }
int MagicItem::getPrice() const { return price; }
double MagicItem::getWeight() const { return weight; }