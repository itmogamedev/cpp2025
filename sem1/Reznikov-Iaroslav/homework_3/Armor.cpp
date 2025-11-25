#include "Armor.h"

#include <sstream>
#include <string>

Armor::Armor(std::stringstream& line) : MagicItem(line) {
  std::string specP;
  line >> specP;
  specParam = std::stoi(specP);
}

std::variant<std::string, int, double> Armor::getSpecParam() const {
  return specParam;
}

void Armor::introduceSelf() const {
  auto par = getSpecParam();
  std::cout << getName() << " " << getPrice() << " " << getWeight() << " "
            << std::get<int>(getSpecParam()) << std::endl;
}
