#pragma once


#include <string>
#include <variant>
#include <memory>

class MagicItem {
protected:
    std::string name;
    int price;
    double weight;

public:
    MagicItem(std::string name, int price, double weight);
    virtual ~MagicItem() = default;

    virtual std::variant<int, double, std::string> getSpecParam() const = 0;
    virtual std::string getTypeName() const = 0;

    int getPrice() const;
    double getWeight() const;
};

class Weapon : public MagicItem {
    int damage;

public:
    Weapon(std::string name, int price, double weight, int damage);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getTypeName() const override;
};

class Armor : public MagicItem {
    int defense;

public:
    Armor(std::string name, int price, double weight, int defense);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getTypeName() const override;
};

class Potion : public MagicItem {
    double duration;

public:
    Potion(std::string name, int price, double weight, double duration);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getTypeName() const override;
};

class Scroll : public MagicItem {
    std::string effect;

public:
    Scroll(std::string name, int price, double weight, std::string effect);
    std::variant<int, double, std::string> getSpecParam() const override;
    std::string getTypeName() const override;
};

