#ifndef MAGICITEM_H_
#define MAGICITEM_H_

#include <string>
#include <sstream>
#include <variant>

using SpecialParam = std::variant<int, double, std::string>;

enum ItemType {
  kWeapon,
  kArmor,
  kPotion,
  kScroll
};

class MagicItem {
 public: 
  MagicItem(const std::string& n, int p, double w)
    :name(n), price(p), weight(w) {}
  
  std::string get_name() { return name; }
  int get_price() {return price; }
  double get_weight() { return weight; }

  virtual SpecialParam get_special_param() = 0;

  virtual ItemType get_type() = 0;

  virtual ~MagicItem() = default;

 protected:
  std::string name;
  int         price;
  double      weight;
};

class Weapon : public MagicItem {
 public:
  Weapon(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), damage(d)  {}

  ItemType get_type() override { return kWeapon; }

  SpecialParam get_special_param() override {
    return damage;
  }

 private:
  int damage;
};

class Armor : public MagicItem {
 public:
  Armor(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), defence(d)  {}

  ItemType get_type() override { return kArmor; }

  SpecialParam get_special_param() override {
    return defence;
  }

 private:
  int defence;
};

class Potion : public MagicItem {
 public:
  Potion(const std::string& n, int p, double w, double d)
    : MagicItem(n, p, w), duration(d)  {}

  ItemType get_type() override { return kPotion; }

  SpecialParam get_special_param() override {
    return duration;
  }

 private:
  double duration;
};

class Scroll : public MagicItem {
 public:
  Scroll(const std::string& n, int p, double w, std::string& e)
    : MagicItem(n, p, w), effect(e)  {}

  ItemType get_type() override { return kScroll; }

  SpecialParam get_special_param() override {
    return effect;
  }

 private:
  std::string effect;
};

MagicItem* ProcessItem(std::string, std::stringstream*);

#endif // MAGICITEM_H_