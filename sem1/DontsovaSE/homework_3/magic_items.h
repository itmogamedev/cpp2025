#ifndef MAGIC_ITEMS_H_
#define MAGIC_ITEMS_H_

#include <string>
#include <variant>
#include <vector>
#include <map>

using SpecificParam = std::variant<int, double, std::string>;

class MagicItem {
protected:
    std::string name;
    double price;
    double weight;

public:
    MagicItem(const std::string& name, double price, double weight);
    virtual ~MagicItem() = default;
    
    virtual std::string getType() const = 0;
    virtual SpecificParam getSpecificParam() const = 0;
    
    std::string getName() const;
    double getPrice() const;
    double getWeight() const;
};

class Weapon : public MagicItem {
private:
    int damage;

public:
    Weapon(const std::string& name, double price, double weight, int damage);
    
    std::string getType() const override;
    SpecificParam getSpecificParam() const override;
    int getDamage() const;
};

class Armor : public MagicItem {
private:
    int defense;

public:
    Armor(const std::string& name, double price, double weight, int defense);
    
    std::string getType() const override;
    SpecificParam getSpecificParam() const override;
    int getDefense() const;
};

class Potion : public MagicItem {
private:
    double duration;

public:
    Potion(const std::string& name, double price, double weight, 
           double duration);
    
    std::string getType() const override;
    SpecificParam getSpecificParam() const override;
    double getDuration() const;
};

class Scroll : public MagicItem {
private:
    std::string effect;

public:
    Scroll(const std::string& name, double price, double weight,
           const std::string& effect);
    
    std::string getType() const override;
    SpecificParam getSpecificParam() const override;
    std::string getEffect() const;
};

class Shop {
private:
    std::string shop_name;
    std::vector<MagicItem*> items;

public:
    Shop(const std::string& name);
    ~Shop();
    
    void addItem(MagicItem* item);
    std::string getName() const;
    const std::vector<MagicItem*>& getItems() const;
    
    double calculateAveragePrice() const;
    double calculateAverageWeight() const;
    void analyzeSpecificParams() const;
};

#endif