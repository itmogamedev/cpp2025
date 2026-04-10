#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

enum ITEM_TYPES {
  TYPE_NONE,

  TYPE_INT,
  WEAPON,
  DEVICE,
  AMMO,

  TYPE_STRING,
  GOODS
};

class MagicItem {
 protected:
  ITEM_TYPES type = ITEM_TYPES::TYPE_NONE;

 public:
  std::string name;
  int price = 0;
  int weight = 0;

  MagicItem(std::stringstream &line) {
    line >> name;
    line >> price;
    line >> weight;
  }

  ITEM_TYPES getType() { return type; }

  virtual std::variant<int, std::string> getSpecific() = 0;
};

class Weapon : public MagicItem {
 private:
  int damage = 0;

 public:
  Weapon(std::stringstream &line) : MagicItem(line) {
    line >> damage;
    type = ITEM_TYPES::WEAPON;
  }

  std::variant<int, std::string> getSpecific() override { return damage; }
};

class Device : public MagicItem {
 private:
  int duration = 0;

 public:
  Device(std::stringstream &line) : MagicItem(line) {
    line >> duration;
    type = ITEM_TYPES::DEVICE;
  }

  std::variant<int, std::string> getSpecific() override { return duration; }
};

class Ammo : public MagicItem {
 private:
  int quantity = 0;

 public:
  Ammo(std::stringstream &line) : MagicItem(line) {
    line >> quantity;
    type = ITEM_TYPES::AMMO;
  }

  std::variant<int, std::string> getSpecific() override { return quantity; }
};

class Goods : public MagicItem {
 private:
  std::string deliveryPlace;

 public:
  Goods(std::stringstream &line) : MagicItem(line) {
    line >> deliveryPlace;
    type = ITEM_TYPES::GOODS;
  }

  std::variant<int, std::string> getSpecific() override {
    return deliveryPlace;
  }
};

class Shop {
 private:
  std::vector<MagicItem *> items;

 public:
  std::string name;

  Shop(std::string name) { this->name = name; }

  void add(MagicItem *item) { items.push_back(item); }

  std::size_t size() { return items.size(); }

  float meanPrice() {
    if (size() == 0) {
      return 0;
    }

    float mean = 0;

    for (auto it : items) {
      mean += it->price;
    }

    return mean / size();
  }

  float meanWeight() {
    if (size() == 0) {
      return 0;
    }

    float mean = 0;

    for (auto it : items) {
      mean += it->weight;
    }

    return mean / size();
  }

  std::string meanSpecific(ITEM_TYPES type) {
    if (ITEM_TYPES::TYPE_INT < type && type < ITEM_TYPES::TYPE_STRING) {
      float mean = 0;
      int size = 0;

      for (auto it : items) {
        if (it->getType() == type) {
          mean += std::get<int>(it->getSpecific());
          size++;
        }
      }

      if (size == 0) {
        return "No items found";
      }

      return std::to_string(mean / size);
    } else if (ITEM_TYPES::TYPE_STRING < type) {
      std::map<std::string, int> counter;

      for (auto it : items) {
        if (it->getType() == type) {
          std::string item = std::get<std::string>(it->getSpecific());
          counter[item]++;
        }
      }

      if (counter.size() == 0) {
        return "No items found";
      }

      return counter.begin()->first;
    }

    return "No items found";
  }
};

int main() {
  std::ifstream file("shop.txt");

  std::vector<Shop> shops;
  MagicItem *item;
  bool commentFlag = false;
  for (std::string line; std::getline(file, line);) {
    std::stringstream streamline(line);
    std::string token;
    streamline >> token;

    if (commentFlag) {
      if (token == "*/") {
        commentFlag = false;
      }
      continue;
    }
    if (token == "/*") {
      commentFlag = true;
      continue;
    }
    if (token.length() == 0) {
      continue;
    }

    if (token == "Weapon") {
      item = new Weapon(streamline);
    } else if (token == "Device") {
      item = new Device(streamline);
    } else if (token == "Ammo") {
      item = new Ammo(streamline);
    } else if (token == "Goods") {
      item = new Goods(streamline);
    } else {
      shops.push_back(Shop(token));
      continue;
    }

    shops.back().add(item);
  }

  for (auto shop : shops) {
    std::cout << "=== Shop: " << shop.name << " ===\n";
    std::cout << "Number of items: " << shop.size() << "\n";
    std::cout << "Mean price: " << shop.meanPrice() << "\n";
    std::cout << "Mean weight: " << shop.meanWeight() << "\n";

    std::cout << "\n";

    std::cout << "Items statistics:\n";
    std::cout << "Weapon damage: " << shop.meanSpecific(ITEM_TYPES::WEAPON)
              << "\n";
    std::cout << "Device duration: " << shop.meanSpecific(ITEM_TYPES::DEVICE)
              << "\n";
    std::cout << "Ammo quantity: " << shop.meanSpecific(ITEM_TYPES::AMMO)
              << "\n";
    std::cout << "Goods most common delivery place: "
              << shop.meanSpecific(ITEM_TYPES::GOODS) << "\n";

    std::cout << "\n" << std::endl;
  }

  return 0;
}