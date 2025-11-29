#ifndef DERIVEDITEMS_H
#define DERIVEDITEMS_H

#include "MagicItem.h"
#include <string>

class Weapon : public MagicItem {
  private:
    int damage;

  public:
    Weapon(const std::string& name, int price, double weight, int damage);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

class Armor : public MagicItem {
  private:
    int defense;

  public:
    Armor(const std::string& name, int price, double weight, int defense);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

class Brace : public MagicItem {
  private:
    std::string effect;

  public:
    Brace(const std::string& name, int price, double weight, const std::string& effect);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

class Mushroom : public MagicItem {
  private:
    std::string roaring;

  public:
    Mushroom(const std::string& name, int price, double weight, const std::string& roaring);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

#endif