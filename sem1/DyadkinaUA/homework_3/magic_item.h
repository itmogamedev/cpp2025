#ifndef MAGIC_ITEM_H
#define MAGIC_ITEM_H

#include <string>
#include <variant>

class MagicItem {
 public:
  MagicItem(const std::string& name, int price, double weight)
      : name(name), price(price), weight(weight) {}

  virtual ~MagicItem() = default;

  const std::string& getName() const { return name; }
  int getPrice() const { return price; }
  double getWeight() const { return weight; }

  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
  virtual std::string getTypeName() const = 0;

 protected:
  std::string name;
  int price;
  double weight;
};

#endif  // MAGIC_ITEM_H
