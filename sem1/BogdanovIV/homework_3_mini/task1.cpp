#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

enum Types { kWeapone, kArmor, kScroll, kPotion };

class Item {
 public:
  Item(Types type, std::string& name, double cost, double weight)
      : type(type), name(name), cost(cost), weight(weight) {}
  virtual ~Item() = default;

  Types getType() const { return type; }
  double getCost() const { return cost; }
  double getWeight() const { return weight; }

  virtual std::string getSpecialParam() const = 0;

 private:
  Types type;
  std::string name;
  double cost, weight;
};

class Weapone : public Item {
 public:
  Weapone(std::string& name, double cost, double weight, int damage)
      : Item(kWeapone, name, cost, weight), damage(damage) {}

  std::string getSpecialParam() const { return std::to_string(damage); };

  int getDamage() const { return damage; }

 private:
  int damage;
};

class Armor : public Item {
 public:
  Armor(std::string& name, double cost, double weight, int defense)
      : Item(kArmor, name, cost, weight), defense(defense) {}

  std::string getSpecialParam() const { return std::to_string(defense); };

  int getDefense() const { return defense; }

 private:
  int defense;
};

class Potion : public Item {
 public:
  Potion(std::string& name, double cost, double weight, double duration)
      : Item(kPotion, name, cost, weight), duration(duration) {}

  std::string getSpecialParam() const { return std::to_string(duration); };

  double getDuration() const { return duration; }

 private:
  double duration;
};

class Scroll : public Item {
 public:
  Scroll(std::string& name, double cost, double weight, std::string effect)
      : Item(kScroll, name, cost, weight), effect(effect) {}

  std::string getSpecialParam() const { return effect; };

  std::string getEffect() const { return effect; }

 private:
  std::string effect;
};

class Shop {
 public:
  Shop(std::string name) : name(name) {}

  void addItem(std::unique_ptr<Item> item) {
    ++count_items;
    total_cost += item->getCost();
    total_weight += item->getWeight();
    switch (item->getType()) {
      case (0):
        total_damage += std::stoi(item->getSpecialParam());
        break;
      case (1):
        total_defense += std::stoi(item->getSpecialParam());
        break;
      case (2):
        effects[item->getSpecialParam()] += 1;
        if (effects[item->getSpecialParam()] > effect_counter) {
          std::cout << item->getSpecialParam();
          effect_counter = effects[item->getSpecialParam()];
          most_often_effect = item->getSpecialParam();
        }
        break;
      case (3):
        total_duration += std::stod(item->getSpecialParam());
        break;
      default:
        break;
    }
    items[item->getType()].push_back(move(item));
  }
  void getInfo() {
    std::cout << "\n============" << name << "============\n\n";
    std::cout << "Count items: " << count_items << '\n';
    std::cout << "Total cost: " << total_cost << '\n';
    std::cout << "Total weight: " << total_weight << "\n\n";
    std::cout << "Middle cost: " << getMidCost() << '\n';
    std::cout << "Middle weight: " << getMidWeight() << "\n\n";
    std::cout << "Middle Damage: " << getMidDamage() << '\n';
    std::cout << "Middle Defense: " << getMidDefense() << '\n';
    std::cout << "Middle Duration: " << getMidDuration() << "\n\n";
    std::cout << "Most often potion effect: " << getOftenEffect() << '\n';
  }

 private:
  double getMidCost() {
    if (!count_items) return 0.0;
    return total_cost / count_items;
  }
  double getMidWeight() {
    if (!count_items) return 0.0;
    return total_weight / count_items;
  }

  int getMidDamage() {
    if (items[Types::kWeapone].size() == 0) return 0;
    return total_damage / items[Types::kWeapone].size();
  }

  int getMidDefense() {
    if (items[Types::kArmor].size() == 0) return 0;
    return total_defense / items[Types::kArmor].size();
  }
  double getMidDuration() {
    if (items[Types::kPotion].size() == 0) return 0;
    return total_duration / items[Types::kPotion].size();
  }
  std::string getOftenEffect() { return most_often_effect; }

  std::string name, most_often_effect = "";
  std::map<Types, std::vector<std::unique_ptr<Item>>> items;
  std::map<std::string, int> effects;
  double total_cost = 0, total_weight = 0, total_duration = 0;
  int count_items = 0, total_damage = 0, total_defense = 0, effect_counter = 0;
};

std::unique_ptr<Item> getItemFromLine(std::string line) {
  std::istringstream iss(line);
  std::string type, name, special;
  double cost, weight;

  iss >> type >> name >> cost >> weight >> special;

  if (type == "WEAPON") {
    return std::make_unique<Weapone>(name, cost, weight, std::stoi(special));
  } else if (type == "ARMOR") {
    return std::make_unique<Armor>(name, cost, weight, std::stoi(special));
  } else if (type == "SCROLL") {
    return std::make_unique<Scroll>(name, cost, weight, special);
  } else if (type == "POTION") {
    return std::make_unique<Potion>(name, cost, weight, std::stod(special));
  }
  return nullptr;
}

int main() {
  setlocale(LC_ALL, "rus");
  std::string filename = "shops.txt"; // ТУТ НАДО ВПИСАТЬ ПУТЬ ДО shops.txt

  std::ifstream file(filename);

  std::string line;

  Shop* current_shop = nullptr;
  std::vector<Shop*> shops;
  while (getline(file, line)) {
    if (line.find("SHOP") == 0) {
      current_shop = new Shop(line.substr(5));
      shops.push_back(current_shop);
    } else if (!line.empty()) {
      current_shop->addItem(getItemFromLine(line));
    }
  }

  for (Shop* sh : shops) {
    sh->getInfo();
  }

  return 0;
}
