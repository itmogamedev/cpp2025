#ifndef MAGIC_ITEM_HPP
#define MAGIC_ITEM_HPP

#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

using SpecialParam = std::variant<int, double, std::string>;

// Abs class
class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& n, int p, double w);

  virtual SpecialParam getSpecParam() const = 0;
  virtual std::string getType() const = 0;

  // Getters
  std::string getName() const;
  int getPrice() const;
  double getWeight() const;
};

//
class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int d);
  SpecialParam getSpecParam() const override;
  std::string getType() const override;
};

//
class Armor : public MagicItem {
 private:
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int d);
  SpecialParam getSpecParam() const override;
  std::string getType() const override;
};

//
class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double d);
  SpecialParam getSpecParam() const override;
  std::string getType() const override;
};

//
class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& e);
  SpecialParam getSpecParam() const override;
  std::string getType() const override;
};

//
class MagicShop {
 private:
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;

 public:
  MagicShop(const std::string& n);
  void addItem(std::unique_ptr<MagicItem> item);
  double getAveragePrice() const;
  double getAverageWeight() const;
  void analyzeSpecialParams() const;
  void printReport() const;
};

// Funcs
std::unique_ptr<MagicItem> createItem(const std::string& type,
                                      const std::string& name, int price,
                                      double weight,
                                      const std::string& specParam);

std::vector<MagicShop> readShopsFromFile(const std::string& filename);

#endif
