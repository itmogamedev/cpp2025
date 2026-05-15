#include "Weapon.h"

#include <sstream>
#include <string>

Weapon::Weapon(std::stringstream& line) : MagicItem(line) {
  int damage;
  line >> damage;
  specParam = damage;
}

std::variant<std::string, int, double> Weapon::getSpecParam() const {
  return specParam;
}

void Weapon::introduceSelf() const {
  auto par = getSpecParam();
  std::cout << getName() << " " << getPrice() << " " << getWeight() << " "
            << std::get<int>(getSpecParam()) << std::endl;
}
