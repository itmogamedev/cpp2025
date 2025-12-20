#include <windows.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& name, int price, double weight)
      : name(name), price(price), weight(weight) {}

  virtual ~MagicItem() = default;

  int getPrice() const { return price; }
  double getWeight() const { return weight; }
  const std::string& getName() const { return name; }

  virtual std::string getType() const = 0;

  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
};

class Weapon : public MagicItem {
 protected:
  int damage;

 public:
  Weapon(const std::string& name, int price, double weight, int damage)
      : MagicItem(name, price, weight), damage(damage) {}

  std::string getType() const override { return "Оружие"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }
};

class Armor : public MagicItem {
 protected:
  int defense;

 public:
  Armor(const std::string& name, int price, double weight, int defense)
      : MagicItem(name, price, weight), defense(defense) {}

  std::string getType() const override { return "Броня"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return defense;
  }
};

class Potion : public MagicItem {
 protected:
  double duration;

 public:
  Potion(const std::string& name, int price, double weight, double duration)
      : MagicItem(name, price, weight), duration(duration) {}

  std::string getType() const override { return "Зелье"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }
};

class Scroll : public MagicItem {
 protected:
  std::string effect;

 public:
  Scroll(const std::string& name, int price, double weight,
         const std::string& effect)
      : MagicItem(name, price, weight), effect(effect) {}

  std::string getType() const override { return "Свиток"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }
};

struct Shop {
  std::string name;
  std::vector<std::shared_ptr<MagicItem>> items;
};

std::vector<Shop> readShopsFromFile(const std::string& filename) {
  std::ifstream in(filename);
  std::vector<Shop> shops;

  if (!in) {
    std::cerr << "Не удалось открыть файл: " << filename << std::endl;
    return shops;
  }

  std::string token;
  while (in >> token) {
    if (token != "Магазин:") {
      std::string dummy;
      std::getline(in, dummy);
      continue;
    }

    Shop shop;
    in >> shop.name;

    std::string label;
    int count = 0;
    in >> label >> count;

    shop.items.reserve(count);

    for (int i = 0; i < count; ++i) {
      std::string type;
      std::string item_name;
      int price;
      double weight;

      if (!(in >> type >> item_name >> price >> weight)) {
        std::cerr << "Ошибка чтения предмета в магазине " << shop.name
                  << std::endl;
        break;
      }

      if (type == "Оружие") {
        int damage;
        in >> damage;
        shop.items.push_back(
            std::make_shared<Weapon>(item_name, price, weight, damage));
      } else if (type == "Броня") {
        int defense;
        in >> defense;
        shop.items.push_back(
            std::make_shared<Armor>(item_name, price, weight, defense));
      } else if (type == "Зелье") {
        double duration;
        in >> duration;
        shop.items.push_back(
            std::make_shared<Potion>(item_name, price, weight, duration));
      } else if (type == "Свиток") {
        std::string effect;
        in >> effect;
        shop.items.push_back(
            std::make_shared<Scroll>(item_name, price, weight, effect));
      } else {
        std::string rest;
        std::getline(in, rest);
      }
    }

    shops.push_back(shop);
  }

  return shops;
}

double computeAveragePrice(const Shop& shop) {
  if (shop.items.empty()) return 0.0;
  long long sum = 0;
  for (const auto& item : shop.items) {
    sum += item->getPrice();
  }
  return static_cast<double>(sum) / shop.items.size();
}

double computeAverageWeight(const Shop& shop) {
  if (shop.items.empty()) return 0.0;
  double sum = 0.0;
  for (const auto& item : shop.items) {
    sum += item->getWeight();
  }
  return sum / shop.items.size();
}

template <typename T>
bool computeAverageSpec(
    const std::vector<std::variant<int, double, std::string>>& data,
    double& outAvg) {
  if (data.empty()) return false;
  double sum = 0.0;
  int cnt = 0;
  for (const auto& v : data) {
    if constexpr (std::is_same_v<T, int>) {
      if (std::holds_alternative<int>(v)) {
        sum += std::get<int>(v);
        ++cnt;
      }
    } else if constexpr (std::is_same_v<T, double>) {
      if (std::holds_alternative<double>(v)) {
        sum += std::get<double>(v);
        ++cnt;
      }
    }
  }
  if (cnt == 0) return false;
  outAvg = sum / cnt;
  return true;
}

