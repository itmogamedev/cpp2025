#ifndef POTION_H
#define POTION_H

#include "magic_item.h"

class Potion : public MagicItem {
 public:
  Potion(const std::string& name, int price, double weight, double duration)
      : MagicItem(name, price, weight), duration(duration) {}

  double getDuration() const { return duration; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }

  std::string getTypeName() const override { return "Potion"; }

 private:
  double duration;
};

#endif  // POTION_H
