#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

enum item_TypeS {
  Type_None,

  Type_Int,
  Weapon,
  Armor,
  Tech,

  Type_String,
  Power
};

class MagicItem {
 public:
  std::string name;
  int price = 0;
  int weight = 0;

  MagicItem(std::stringstream& line) {
    line >> name;
    line >> price;
    line >> weight;
  }

  item_TypeS getType() { return Type; }

  virtual std::variant<int, std::string> getSpecific() = 0;

 protected:
  item_TypeS Type = item_TypeS::Type_None;
};

class weapon : public MagicItem {
 public:
  weapon(std::stringstream& line) : MagicItem(line) {
    line >> damage;
    Type = item_TypeS::Weapon;
  }

  std::variant<int, std::string> getSpecific() override { return damage; }

 private:
  int damage = 0;
};

class armor : public MagicItem {
 public:
  armor(std::stringstream& line) : MagicItem(line) {
    line >> protection;
    Type = item_TypeS::Armor;
  }

  std::variant<int, std::string> getSpecific() override { return protection; }

 private:
  int protection = 0;
};

class tech : public MagicItem {
 public:
  tech(std::stringstream& line) : MagicItem(line) {
    line >> quality;
    Type = item_TypeS::Tech;
  }

  std::variant<int, std::string> getSpecific() override { return quality; }

 private:
  int quality = 0;
};

class power : public MagicItem {
 public:
  power(std::stringstream& line) : MagicItem(line) {
    line >> description;
    Type = item_TypeS::Power;
  }

  std::variant<int, std::string> getSpecific() override { return description; }

 private:
  std::string description;
};

class Shop {
 private:
  std::vector<MagicItem*> items;

 public:
  std::string name;

  Shop(std::string name) { this->name = name; }

  void add(MagicItem* item) { items.push_back(item); }

  std::size_t size() { return items.size(); }

  float commonPrice() {
    if (size() == 0) {
      return 0;
    }

    float common = 0;

    for (auto it : items) {
      common += it->price;
    }

    return common / size();
  }

  float commonWeight() {
    if (size() == 0) {
      return 0;
    }

    float common = 0;

    for (auto it : items) {
      common += it->weight;
    }

    return common / size();
  }

  std::string commonSpecific(item_TypeS Type) {
    if (item_TypeS::Type_Int < Type && Type < item_TypeS::Type_String) {
      float common = 0;
      int size = 0;

      for (auto it : items) {
        if (it->getType() == Type) {
          common += std::get<int>(it->getSpecific());
          size++;
        }
      }

      if (size == 0) {
        return "Нет в наличии";
      }

      return std::to_string(common / size);
    } else if (item_TypeS::Type_String < Type) {
      std::map<std::string, int> counter;

      for (auto it : items) {
        if (it->getType() == Type) {
          std::string item = std::get<std::string>(it->getSpecific());
          counter[item]++;
        }
      }

      if (counter.size() == 0) {
        return "Нет в наличии";
      }

      return counter.begin()->first;
    }

    return "Нет в наличии";
  }
};

int main() {
  setlocale(LC_ALL, "Russian");
  std::ifstream file("shop.txt");

  std::vector<Shop> shops;
  MagicItem* item;
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

    if (token == "weapon") {
      item = new weapon(streamline);
    } else if (token == "armor") {
      item = new armor(streamline);
    } else if (token == "tech") {
      item = new tech(streamline);
    } else if (token == "power") {
      item = new power(streamline);
    } else {
      shops.push_back(Shop(token));
      continue;
    }

    shops.back().add(item);
  }

  for (auto shop : shops) {
    std::cout << "=== Магазин: " << shop.name << " ===\n";
    std::cout << "Количество предметов: " << shop.size() << "\n";
    std::cout << "Средняя цена: " << shop.commonPrice() << "\n";
    std::cout << "Средний вес: " << shop.commonWeight() << "\n";

    std::cout << "\n";

    std::cout << "Статистика:\n";
    std::cout << "Урон оружий: " << shop.commonSpecific(item_TypeS::Weapon)
              << "\n";
    std::cout << "Защита брони: " << shop.commonSpecific(item_TypeS::Armor)
              << "\n";
    std::cout << "Качество техники: " << shop.commonSpecific(item_TypeS::Tech)
              << "\n";
    std::cout << "Самый частый эффект: "
              << shop.commonSpecific(item_TypeS::Power) << "\n";

    std::cout << "\n" << std::endl;
  }

  return 0;
}
