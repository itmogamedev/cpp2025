#ifndef SCROLL_H
#define SCROLL_H

#include "magic_item.h"

class Scroll : public MagicItem {
 public:
  Scroll(const std::string& name, int price, double weight,
         const std::string& effect)
      : MagicItem(name, price, weight), effect(effect) {}

  const std::string& getEffect() const { return effect; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }

  std::string getTypeName() const override { return "Scroll"; }

 private:
  std::string effect;
};

#endif  // SCROLL_H
