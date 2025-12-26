#include "Armor.h"

Armor::Armor(const std::string& name, int price, double weight, int defense) {
	this->name = name;
	this->price = price;
	this->weight = weight;
	this->defense = defense;
}

std::variant<int, double, std::string> Armor::getSpecParam() const {
	return defense;
}