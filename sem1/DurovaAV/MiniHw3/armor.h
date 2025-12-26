#pragma once

#include "MagicItem.h"

class Armor : public MagicItem {
private:
	int defense;

public:
	Armor(const std::string& name, int price, double weight, int defense);
	std::variant<int, double, std::string> getSpecParam() const override;
};