#pragma once
#include <string>
#include <variant>

class MagicItem {
 public:
  std::string getName() const { return name; }
  int getPrice() const { return price; }
  double getWeight() const { return weight; }
  virtual std::variant<std::string, int, double> getSpecParam() const = 0;
  virtual void introduceSelf() const = 0;
  virtual ~MagicItem() = default;

 protected:
  MagicItem(const std::string& name, int price, const double& weight)
      : name(name), price(price), weight(weight) {};
  MagicItem(std::stringstream&);
  std::string name;
  int price;
  double weight;
  std::variant<std::string, int, double> specParam;
};
