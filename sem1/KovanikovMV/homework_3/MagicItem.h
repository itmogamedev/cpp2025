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
      : name(n), price(p), weight(w) {};
  std::string getName() { return name; }
  int getPrice() { return price; }
  double getWeight() { return weight; }
  virtual std::variant<int, double, std::string> getSpecialParam() = 0;
  virtual std::string getType() = 0;
  virtual ~MagicItem() = default;
};

class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int dmg)
      : MagicItem(n, p, w), damage(dmg) {};
  std::string getType() override { return "Weapon"; }
  std::variant<int, double, std::string> getSpecialParam() override {
    return damage;
  }
};

class Armor : public MagicItem {
 private:
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int def)
      : MagicItem(n, p, w), defense(def) {};
  std::string getType() override { return "Armor"; }
  std::variant<int, double, std::string> getSpecialParam() override {
    return defense;
  }
};

class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double dur)
      : MagicItem(n, p, w), duration(dur) {};
  std::string getType() override { return "Potion"; }
  std::variant<int, double, std::string> getSpecialParam() override {
    return duration;
  }
};

class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& eff)
      : MagicItem(n, p, w), effect(eff) {};
  std::string getType() override { return "Scroll"; }
  std::variant<int, double, std::string> getSpecialParam() override {
    return effect;
  }
};
