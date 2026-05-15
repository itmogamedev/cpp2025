#include "Potion.h"

Potion::Potion(const std::string& name, int price, double weight,
               double duration) {
  this->name = name;
  this->price = price;
  this->weight = weight;
  this->duration = duration;
}

std::variant<int, double, std::string> Potion::getSpecParam() const {
  return duration;
}
