#ifndef MAGICITEM_H
#define MAGICITEM_H

#include <string>

class MagicItem {
protected:
    std::string name;
    int price;
    double weight;

public:
    MagicItem(const std::string& itemName, int itemPrice, double itemWeight);
    virtual ~MagicItem() = default;

    virtual std::string getType() const = 0;
    virtual int getIntParam() const = 0;
    virtual double getDoubleParam() const = 0;
    virtual std::string getStringParam() const = 0;

    std::string getName() const;
    int getPrice() const;
    double getWeight() const;
};

#endif