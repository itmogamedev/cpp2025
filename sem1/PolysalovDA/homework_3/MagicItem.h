#ifndef MAGICITEM_H
#define MAGICITEM_H

#include <string>
#include <variant>

class MagicItem {
  protected:
    std::string name;
    int price;
    double weight;

  public:
    MagicItem(const std::string& name, int price, double weight);
    virtual ~MagicItem() = default;

    virtual std::variant<int, double, std::string> getSpecParam() const = 0;

    std::string getName() const;
    int getPrice() const;
    double getWeight() const;

    virtual std::string getType() const = 0;
};

#endif