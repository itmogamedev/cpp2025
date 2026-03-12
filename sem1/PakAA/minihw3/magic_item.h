#ifndef MAGIC_ITEM_H
#define MAGIC_ITEM_H

#include <string>

class MagicItem {
public:
	MagicItem(const std::string& item_name, int item_price, double item_weight);
	virtual ~MagicItem() = default;

	// Виртуальный метод для получения специального параметра
	virtual std::string getSpecialParam() const = 0;

	// Геттеры с разными именами, чтобы избежать конфликта
	std::string getName() const;
	int getPrice() const;
	double getWeight() const;

protected:
	std::string name_;
	int price_;
	double weight_;
};

#endif  // MAGIC_ITEM_H