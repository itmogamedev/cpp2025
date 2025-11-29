#ifndef MAGIC_ITEM_H
#define MAGIC_ITEM_H

#include <string>
#include <variant>

class MagicItem {
public:
	MagicItem(const std::string& item_name, int item_price, double item_weight);
	virtual ~MagicItem() = default;

	virtual std::variant<int, double, std::string> getSpecParam() const = 0;

	std::string name() const { return name; }
	int price() const { return price; }
	double weight() const { return weight; }

private:
	std::string name;
	int price;
	double weight;
};

#endif  // MAGIC_ITEM_H