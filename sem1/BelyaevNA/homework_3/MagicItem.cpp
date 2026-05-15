#include "MagicItem.h"

#include <algorithm>
#include <iostream>

MagicItem::MagicItem(const std::string& n, int p, double w)
    : name(n), price(p), weight(w) {}

std::string MagicItem::getName() const { return name; }

int MagicItem::getPrice() const { return price; }

double MagicItem::getWeight() const { return weight; }

Weapon::Weapon(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), damage(d) {}

std::string Weapon::getSpecParam() const { return std::to_string(damage); }

std::string Weapon::getType() const { return "Weapon"; }

int Weapon::getDamage() const { return damage; }

Armor::Armor(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), defense(d) {}

std::string Armor::getSpecParam() const { return std::to_string(defense); }

std::string Armor::getType() const { return "Armor"; }

int Armor::getDefense() const { return defense; }

Potion::Potion(const std::string& n, int p, double w, double d)
    : MagicItem(n, p, w), duration(d) {}

std::string Potion::getSpecParam() const { return std::to_string(duration); }

std::string Potion::getType() const { return "Potion"; }

double Potion::getDuration() const { return duration; }

Scroll::Scroll(const std::string& n, int p, double w, const std::string& e)
    : MagicItem(n, p, w), effect(e) {}

std::string Scroll::getSpecParam() const { return effect; }

std::string Scroll::getType() const { return "Scroll"; }

std::string Scroll::getEffect() const { return effect; }

Shop::Shop(const std::string& n) : name(n) {}

void Shop::addItem(std::unique_ptr<MagicItem> item) {
  items.push_back(std::move(item));
}

void Shop::analyzeShop() const {
  std::cout << "=== Shop: " << name << " ===" << std::endl;
  std::cout << "Total items: " << items.size() << std::endl;

  double totalPrice = 0, totalWeight = 0;

  std::vector<int> weaponParams;
  std::vector<int> armorParams;
  std::vector<double> potionParams;
  std::vector<std::string> scrollParams;

  for (const auto& item : items) {
    totalPrice += item->getPrice();
    totalWeight += item->getWeight();

    std::string type = item->getType();
    if (type == "Weapon") {
      Weapon* weapon = static_cast<Weapon*>(item.get());
      weaponParams.push_back(weapon->getDamage());
    } else if (type == "Armor") {
      Armor* armor = static_cast<Armor*>(item.get());
      armorParams.push_back(armor->getDefense());
    } else if (type == "Potion") {
      Potion* potion = static_cast<Potion*>(item.get());
      potionParams.push_back(potion->getDuration());
    } else if (type == "Scroll") {
      Scroll* scroll = static_cast<Scroll*>(item.get());
      scrollParams.push_back(scroll->getEffect());
    }
  }

  if (items.size() > 0) {
    std::cout << "Average price: " << totalPrice / items.size() << " gold"
              << std::endl;
    std::cout << "Average weight: " << totalWeight / items.size() << " kg"
              << std::endl;
  }

  std::cout << "\nItem statistics:" << std::endl;

  if (weaponParams.empty()) {
    std::cout << "- Weapon: not available" << std::endl;
  } else {
    int sum = 0;
    for (int damage : weaponParams) sum += damage;
    std::cout << "- Weapon: average damage = " << sum / weaponParams.size()
              << std::endl;
  }

  if (armorParams.empty()) {
    std::cout << "- Armor: not available" << std::endl;
  } else {
    int sum = 0;
    for (int defense : armorParams) sum += defense;
    std::cout << "- Armor: average defense = " << sum / armorParams.size()
              << std::endl;
  }

  if (potionParams.empty()) {
    std::cout << "- Potion: not available" << std::endl;
  } else {
    double sum = 0;
    for (double duration : potionParams) sum += duration;
    std::cout << "- Potion: average duration = " << sum / potionParams.size()
              << std::endl;
  }

  if (scrollParams.empty()) {
    std::cout << "- Scroll: not available" << std::endl;
  } else {
    std::map<std::string, int> effectCount;
    for (const auto& effect : scrollParams) {
      effectCount[effect]++;
    }
    std::string mostCommonEffect;
    int maxCount = 0;
    for (const auto& pair : effectCount) {
      if (pair.second > maxCount) {
        maxCount = pair.second;
        mostCommonEffect = pair.first;
      }
    }
    std::cout << "- Scroll: most common effect '" << mostCommonEffect << "'"
              << std::endl;
  }
  std::cout << std::endl;
}
