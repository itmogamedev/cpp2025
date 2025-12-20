#ifndef SHOP_H
#define SHOP_H

#include <memory>
#include <string>
#include <vector>
#include "magic_item.h"

class Shop {
public:
	explicit Shop(const std::string& shop_name);
	void addItem(std::unique_ptr<MagicItem> item);
	void printReport() const;

private:
	std::string name_;
	std::vector<std::unique_ptr<MagicItem>> items_;

	double calculateAveragePrice() const;
	double calculateAverageWeight() const;
	void printItemStats() const;
};

#endif  // SHOP_H