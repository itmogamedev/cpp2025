#pragma once

#include <string>
#include <variant>

using SpecialParam = std::variant<int, double, std::string>;

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;
  void parseCommonFields(std::string data);

 public:
  MagicItem(std::string data);
  virtual ~MagicItem() = default;

  virtual SpecialParam getSpecParam() = 0;
  virtual std::string getType() = 0;

  std::string getName();
  int getPrice();
  double getWeight();
};

class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(std::string data);
  SpecialParam getSpecParam() override;
  std::string getType() override;
};

class Armor : public MagicItem {
 private:
  int defense;

 public:
  Armor(std::string data);
  SpecialParam getSpecParam() override;
  std::string getType() override;
};

class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(std::string data);
  SpecialParam getSpecParam() override;
  std::string getType() override;
};

class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(std::string data);
  SpecialParam getSpecParam() override;
  std::string getType() override;
};
