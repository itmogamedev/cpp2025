#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include <algorithm>

class MagicItem {
 public:
  MagicItem(std::string name, int price, double weight)
      : name(std::move(name)), price(price), weight(weight) {}
  
  virtual ~MagicItem() = default;

  virtual std::variant<int, double, std::string> GetSpecParam() const = 0;
  virtual std::string GetType() const = 0;

  const std::string& GetName() const { return name; }
  int GetPrice() const { return price; }
  double GetWeight() const { return weight; }

 private:
  std::string name;
  int price;
  double weight;
};

class Weapon : public MagicItem {
 public:
  Weapon(std::string name, int price, double weight, int damage)
      : MagicItem(std::move(name), price, weight), damage(damage) {}
  
  std::variant<int, double, std::string> GetSpecParam() const override {
    return damage;
  }
  
  std::string GetType() const override { return "Оружие"; }

 private:
  int damage;
};

class Armor : public MagicItem {
 public:
  Armor(std::string name, int price, double weight, int defence)
      : MagicItem(std::move(name), price, weight), defence(defence) {}
  
  std::variant<int, double, std::string> GetSpecParam() const override {
    return defence;
  }
  
  std::string GetType() const override { return "Броня"; }

 private:
  int defence;
};

class Potion : public MagicItem {
 public:
  Potion(std::string name, int price, double weight, double duration)
      : MagicItem(std::move(name), price, weight), duration(duration) {}
  
  std::variant<int, double, std::string> GetSpecParam() const override {
    return duration;
  }
  
  std::string GetType() const override { return "Зелье"; }

 private:
  double duration;
};

class Scroll : public MagicItem {
 public:
  Scroll(std::string name, int price, double weight, std::string effect)
      : MagicItem(std::move(name), price, weight), effect(std::move(effect)) {}
  
  std::variant<int, double, std::string> GetSpecParam() const override {
    return effect;
  }
  
  std::string GetType() const override { return "Свиток"; }
  
  const std::string& GetEffect() const { return effect; }

 private:
  std::string effect;
};

MagicItem* CreateItem(const std::string& line) {
  std::istringstream iss(line);
  std::string type, name;
  int price;
  double weight;

  if (!(iss >> type >> name >> price >> weight)) return nullptr;

  if (type == "Оружие") {
    int damage;
    if (iss >> damage) return new Weapon(name, price, weight, damage);
  } else if (type == "Броня") {
    int defence;
    if (iss >> defence) return new Armor(name, price, weight, defence);
  } else if (type == "Зелье") {
    double duration;
    if (iss >> duration) return new Potion(name, price, weight, duration);
  } else if (type == "Свиток") {
    std::string effect, word;
    while (iss >> word) {
      if (!effect.empty()) effect += " ";
      effect += word;
    }
    if (effect.empty()) effect = "Неизвестно";
    return new Scroll(name, price, weight, effect);
  }
  return nullptr;
}

std::string GetMostCommonScrollEffect(const std::vector<std::string>& effects) {
  if (effects.empty()) return "нет свитков";

  std::vector<std::string> uniqueEffects;
  std::vector<int> counts;
  
  for (const auto& effect : effects) {
    bool found = false;
    for (size_t i = 0; i < uniqueEffects.size(); ++i) {
      if (uniqueEffects[i] == effect) {
        counts[i]++;
        found = true;
        break;
      }
    }
    if (!found) {
      uniqueEffects.push_back(effect);
      counts.push_back(1);
    }
  }
  
  int maxCount = 0;
  std::string mostCommon;
  for (size_t i = 0; i < uniqueEffects.size(); ++i) {
    if (counts[i] > maxCount) {
      maxCount = counts[i];
      mostCommon = uniqueEffects[i];
    }
  }
  
  return mostCommon + " (" + std::to_string(maxCount) + " раз)";
}

int main() {
  std::ifstream file("items.txt");
  if (!file.is_open()) {
    std::cout << "Ошибка: не удалось открыть items.txt\n";
    return 1;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    
    if (line.find("Магазин:") == std::string::npos) continue;

    std::string shopName = line.substr(line.find(':') + 1);
    shopName.erase(0, shopName.find_first_not_of(" \t"));
    
    std::vector<MagicItem*> items;

    std::getline(file, line);

    while (std::getline(file, line)) {
      if (line.empty() || line.find("Магазин:") != std::string::npos) {
        if (line.find("Магазин:") != std::string::npos) {
          file.seekg(-static_cast<int>(line.length()) - 1, std::ios_base::cur);
        }
        break;
      }
      
      if (line.find("Предметы:") != std::string::npos) continue;
      
      if (MagicItem* item = CreateItem(line)) {
        items.push_back(item);
      }
    }

    if (items.empty()) {
      std::cout << "Магазин '" << shopName << "' не содержит предметов!\n";
      continue;
    }

    std::cout << std::string(60, '=') << '\n';
    std::cout << "Магазин: " << shopName << '\n';
    std::cout << std::string(60, '-') << '\n';

    double totalPrice = 0.0;
    double totalWeight = 0.0;
    std::vector<int> damageValues;
    std::vector<int> defenceValues;
    std::vector<double> durationValues;
    std::vector<std::string> effects;

    for (const auto* item : items) {
      totalPrice += item->GetPrice();
      totalWeight += item->GetWeight();
      auto param = item->GetSpecParam();

      if (item->GetType() == "Оружие") {
        damageValues.push_back(std::get<int>(param));
      } else if (item->GetType() == "Броня") {
        defenceValues.push_back(std::get<int>(param));
      } else if (item->GetType() == "Зелье") {
        durationValues.push_back(std::get<double>(param));
      } else if (item->GetType() == "Свиток") {
        effects.push_back(std::get<std::string>(param));
      }
    }

    auto CalculateAverage = [](const auto& values) -> double {
      if (values.empty()) return 0.0;
      return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    };

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Всего предметов: " << items.size() << '\n';
    std::cout << "Средняя цена: " << totalPrice / items.size() << " золотых\n";
    std::cout << "Средний вес: " << totalWeight / items.size() << " кг\n\n";
    std::cout << "Средние специфические параметры по типам:\n";
    std::cout << "  Оружие (урон):     "
              << (damageValues.empty() ? "нет товаров"
                                      : std::to_string(static_cast<int>(std::round(CalculateAverage(damageValues)))))
              << '\n';
    std::cout << "  Броня (защита):    "
              << (defenceValues.empty() ? "нет товаров"
                                       : std::to_string(static_cast<int>(std::round(CalculateAverage(defenceValues)))))
              << '\n';
    std::cout << "  Зелье (длительность): "
              << (durationValues.empty() ? "нет товаров" : std::to_string(CalculateAverage(durationValues)) + " сек")
              << '\n';
    std::cout << "  Свиток (самый частый эффект): " << GetMostCommonScrollEffect(effects)
              << '\n';
    std::cout << '\n';

    for (auto* item : items) delete item;
  }

  file.close();
  return 0;
}