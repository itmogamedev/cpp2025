#include "MagicItems.h"

#include <sstream>
#include <string>

void MagicItem::parseCommonFields(std::string data) {
  std::istringstream iss(data);
  std::string temp;
  iss >> temp >> name >> price >> weight;
}

MagicItem::MagicItem(std::string data) { parseCommonFields(data); }

std::string MagicItem::getName() { return name; }

int MagicItem::getPrice() { return price; }

double MagicItem::getWeight() { return weight; }

Weapon::Weapon(std::string data) : MagicItem(data) {
  std::istringstream iss(data);
  std::string temp;
  iss >> temp >> temp >> temp >> temp;
  iss >> damage;
}

SpecialParam Weapon::getSpecParam() { return damage; }

std::string Weapon::getType() { return "Оружие"; }

Armor::Armor(std::string data) : MagicItem(data) {
  std::istringstream iss(data);
  std::string temp;
  iss >> temp >> temp >> temp >> temp;
  iss >> defense;
}

SpecialParam Armor::getSpecParam() { return defense; }

std::string Armor::getType() { return "Броня"; }

Potion::Potion(std::string data) : MagicItem(data) {
  std::istringstream iss(data);
  std::string temp;
  iss >> temp >> temp >> temp >> temp;
  iss >> duration;
}

SpecialParam Potion::getSpecParam() { return duration; }

std::string Potion::getType() { return "Зелье"; }

Scroll::Scroll(std::string data) : MagicItem(data) {
  std::istringstream iss(data);
  std::string temp;
  iss >> temp >> temp >> temp >> temp;
  iss >> effect;
}

SpecialParam Scroll::getSpecParam() { return effect; }

std::string Scroll::getType() { return "Свиток"; }
