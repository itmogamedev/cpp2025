#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& n, int p, double w);
  virtual ~MagicItem() = default;

  virtual std::string getSpecParam() const = 0;
  virtual std::string getType() const = 0;

  std::string getName() const;
  int getPrice() const;
  double getWeight() const;
};

class Weapon : public MagicItem {
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int d);
  std::string getSpecParam() const override;
  std::string getType() const override;
  int getDamage() const;
};

class Armor : public MagicItem {
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int d);
  std::string getSpecParam() const override;
  std::string getType() const override;
  int getDefense() const;
};

class Potion : public MagicItem {
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double d);
  std::string getSpecParam() const override;
  std::string getType() const override;
  double getDuration() const;
};

class Scroll : public MagicItem {
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& e);
  std::string getSpecParam() const override;
  std::string getType() const override;
  std::string getEffect() const;
};

class Shop {
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;

 public:
  Shop(const std::string& n);
  void addItem(std::unique_ptr<MagicItem> item);
  void analyzeShop() const;
};
