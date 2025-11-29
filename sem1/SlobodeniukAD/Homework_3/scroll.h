// объ€вление класса scroll
#pragma once
#include <string>

#include "item.h"

class Scroll : public MagicItem {
 public:
  Scroll(std::string name, int price, double weight, std::string effect);
  void printSpecParam(std::ostream& os) const;
  const char* getTypeName() const;
  const std::string& getEffect() const { return effect; }

 private:
  std::string effect;
};
