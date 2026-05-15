#pragma once

#include <string>
#include <variant>

using SpecParam = std::variant<int, double, std::string>;

class MagicItem {
 public:
  MagicItem(const std::string name, int price, double weight);
  virtual ~MagicItem() = default;

  const std::string& getName() const;
  int getPrice() const;
  double getWeight() const;

  virtual SpecParam getSpecParam() const = 0;
  virtual std::string getTypeName() const = 0;

 protected:
  std::string name;
  int price;
  double weight;
};

class Weapon : public MagicItem {
 public:
  Weapon(const std::string& name, int price, double weight, int damage);

  SpecParam getSpecParam() const override;
  std::string getTypeName() const override;

 private:
  int damage;
};

class Armor : public MagicItem {
 public:
  Armor(const std::string& name, int price, double weight, int defense);

  SpecParam getSpecParam() const override;
  std::string getTypeName() const override;

 private:
  int defense;
};

class Potion : public MagicItem {
 public:
  Potion(const std::string& name, int price, double weight, double duration);

  SpecParam getSpecParam() const override;
  std::string getTypeName() const override;

 private:
  double duration;
};

class Scroll : public MagicItem {
 public:
  Scroll(const std::string& name, int price, double weight,
         const std::string& effect);

  SpecParam getSpecParam() const override;
  std::string getTypeName() const override;

 private:
  std::string effect;
};
