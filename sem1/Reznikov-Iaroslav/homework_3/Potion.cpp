#include "Potion.h"

#include <sstream>
#include <string>

Potion::Potion(std::stringstream& line) : MagicItem(line) {
  double duration;
  line >> duration;
  specParam = duration;
}

std::variant<std::string, int, double> Potion::getSpecParam() const {
  return specParam;
}

void Potion::introduceSelf() const {
  auto par = getSpecParam();
  std::cout << getName() << " " << getPrice() << " " << getWeight() << " "
            << std::get<double>(getSpecParam()) << std::endl;
}