bool computeMostFrequentString(
    const std::vector<std::variant<int, double, std::string>>& data,
    std::string& outStr) {
  if (data.empty()) return false;
  std::map<std::string, int> freq;
  for (const auto& v : data) {
    if (std::holds_alternative<std::string>(v)) {
      ++freq[std::get<std::string>(v)];
    }
  }
  if (freq.empty()) return false;
  int bestCount = -1;
  std::string best;
  for (const auto& p : freq) {
    if (p.second > bestCount) {
      bestCount = p.second;
      best = p.first;
    }
  }
  outStr = best;
  return true;
}

void printShopStats(const Shop& shop) {
  std::cout << "=== Магазин: " << shop.name << " ===\n";
  std::cout << "Всего предметов: " << shop.items.size() << "\n";

  double avgPrice = computeAveragePrice(shop);
  double avgWeight = computeAverageWeight(shop);

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Средняя цена: " << avgPrice << " золота\n";
  std::cout << "Средний вес: " << avgWeight << " кг\n\n";

  std::vector<std::variant<int, double, std::string>> weaponParams;
  std::vector<std::variant<int, double, std::string>> armorParams;
  std::vector<std::variant<int, double, std::string>> potionParams;
  std::vector<std::variant<int, double, std::string>> scrollParams;

  for (const auto& item : shop.items) {
    std::string type = item->getType();
    if (type == "Оружие") {
      weaponParams.push_back(item->getSpecParam());
    } else if (type == "Броня") {
      armorParams.push_back(item->getSpecParam());
    } else if (type == "Зелье") {
      potionParams.push_back(item->getSpecParam());
    } else if (type == "Свиток") {
      scrollParams.push_back(item->getSpecParam());
    }
  }

  std::cout << "Статистика по предметам:\n";

  std::cout << "- Оружие: ";
  if (weaponParams.empty()) {
    std::cout << "нет в наличии\n";
  } else {
    double avgDamage = 0.0;
    if (computeAverageSpec<int>(weaponParams, avgDamage)) {
      std::cout << "средний урон = " << avgDamage << "\n";
    } else {
      std::cout << "ошибка вычисления\n";
    }
  }

  std::cout << "- Броня: ";
  if (armorParams.empty()) {
    std::cout << "нет в наличии\n";
  } else {
    double avgDef = 0.0;
    if (computeAverageSpec<int>(armorParams, avgDef)) {
      std::cout << "средняя защита = " << avgDef << "\n";
    } else {
      std::cout << "ошибка вычисления\n";
    }
  }

  std::cout << "- Зелья: ";
  if (potionParams.empty()) {
    std::cout << "нет в наличии\n";
  } else {
    double avgDur = 0.0;
    if (computeAverageSpec<double>(potionParams, avgDur)) {
      std::cout << "средняя длительность = " << avgDur << "\n";
    } else {
      std::cout << "ошибка вычисления\n";
    }
  }

  std::cout << "- Свитки: ";
  if (scrollParams.empty()) {
    std::cout << "нет в наличии\n";
  } else {
    std::string mostFreq;
    if (computeMostFrequentString(scrollParams, mostFreq)) {
      std::cout << "самый частый эффект " << mostFreq << "\n";
    } else {
      std::cout << "ошибка вычисления\n";
    }
  }

  std::cout << "\n";
}

int main() {
  setlocale(LC_ALL, "");

  std::string filename = "shops.txt";
  auto shops = readShopsFromFile(filename);

  if (shops.empty()) {
    std::cerr << "Магазины не найдены. Проверьте файл " << filename
              << std::endl;
    return 1;
  }

  for (const auto& shop : shops) {
    printShopStats(shop);
  }

  return 0;
}
