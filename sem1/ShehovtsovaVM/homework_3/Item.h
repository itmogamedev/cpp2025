#include <iostream>
#include <variant>
#include <vector>
class MagicItem {
  public:
   std::string name;
   int price;
   double weight;
   virtual std::variant<int, double, std::string> getSpecParam() = 0;
};
class Weapon : MagicItem {
 public:
  Weapon(std::string _name, int _price, double _weight, int _damage) {
    name = _name;
    price = _price;
    weight = _weight;
    damage = _damage;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return damage;
  }
  int getPrice() { return price;}
  double getWeight() { return weight; }
 private:
  int damage;
};

class Armor : MagicItem {
 public:
  Armor(std::string _name, int _price, double _weight, int _defense) {
    name = _name;
    price = _price;
    weight = _weight;
    defense = _defense;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return defense;
  }
  int getPrice() { return price; }
  double getWeight() { return weight; }
 private:
  int defense;
};

class Potion : MagicItem {
 public:
  Potion(std::string _name, int _price, double _weight, double _duration) {
    name = _name;
    price = _price;
    weight = _weight;
    duration = _duration;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return duration;
  }
  int getPrice() { return price; }
  double getWeight() { return weight; }
 private:
  double duration;
};

class Scroll : MagicItem {
 public:
  Scroll(std::string _name, int _price, double _weight, std::string _effect) {
    name = _name;
    price = _price;
    weight = _weight;
    effect = _effect;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return effect; }
  int getPrice() { return price; }
  double getWeight() { return weight; }
 private:
  std::string effect;
};
