#include "Scroll.h"

#include <sstream>
#include <string>

Scroll::Scroll(std::stringstream& line) : MagicItem(line) {
  std::string effect;
  line >> effect;
  specParam = effect;
}

std::variant<std::string, int, double> Scroll::getSpecParam() const {
  return specParam;
}

void Scroll::introduceSelf() const {
  auto par = getSpecParam();
  std::cout << getName() << " " << getPrice() << " " << getWeight() << " "
            << std::get<std::string>(getSpecParam()) << std::endl;
}
