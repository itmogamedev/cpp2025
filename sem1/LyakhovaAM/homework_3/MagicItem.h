#pragma once
#include <iostream>
#include <variant>

class MagicItem {
 private:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(std::string name, int price, double weight)
      : name(name), price(price), weight(weight) {}
  virtual std::variant<int, double, std::string> getSpecParam() = 0;
  virtual std::string getType() = 0;
  std::string getName() { return name; }
  int getPrice() { return price; }
  double getWeight() { return weight; }
};

class Weapon : public MagicItem {
  int damage;

 public:
  Weapon(std::string name, int price, double weight, int damage)
      : MagicItem(name, price, weight), damage(damage) {}
  std::variant<int, double, std::string> getSpecParam() { return damage; }
  std::string getType() { return "Weapon"; }
};

class Armor : public MagicItem {
  int defense;

 public:
  Armor(std::string name, int price, double weight, int defense)
      : MagicItem(name, price, weight), defense(defense) {}
  std::variant<int, double, std::string> getSpecParam() { return defense; }
  std::string getType() { return "Armor"; }
};

class Potion : public MagicItem {
  double duration;

 public:
  Potion(std::string name, int price, double weight, double duration)
      : MagicItem(name, price, weight), duration(duration) {}
  std::variant<int, double, std::string> getSpecParam() { return duration; }
  std::string getType() { return "Potion"; }
};

class Scroll : public MagicItem {
  std::string effect;

 public:
  Scroll(std::string name, int price, double weight, std::string effect)
      : MagicItem(name, price, weight), effect(effect) {}
  std::variant<int, double, std::string> getSpecParam() { return effect; }
  std::string getType() { return "Scroll"; }
};
