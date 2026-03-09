#include <iostream>
#include <string>
#include <variant>
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>

#define NOMINMAX

class MagicItem {
 private:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(std::string name, int price, double weight)
      : name(name), price(price), weight(weight) {}
  virtual std::variant<int, double, std::string> getSpecialParam() const = 0;
  virtual std::string getType() const = 0;

  int getPrice() const { return price; }
  double getWeight() const { return weight; }
};

class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(std::string name, int price, double weight, int damage)
      : MagicItem(name, price, weight), damage(damage) {}

  std::variant<int, double, std::string> getSpecialParam() const override {
    return damage;
  }

  std::string getType() const override { return "Weapon"; }

};

class Armor : public MagicItem {
 private:
  int defence;

 public:
  Armor(std::string name, int price, double weight, int defence)
      : MagicItem(name, price, weight), defence(defence) {}

  std::variant<int, double, std::string> getSpecialParam() const override {
    return defence;
  }

  std::string getType() const override { return "Armor"; }

};

class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(std::string name, int price, double weight, double duration)
      : MagicItem(name, price, weight), duration(duration) {}

  std::variant<int, double, std::string> getSpecialParam() const override {
    return duration;
  }

  std::string getType() const override { return "Potion"; }

};

class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(std::string name, int price, double weight, std::string effect)
      : MagicItem(name, price, weight), effect(effect) {}

  std::variant<int, double, std::string> getSpecialParam() const override {
    return effect;
  }

  std::string getType() const override { return "Scroll"; }

};

class shop {
  std::string name;
  std::vector<MagicItem*> items;

 public:
  shop(std::string name) : name(name) {}

  shop(shop&& other) noexcept  //списал
      : name(std::move(other.name)), items(std::move(other.items)) {
    other.items.clear();
  }

  void addItem(std::string type, std::string name, int price, double weight,
               std::string sp_par) {
    if (type == "Weapon") {
      items.push_back(new Weapon(name, price, weight, stoi(sp_par)));
    } 
    else if (type == "Armor") {
      items.push_back(new Armor(name, price, weight, std::stoi(sp_par)));
    } 
    else if (type == "Potion") {
      items.push_back(new Potion(name, price, weight, std::stod(sp_par)));
    } 
    else if (type == "Scroll") {
      items.push_back(new Scroll(name, price, weight, sp_par));
    }
  }

  void printStats() {
    int total_price = 0;
    double total_weight = .0;
    for (auto& i : items) {
      total_price += i->getPrice();
      total_weight += i->getWeight();
    }
    std::cout << name << std::endl;
    std::cout << "Всего предметов: " << items.size() << std::endl;
    std::cout << "Средняя цена: " << total_price / items.size() << std::endl;
    std::cout << "Средний вес: " << total_weight / items.size() << std::endl;

    int total_damage = 0;
    int weapon_count = 0;
    for (auto& i : items) {
      if (i->getType() == "Weapon") {
        total_damage += get<int>(i->getSpecialParam());
        weapon_count++;
      }
    }
    if (weapon_count != 0) {
      std::cout << "Оружие: средний урон = " << float(total_damage) / weapon_count
                << std::endl;
    } else {
      std::cout << "Оружие: нет в наличии" << std::endl;
    }

    int total_defence = 0;
    int armor_count = 0;
    for (auto& i : items) {
      if (i->getType() == "Armor") {
        total_defence += get<int>(i->getSpecialParam());
        armor_count++;
      }
    }
    if (armor_count != 0) {
      std::cout << "Броня: средняя защита = " << float(total_defence) / armor_count
                << std::endl;
    } else {
      std::cout << "Броня: нет в наличии" << std::endl;
    }

    double total_duration = 0;
    int potion_count = 0;
    for (auto& i : items) {
      if (i->getType() == "Potion") {
        total_duration += get<double>(i->getSpecialParam());
        potion_count++;
      }
    }
    if (potion_count != 0) {
      std::cout << "Зелья: средняя длительность = "
                << total_duration / potion_count << std::endl;
    } else {
      std::cout << "Зелья: нет в наличии" << std::endl;
    }

    std::map<std::string, int> spells;
    for (auto& i : items) {
      if (i->getType() == "Scroll") {
        spells[std::get<std::string>(i->getSpecialParam())]++;
      }
    }
    if (!spells.empty()) {
      std::string very_effect;
      int max_count = 0;
      for (auto& [effect, count] : spells) {
        if (count > max_count) {
          very_effect = effect;
          max_count = count;
        }
      }
      std::cout << "Свитки: самый частый эффект = " << very_effect << std::endl
                << std::endl;
    } else {
      std::cout << "Свитки: нет в наличии" << std::endl << std::endl;
    }
  }

  ~shop() {
    for (auto item : items) {
      delete item;
    }
    items.clear();
  }
};

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  std::ifstream file("SHOPS.txt");
  std::vector<shop> shops;

  int item_count;
  std::string shop_name;

  while (file >> shop_name >> item_count) {
    shop cur_shop(shop_name);
    for (int i = 0; i < item_count; i++) {
      std::string type, name, special_parameter;
      int price;
      double weight;

      file >> type >> name >> price >> weight >> special_parameter;
      cur_shop.addItem(type, name, price, weight, special_parameter);

    }

    shops.push_back(std::move(cur_shop));

  }

  file.close();

  for (auto& s : shops) {
    s.printStats();
  }

}