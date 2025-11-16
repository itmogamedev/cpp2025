#include "MagicItem.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>

// MagicItem's Methods
MagicItem::MagicItem(const std::string& n, int p, double w)
    : name(n), price(p), weight(w) {}

std::string MagicItem::getName() const { return name; }
int MagicItem::getPrice() const { return price; }
double MagicItem::getWeight() const { return weight; }

// Weapon's Methods
Weapon::Weapon(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), damage(d) {}

SpecialParam Weapon::getSpecParam() const { return damage; }

std::string Weapon::getType() const { return "Оружие"; }

// Armor's Method
Armor::Armor(const std::string& n, int p, double w, int d)
    : MagicItem(n, p, w), defense(d) {}

SpecialParam Armor::getSpecParam() const { return defense; }

std::string Armor::getType() const { return "Броня"; }

// Potion's Methods
Potion::Potion(const std::string& n, int p, double w, double d)
    : MagicItem(n, p, w), duration(d) {}

SpecialParam Potion::getSpecParam() const { return duration; }

std::string Potion::getType() const { return "Зелье"; }

// Scroll's Methods
Scroll::Scroll(const std::string& n, int p, double w, const std::string& e)
    : MagicItem(n, p, w), effect(e) {}

SpecialParam Scroll::getSpecParam() const { return effect; }

std::string Scroll::getType() const { return "Свиток"; }

// MagicShop's Methods
MagicShop::MagicShop(const std::string& n) : name(n) {}

void MagicShop::addItem(std::unique_ptr<MagicItem> item) {
  items.push_back(std::move(item));
}

double MagicShop::getAveragePrice() const {
  if (items.empty()) return 0.0f;
  int total = 0;
  for (const auto& item : items) {
    total += item->getPrice();
  }
  return static_cast<double>(total) / items.size();
}

double MagicShop::getAverageWeight() const {
  if (items.empty()) return 0.0f;
  double total = 0.0f;
  for (const auto& item : items) {
    total += item->getWeight();
  }
  return total / items.size();
}

void MagicShop::analyzeSpecialParams() const {
  // Key -> MagicItem's Type; Value -> {spec_params, ...}
  std::map<std::string, std::vector<SpecialParam>> paramsByType;

  for (const auto& item : items) {
    paramsByType[item->getType()].push_back(item->getSpecParam());
  }

  std::vector<std::string> allTypes = {"Оружие", "Броня", "Зелье", "Свиток"};

  std::cout << "  " << "Статистика по предметам:\n";
  for (const auto& type : allTypes) {
    if (paramsByType.find(type) == paramsByType.end()) {
      std::cout << "    - " << type << ": распродано\n";
      continue;
    }

    const auto& params = paramsByType[type];

    if (type == "Оружие" || type == "Броня") {
      // For int params (damage, defense)
      double sum = 0;
      for (const auto& param : params) {
        sum += std::get<int>(param);
      }
      double average = sum / params.size();
      std::string paramName = (type == "Оружие") ? "урон" : "защита";
      std::cout << "    - " << type << ": средний " << paramName << " = "
                << std::fixed << std::setprecision(0) << average << "\n";
    } else if (type == "Зелье") {
      // For double params (duratation)
      double sum = 0;
      for (const auto& param : params) {
        sum += std::get<double>(param);
      }
      double average = sum / params.size();
      std::cout << "    - " << type << ": средняя длительность = " << std::fixed
                << std::setprecision(1) << average << "\n";
    } else if (type == "Свиток") {
      // For string params
      std::map<std::string, int> effectCount;
      for (const auto& param : params) {
        effectCount[std::get<std::string>(param)]++;
      }

      std::string mostCommon;
      int maxCount = 0;
      for (const auto& [effect, count] : effectCount) {
        if (count > maxCount) {
          maxCount = count;
          mostCommon = effect;
        }
      }

      std::cout << "    - " << type << ": самый частый эффект " << mostCommon
                << "\n";
    }
  }

  std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void MagicShop::printReport() const {
  std::cout << "=== Магазин:" << name << " ===\n";
  std::cout << "  " << "Всего предметов: " << items.size() << "\n";
  std::cout << "  " << "Средняя цена: " << std::fixed << std::setprecision(2)
            << getAveragePrice() << " золота\n";
  std::cout << "  " << "Средний вес: " << std::fixed << std::setprecision(2)
            << getAverageWeight() << " кг\n\n";

  analyzeSpecialParams();
  std::cout << "\n";
}

// Create item from MagicItem class
std::unique_ptr<MagicItem> createItem(const std::string& type,
                                      const std::string& name, int price,
                                      double weight,
                                      const std::string& specParam) {
  if (type == "Оружие") {
    return std::make_unique<Weapon>(name, price, weight, std::stoi(specParam));
  } else if (type == "Броня") {
    return std::make_unique<Armor>(name, price, weight, std::stoi(specParam));
  } else if (type == "Зелье") {
    return std::make_unique<Potion>(name, price, weight, std::stod(specParam));
  } else if (type == "Свиток") {
    return std::make_unique<Scroll>(name, price, weight, specParam);
  }

  return nullptr;
}

// Fead from file
std::vector<MagicShop> readShopsFromFile(const std::string& filename) {
  std::vector<MagicShop> shops;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Can't open file" << filename << "\n";
    return shops;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;

    if (line.find("Магазин:") != std::string::npos) {
      size_t pos = line.find("Магазин:");
      std::string shopName = line.substr(pos + 8);

      if (!std::getline(file, line)) break;

      int itemCount = 0;
      if (line.find("Предметы:") != std::string::npos) {
        size_t itemPos = line.find("Предметы:");
        itemCount = std::stoi(line.substr(itemPos + 9));
      }

      MagicShop shop(shopName);

      // Items
      for (int i = 0; i < itemCount; ++i) {
        if (!std::getline(file, line)) break;

        std::istringstream iss(line);
        std::string type, name, specParam;
        int price;
        double weight;

        if (iss >> type >> name >> price >> weight >> specParam) {
          try {
            auto item = createItem(type, name, price, weight, specParam);
            if (item) {
              shop.addItem(std::move(item));
            }
          } catch (const std::exception& e) {
            std::cerr << "Error: can't create an item" << e.what() << "\n";
          }
        }
      }

      shops.push_back(std::move(shop));
    }
  }

  file.close();
  return shops;
}
