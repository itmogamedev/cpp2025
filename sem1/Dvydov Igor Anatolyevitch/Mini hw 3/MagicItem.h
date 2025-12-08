#pragma once
#include <iostream>
#include <string>
class MagicItem {
 protected:
  std::string name;
  int price;
  int weight;

 public:
  virtual std::string getSpecialParm() const = 0;
  std::string getName();
  int getPrice();
  int getWeight();
  MagicItem(std::string name, int price, int weight);
};
class Weapon : public MagicItem {
 private:
  int damage;

 public:
  std::string getSpecialParm() const override;
  Weapon(std::string name, int price, int weight, int special);
};
class Armor : public MagicItem {
 private:
  int defense;

 public:
  std::string getSpecialParm() const override;
  Armor(std::string name, int price, int weight, int special);
};
class Posion : public MagicItem {
 private:
  double duration;

 public:
  std::string getSpecialParm() const override;
  Posion(std::string name, int price, int weight, double special);
};
class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  std::string getSpecialParm() const override;
  Scroll(std::string name, int price, int weight, std::string special);
};
