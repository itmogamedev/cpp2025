#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>
#include <variant>
#include <vector>

class MagicItem {
 public:
  std::string name;
  int price;
  double weight;

  MagicItem(std::string n, int p, double w) : name(n), price(p), weight(w) {}
  virtual ~MagicItem() = default;

  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
};

class Weapon : public MagicItem {
 public:
  int damage;

  Weapon(std::string n, int p, double w, int d)
      : MagicItem(n, p, w), damage(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }
};

class Armor : public MagicItem {
 public:
  int defense;

  Armor(std::string n, int p, double w, int d)
      : MagicItem(n, p, w), defense(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return defense;
  }
};

class Potion : public MagicItem {
 public:
  double duration;

  Potion(std::string n, int p, double w, double d)
      : MagicItem(n, p, w), duration(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }
};

class Scroll : public MagicItem {
 public:
  std::string effect;

  Scroll(std::string n, int p, double w, std::string e)
      : MagicItem(n, p, w), effect(e) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }
};

struct Shop {
  std::string name;
  std::vector<std::shared_ptr<MagicItem>> items;
};

std::vector<Shop> readDataFromFile(const std::string& filename) {
  std::ifstream file(filename);
  std::vector<Shop> shops;
  std::string line;

  while (std::getline(file, line)) {
    if (line.rfind("Shop: ", 0) == 0) {
      std::string shopName = line.substr(line.find(":") + 2);

      std::getline(file, line);
      int numItems = std::stoi(line.substr(line.find(":") + 2));

      Shop shop;
      shop.name = shopName;

      for (int i = 0; i < numItems; i++) {
        std::getline(file, line);
        std::stringstream ss(line);

        std::string type, name;
        int price;
        double weight;

        ss >> type >> name >> price >> weight;

        if (type == "Weapon") {
          int damage;
          ss >> damage;
          shop.items.push_back(
              std::make_shared<Weapon>(name, price, weight, damage));
        } else if (type == "Armor") {
          int defense;
          ss >> defense;
          shop.items.push_back(
              std::make_shared<Armor>(name, price, weight, defense));
        } else if (type == "Potion") {
          double duration;
          ss >> duration;
          shop.items.push_back(
              std::make_shared<Potion>(name, price, weight, duration));
        } else if (type == "Scroll") {
          std::string effect;
          ss >> effect;
          shop.items.push_back(
              std::make_shared<Scroll>(name, price, weight, effect));
        }
      }
      shops.push_back(shop);
    }
  }
  return shops;
}

void printShopStats(const Shop& shop) {
  std::cout << "\n=== Shop: " << shop.name << " ===\n";
  std::cout << "Items: " << shop.items.size() << "\n";

  double totalPrice = 0;
  double totalWeight = 0;

  std::map<std::string, std::vector<std::variant<int, double, std::string>>>
      stats;

  for (const auto& item : shop.items) {
    totalPrice += item->price;
    totalWeight += item->weight;

    std::string type;
    if (dynamic_cast<Weapon*>(item.get()))
      type = "Weapon";
    else if (dynamic_cast<Armor*>(item.get()))
      type = "Armor";
    else if (dynamic_cast<Potion*>(item.get()))
      type = "Potion";
    else if (dynamic_cast<Scroll*>(item.get()))
      type = "Scroll";

    stats[type].push_back(item->getSpecParam());
  }

  std::cout << "Average price: " << totalPrice / shop.items.size();
  std::cout << " Average weight: " << totalWeight / shop.items.size() << "\n";

  std::cout << "Item Stats:\n";

  if (stats["Weapon"].empty()) {
    std::cout << "- Weapon: out of stock\n";
  } else {
    int sum = 0;
    for (const auto& v : stats["Weapon"]) sum += std::get<int>(v);
    std::cout << "- Weapon: average damage = " << sum / stats["Weapon"].size()
              << "\n";
  }

  if (stats["Armor"].empty()) {
    std::cout << "- Armor: out of stock\n";
  } else {
    int sum = 0;
    for (const auto& v : stats["Armor"]) sum += std::get<int>(v);
    std::cout << "- Armor: average defense = " << sum / stats["Armor"].size()
              << "\n";
  }

  if (stats["Potion"].empty()) {
    std::cout << "- Potion: out of stock\n";
  } else {
    double sum = 0;
    for (const auto& v : stats["Potion"]) sum += std::get<double>(v);
    std::cout << "- Potion: average duration = " << sum / stats["Potion"].size()
              << "\n";
  }

  if (stats["Scroll"].empty()) {
    std::cout << "- Scroll: out of stock\n";
  } else {
    std::map<std::string, int> freq;
    for (const auto& v : stats["Scroll"]) freq[std::get<std::string>(v)]++;

    std::string most;
    int best = 0;
    for (const auto& p : freq) {
      if (p.second > best) {
        most = p.first;
        best = p.second;
      }
    }
    std::cout << "- Scrolls: most common effect = " << most << "\n";
  }
}

int main() {
  std::vector<Shop> shops = readDataFromFile("shops.txt");

  for (const auto& shop : shops) {
    printShopStats(shop);
  }

  return 0;
}
