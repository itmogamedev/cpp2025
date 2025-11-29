#ifndef MAGICITEM_H
#define MAGICITEM_H

#include <string>
#include <variant>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  enum class Type { Weapon, Armor, Potion, Scroll };

  MagicItem(const std::string& n, int p, double w);
  virtual ~MagicItem() = default;

  int getPrice() const;
  double getWeight() const;

  virtual Type getType() const = 0;
  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
};

#endif
