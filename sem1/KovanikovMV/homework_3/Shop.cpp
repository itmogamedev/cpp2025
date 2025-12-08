#include "Shop.h"

#include <map>
void Shop::addItem(const std::string& type, const std::string& name, int price,
                   double weight, const std::string& specParam) {
  if (type == "Оружие")
    items_container.push_back(
        new Weapon(name, price, weight, std::stoi(specParam)));
  else if (type == "Броня")
    items_container.push_back(
        new Armor(name, price, weight, std::stoi(specParam)));
  else if (type == "Зелье")
    items_container.push_back(
        new Potion(name, price, weight, std::stod(specParam)));
  else if (type == "Свиток")
    items_container.push_back(new Scroll(name, price, weight, specParam));
}
double Shop::avgPrice() {
  int totalPrice = 0;
  for (auto item : items_container) {
    totalPrice += item->getPrice();
  }
  return totalPrice / getItemsAmount();
}

double Shop::avgWeight() {
  double totalWeight = 0;
  for (auto item : items_container) {
    totalWeight += item->getWeight();
  }
  return totalWeight / getItemsAmount();
}

double Shop::avgParam(const std::string& type) {
  double totalParam = 0;
  int typeCount = 0;
  for (auto item : items_container) {
    if (item->getType() == type) {
      if (type == "Potion")
        totalParam += std::get<double>(item->getSpecialParam());
      else
        totalParam += std::get<int>(item->getSpecialParam());
      typeCount++;
    }
  }
  if (typeCount == 0) return 0;
  return totalParam / typeCount;
}
std::string Shop::avgScroll() {
  std::map<std::string, int> spellFrequency;
  for (auto item : items_container) {
    if (item->getType() == "Scroll") {
      std::string spellName = std::get<std::string>(item->getSpecialParam());
      spellFrequency[spellName]++;
    }
  }
  if (spellFrequency.empty())
    return "";
  else {
    int maxCount = 0;
    std::string maxSpell;
    for (const auto& [spell, count] : spellFrequency) {
      if (maxCount < count) {
        maxCount = count;
        maxSpell = spell;
      }
    }
    return maxSpell;
  }
}
