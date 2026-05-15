#include "MagicItems.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

class Weapon : public MagicItem {
  int strength;

 public:
  Weapon(const std::string& n, double p, double w, int s)
      : MagicItem(n, p, w), strength(s) {}
  std::variant<int, double, std::string> getSpecificParameter() const override {
    return strength;
  }
  std::string getType() const override { return "Оружие"; }
};

class Runes : public MagicItem {
  std::string effect;

 public:
  Runes(const std::string& n, double p, double w, const std::string& e)
      : MagicItem(n, p, w), effect(e) {}
  std::variant<int, double, std::string> getSpecificParameter() const override {
    return effect;
  }
  std::string getType() const override { return "Руны"; }
};

class Potion : public MagicItem {
  int damage;

 public:
  Potion(const std::string& n, double p, double w, int d)
      : MagicItem(n, p, w), damage(d) {}
  std::variant<int, double, std::string> getSpecificParameter() const override {
    return damage;
  }
  std::string getType() const override { return "Зелье"; }
};

class Armor : public MagicItem {
  double protection;

 public:
  Armor(const std::string& n, double p, double w, double r)
      : MagicItem(n, p, w), protection(r) {}
  std::variant<int, double, std::string> getSpecificParameter() const override {
    return protection;
  }
  std::string getType() const override { return "Броня"; }
};

class Clothes : public MagicItem {
  int protection;

 public:
  Clothes(const std::string& n, double p, double w, int r)
      : MagicItem(n, p, w), protection(r) {}
  std::variant<int, double, std::string> getSpecificParameter() const override {
    return protection;
  }
  std::string getType() const override { return "Одежда"; }
};

class Scroll : public MagicItem {
  std::string impact;

 public:
  Scroll(const std::string& n, double p, double w, const std::string& i)
      : MagicItem(n, p, w), impact(i) {}
  std::variant<int, double, std::string> getSpecificParameter() const override {
    return impact;
  }
  std::string getType() const override { return "Свиток"; }
};

// Реализация функций
std::vector<std::unique_ptr<MagicItem>> readShop(std::ifstream& file,
                                                 std::string shopName) {
  std::vector<std::unique_ptr<MagicItem>> items;
  std::string line;

  std::getline(file, line);
  std::istringstream iss(line);
  std::string dummy;
  int count;
  iss >> dummy >> count;

  for (int i = 0; i < count; ++i) {
    std::getline(file, line);
    std::istringstream itemLine(line);

    std::string type, name, parStr;
    double price, weight;
    int intPar;
    double doublePar;

    if (!(itemLine >> type >> name >> price >> weight)) {
      std::cerr << "Ошибка чтения предмета " << i + 1 << std::endl;
      continue;
    }

    if (type == "Оружие") {
      itemLine >> intPar;
      items.push_back(std::make_unique<Weapon>(name, price, weight, intPar));
    } else if (type == "Руны") {
      itemLine >> parStr;
      items.push_back(std::make_unique<Runes>(name, price, weight, parStr));
    } else if (type == "Зелье") {
      itemLine >> intPar;
      items.push_back(std::make_unique<Potion>(name, price, weight, intPar));
    } else if (type == "Броня") {
      itemLine >> doublePar;
      items.push_back(std::make_unique<Armor>(name, price, weight, doublePar));
    } else if (type == "Одежда") {
      itemLine >> intPar;
      items.push_back(std::make_unique<Clothes>(name, price, weight, intPar));
    } else if (type == "Свиток") {
      itemLine >> parStr;
      items.push_back(std::make_unique<Scroll>(name, price, weight, parStr));
    }
  }
  return items;
}

shopStats calculateStats(std::string shopName,
                         const std::vector<std::unique_ptr<MagicItem>>& items) {
  shopStats stats;
  stats.name = shopName;
  stats.totalItems = items.size();
  double totalPrice = 0, totalWeight = 0;
  std::map<std::string, std::vector<double>> numParams;

  for (const auto& item : items) {
    totalPrice += item->price;
    totalWeight += item->weight;
    std::string type = item->getType();
    auto param = item->getSpecificParameter();

    if (type == "Оружие" || type == "Зелье" || type == "Одежда") {
      double value = static_cast<double>(std::get<int>(param));
      numParams[type].push_back(value);
    } else if (type == "Броня") {
      double value = std::get<double>(param);
      numParams[type].push_back(value);
    } else {
      std::string effect = std::get<std::string>(param);
      stats.Effects[type][effect]++;
    }
  }

  if (stats.totalItems > 0) {
    stats.avgPrice = totalPrice / stats.totalItems;
    stats.avgWeight = totalWeight / stats.totalItems;
  }

  for (const auto& pair : numParams) {
    const auto& values = pair.second;
    if (!values.empty()) {
      double sum = 0;
      for (double v : values) sum += v;
      stats.typeAvgParams[pair.first] = sum / values.size();
    }
  }
  return stats;
}

void printStats(const shopStats& stats) {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "=== Магазин: " << stats.name << " ===\n";
  std::cout << "Всего предметов: " << stats.totalItems << "\n";
  std::cout << "Средняя цена: " << stats.avgPrice << " золота\n";
  std::cout << "Средний вес: " << stats.avgWeight << " кг\n\n";

  std::cout << "Статистика по предметам: " << std::endl;

  std::vector<std::string> types = {"Оружие", "Руны",   "Зелье",
                                    "Броня",  "Свиток", "Одежда"};
  for (const std::string& type : types) {
    std::cout << "- " << type << ": ";

    if (stats.typeAvgParams.count(type)) {
      std::cout << "средний параметр = " << std::fixed << std::setprecision(1)
                << stats.typeAvgParams.at(type);
    } else if (stats.Effects.count(type) && !stats.Effects.at(type).empty()) {
      const auto& effects = stats.Effects.at(type);
      auto maxIt = std::max_element(
          effects.begin(), effects.end(),
          [](const auto& a, const auto& b) { return a.second < b.second; });
      std::cout << "самый частый эффект \"" << maxIt->first << "\"";
    } else {
      std::cout << "нет в наличии";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
