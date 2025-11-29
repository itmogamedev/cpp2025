#ifndef SCROLL_H
#define SCROLL_H

#include "MagicItem.h"

class Scroll : public MagicItem {
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& e);
  Type getType() const override;
  std::variant<int, double, std::string> getSpecParam() const override;
};

#endif
