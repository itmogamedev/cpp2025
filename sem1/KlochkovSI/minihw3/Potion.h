#ifndef POTION_H
#define POTION_H

#include "MagicItem.h"

class Potion : public MagicItem {
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double d);
  Type getType() const override;
  std::variant<int, double, std::string> getSpecParam() const override;
};

#endif
