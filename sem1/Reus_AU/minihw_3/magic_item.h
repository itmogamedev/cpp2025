#pragma once
#pragma once

#include <string>
#include <variant>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& n, int p, double w);
  virtual ~MagicItem() = default;

  virtual std::variant<int, double, std::string> getSpecParam() const = 0;

  int getPrice() const;
  double getWeight() const;
  std::string getName() const;
  virtual std::string getType() const = 0;
};
