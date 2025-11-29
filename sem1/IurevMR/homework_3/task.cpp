#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include <iomanip>
#include <map>
#include <algorithm>
#include <numeric>

using SpecParam = std::variant<int, double, std::string>;

class MagicItem {
protected:
  std::string name;
  int price;
  double weight;

public:
  MagicItem(std::string n, int p, double w) : name(n), price(p), weight(w) {}
  virtual ~MagicItem() = default;

  int getPrice() const { return price; }
  double getWeight() const { return weight; }
  std::string getName() const { return name; }

  virtual SpecParam getSpecParam() const = 0;
  virtual std::string getType() const = 0;
};

class Weapon : public MagicItem {
  int damage;
public:
  Weapon(std::string n, int p, double w, int d) : MagicItem(n, p, w), damage(d) {}
  
  SpecParam getSpecParam() const override {
    return damage;
  }
  std::string getType() const override { return "Weapon"; }
};

class Armor : public MagicItem {
  int defense;
public:
  Armor(std::string n, int p, double w, int def) : MagicItem(n, p, w), defense(def) {}
  
  SpecParam getSpecParam() const override {
    return defense;
  }
  std::string getType() const override { return "Armor"; }
};

class Potion : public MagicItem {
  double duration;
public:
  Potion(std::string n, int p, double w, double dur) : MagicItem(n, p, w), duration(dur) {}
  
  SpecParam getSpecParam() const override {
    return duration;
  }
  std::string getType() const override { return "Potion"; }
};

class Scroll : public MagicItem {
  std::string effect;
public:
  Scroll(std::string n, int p, double w, std::string eff) : MagicItem(n, p, w), effect(eff) {}
  
  SpecParam getSpecParam() const override {
    return effect;
  }
  std::string getType() const override { return "Scroll"; }
};

struct Shop {
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;
};

std::string findMostFrequentString(const std::vector<std::string>& vec) {
  if (vec.empty()) return "";
  std::map<std::string, int> counts;
  for (const auto& s : vec) {
    counts[s]++;
  }
  
  std::string bestString;
  int maxCount = -1;
  
  for (const auto& pair : counts) {
    if (pair.second > maxCount) {
      maxCount = pair.second;
      bestString = pair.first;
    }
  }
  return bestString;
}

void analyzeShop(const Shop& shop) {
  std::cout << "=== Shop: " << shop.name << " ===" << std::endl;
  
  if (shop.items.empty()) {
    std::cout << "Shop is empty." << std::endl << std::endl;
    return;
  }

  double totalWeight = 0;
  long long totalPrice = 0;

  std::vector<int> weaponDamages;
  std::vector<int> armorDefenses;
  std::vector<double> potionDurations;
  std::vector<std::string> scrollEffects;

  for (const auto& item : shop.items) {
    totalPrice += item->getPrice();
    totalWeight += item->getWeight();

    SpecParam param = item->getSpecParam();
    std::string type = item->getType();

    if (type == "Weapon") {
      weaponDamages.push_back(std::get<int>(param));
    } else if (type == "Armor") {
      armorDefenses.push_back(std::get<int>(param));
    } else if (type == "Potion") {
      potionDurations.push_back(std::get<double>(param));
    } else if (type == "Scroll") {
      scrollEffects.push_back(std::get<std::string>(param));
    }
  }

  std::cout << "Total items: " << shop.items.size() << std::endl;
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Average price: " << (double)totalPrice / shop.items.size() << " gold" << std::endl;
  std::cout << "Average weight: " << totalWeight / shop.items.size() << " kg" << std::endl;

  std::cout << "\nItem Statistics:" << std::endl;

  if (!weaponDamages.empty()) {
    double avgDmg = std::accumulate(weaponDamages.begin(), weaponDamages.end(), 0.0) / weaponDamages.size();
    std::cout << "- Weapon: average damage = " << (int)avgDmg << std::endl;
  } else {
    std::cout << "- Weapon: not available" << std::endl;
  }

  if (!armorDefenses.empty()) {
    double avgDef = std::accumulate(armorDefenses.begin(), armorDefenses.end(), 0.0) / armorDefenses.size();
    std::cout << "- Armor: average defense = " << (int)avgDef << std::endl;
  } else {
    std::cout << "- Armor: not available" << std::endl;
  }

  if (!potionDurations.empty()) {
    double avgDur = std::accumulate(potionDurations.begin(), potionDurations.end(), 0.0) / potionDurations.size();
    std::cout << "- Potion: average duration = " << avgDur << std::endl;
  } else {
    std::cout << "- Potion: not available" << std::endl;
  }

  if (!scrollEffects.empty()) {
    std::string freqEffect = findMostFrequentString(scrollEffects);
    std::cout << "- Scroll: most frequent effect = " << freqEffect << std::endl;
  } else {
    std::cout << "- Scroll: not available" << std::endl;
  }
  
  std::cout << std::endl;
}

int main() {
  std::ifstream file("artifacts.txt");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open artifacts.txt" << std::endl;
    return 1;
  }

  std::vector<Shop> shops;
  std::string lineTag;

  while (file >> lineTag) {
    if (lineTag == "Shop:") {
      Shop currentShop;
      file >> currentShop.name;
      
      std::string itemsTag;
      file >> itemsTag;
      int count;
      file >> count;

      for (int i = 0; i < count; ++i) {
        std::string type, name;
        int price;
        double weight;
        
        file >> type >> name >> price >> weight;

        if (type == "Weapon") {
          int damage;
          file >> damage;
          currentShop.items.push_back(std::make_unique<Weapon>(name, price, weight, damage));
        } else if (type == "Armor") {
          int defense;
          file >> defense;
          currentShop.items.push_back(std::make_unique<Armor>(name, price, weight, defense));
        } else if (type == "Potion") {
          double duration;
          file >> duration;
          currentShop.items.push_back(std::make_unique<Potion>(name, price, weight, duration));
        } else if (type == "Scroll") {
          std::string effect;
          file >> effect;
          currentShop.items.push_back(std::make_unique<Scroll>(name, price, weight, effect));
        }
      }
      shops.push_back(std::move(currentShop));
    }
  }

  file.close();

  for (const auto& shop : shops) {
    analyzeShop(shop);
  }

  return 0;
}