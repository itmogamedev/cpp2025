#include <iostream>
#include <string>
#include <variant>
#include <vector>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  virtual ~MagicItem() = default;
  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
};

class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(const std::string& NAME, int PRICE, double WEIGHT, int DAMAGE) {
    name = NAME;
    price = PRICE;
    weight = WEIGHT;
    damage = DAMAGE;
  }

  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }
};

class Armor : public MagicItem {
 private:
  int defence;

 public:
  Armor(const std::string& NAME, int PRICE, double WEIGHT, int DEFENCE) {
    name = NAME;
    price = PRICE;
    weight = WEIGHT;
    defence = DEFENCE;
  }

  std::variant<int, double, std::string> getSpecParam() const override {
    return defence;
  }
};

class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(const std::string& NAME, int PRICE, double WEIGHT, int DURATION) {
    name = NAME;
    price = PRICE;
    weight = WEIGHT;
    duration = DURATION;
  }
  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }
};

class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(const std::string& NAME, int PRICE, double WEIGHT,
         std::string EFFECT) {
    name = NAME;
    price = PRICE;
    weight = WEIGHT;
    effect = EFFECT;
  }
  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }
};