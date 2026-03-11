#ifndef MAGICITEM_H
#define MAGICITEM_H

#include <string>

class magicItem {
protected:
    std::string name;
    int price;
    double weight;

public:
    magicItem(const std::string& item_Name, int item_Price, double item_Weight);
    virtual ~magicItem() = default;

    virtual std::string getType() const = 0;
    virtual int getIntParam() const = 0;
    virtual double getDoubleParam() const = 0;
    virtual std::string getStringParam() const = 0;

    std::string getName() const;
    int getPrice() const;
    double getWeight() const;
};

#endif