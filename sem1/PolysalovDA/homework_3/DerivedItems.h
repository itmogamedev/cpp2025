#ifndef DERIVEDITEMS_H
#define DERIVEDITEMS_H

#include "MagicItem.h"
#include <string>

class Weapon : public MagicItem {
  private:
    int damage;

  public:
    Weapon(const std::string& n, int p, double w, int d);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

class Armor : public MagicItem {
  private:
    int defense;

  public:
    Armor(const std::string& n, int p, double w, int d);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

class Scroll : public MagicItem {
  private:
    std::string effect;

  public:
    Scroll(const std::string& n, int p, double w, const std::string& e);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

class Mushroom : public MagicItem {
  private:
    std::string potency;

  public:
    Mushroom(const std::string& n, int p, double w, const std::string& pot);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getType() const override;
};

#endif