#pragma once
#include <string>
#include <variant>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& n, int p, double w)
      : name(n), price(p), weight(w) {}

  virtual ~MagicItem() = default;

  int getPrice() const { return price; }

  double getWeight() const { return weight; }

  const std::string& getName() const { return name; }

  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
  virtual std::string getTypeName() const = 0;
};

class Weapon : public MagicItem {
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int d)
      : MagicItem(n, p, w), damage(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }

  std::string getTypeName() const override { return "Оружие"; }
};

class Armor : public MagicItem {
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int d)
      : MagicItem(n, p, w), defense(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return defense;
  }

  std::string getTypeName() const override { return "Броня"; }
};

class Potion : public MagicItem {
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double d)
      : MagicItem(n, p, w), duration(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }

  std::string getTypeName() const override { return "Зелье"; }
};

class Scroll : public MagicItem {
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& e)
      : MagicItem(n, p, w), effect(e) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }

  std::string getTypeName() const override { return "Свиток"; }
};
