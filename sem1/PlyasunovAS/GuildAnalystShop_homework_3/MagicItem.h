#ifndef MAGIC_ITEM_H
#define MAGIC_ITEM_H

#include <string>

class MagicItem {
protected:
	std::string name;
	int price;
	double weight;

public:
	MagicItem(const std::string& itemName, int itemPrice, double itemWeight);
	virtual ~MagicItem() = default;

	virtual std::string getSpecParam() const = 0;

	std::string getName() const;
	int getPrice() const;
	double getWeight() const;
};

#endif