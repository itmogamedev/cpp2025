// чтение файла, создание объектов, посчет средних значений, написание отчета
// для гильдии
#include "shop_processor.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>

#include "armor.h"
#include "potion.h"
#include "scroll.h"
#include "weapon.h"

void ShopProcessor::processFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл " << filename << '\n';
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("Магазин:") == std::string::npos) continue;

    std::string shopName = line.substr(line.find(':') + 2);
    std::getline(file, line);
    int itemCount = std::stoi(line.substr(line.find(':') + 2));

    std::vector<std::unique_ptr<MagicItem>> items;
    items.reserve(itemCount);

    for (int i = 0; i < itemCount; ++i) {
      std::getline(file, line);
      std::istringstream ss(line);

      std::string typeStr, name;
      int price;
      double weight;

      ss >> typeStr >> name >> price >> weight;
      std::replace(name.begin(), name.end(), '_', ' ');

      if (typeStr == "Оружие") {
        int damage;
        ss >> damage;
        items.emplace_back(
            std::make_unique<Weapon>(name, price, weight, damage));
      } else if (typeStr == "Броня") {
        int defense;
        ss >> defense;
        items.emplace_back(
            std::make_unique<Armor>(name, price, weight, defense));
      } else if (typeStr == "Зелье") {
        double duration;
        ss >> duration;
        items.emplace_back(
            std::make_unique<Potion>(name, price, weight, duration));
      } else if (typeStr == "Свиток") {
        std::string effect, temp;
        std::getline(ss, temp);
        effect = temp;
        effect.erase(0, effect.find_first_not_of(" \t"));
        items.emplace_back(
            std::make_unique<Scroll>(name, price, weight, effect));
      }
    }

    printShopReport(shopName, items);
  }
}

double ShopProcessor::calculateAveragePrice(
    const std::vector<std::unique_ptr<MagicItem>>& items) {
  if (items.empty()) return 0.0;
  double sum = 0.0;
  for (const auto& item : items) sum += item->getPrice();
  return sum / items.size();
}

double ShopProcessor::calculateAverageWeight(
    const std::vector<std::unique_ptr<MagicItem>>& items) {
  if (items.empty()) return 0.0;
  double sum = 0.0;
  for (const auto& item : items) sum += item->getWeight();
  return sum / items.size();
}

void ShopProcessor::printShopReport(
    const std::string& shopName,
    const std::vector<std::unique_ptr<MagicItem>>& items) {
  std::cout << "=== Магазин: " << shopName << " ===\n";
  std::cout << "Всего предметов: " << items.size() << "\n";
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Средняя цена: " << calculateAveragePrice(items) << " золота\n";
  std::cout << "Средний вес: " << calculateAverageWeight(items) << " кг\n\n";
  std::cout << "Статистика по предметам:\n";

  std::unordered_map<std::string, std::vector<const MagicItem*>> groups;
  for (const auto& item : items) {
    groups[item->getTypeName()].push_back(item.get());
  }

  const struct {
    const char* eng;
    const char* rus;
  } types[] = {{"Weapon", "Оружие"},
               {"Armor", "Броня"},
               {"Potion", "Зелья"},
               {"Scroll", "Свитки"}};

  for (const auto& t : types) {
    auto it = groups.find(t.eng);
    if (it == groups.end() || it->second.empty()) {
      std::cout << "- " << t.rus << ": нет в наличии\n";
      continue;
    }

    std::cout << "- " << t.rus << ": ";
    const auto& list = it->second;

    if (t.eng == std::string("Weapon")) {
      double sum = 0;
      for (const auto* w : list)
        sum += static_cast<const Weapon*>(w)->getDamage();
      std::cout << "средний урон = " << (sum / list.size());
    } else if (t.eng == std::string("Armor")) {
      double sum = 0;
      for (const auto* a : list)
        sum += static_cast<const Armor*>(a)->getDefense();
      std::cout << "средняя защита = " << (sum / list.size());
    } else if (t.eng == std::string("Potion")) {
      double sum = 0;
      for (const auto* p : list)
        sum += static_cast<const Potion*>(p)->getDuration();
      std::cout << "средняя длительность = " << std::fixed
                << std::setprecision(1) << (sum / list.size());
    } else if (t.eng == std::string("Scroll")) {
      std::map<std::string, int> freq;
      for (const auto* s : list) {
        freq[static_cast<const Scroll*>(s)->getEffect()]++;
      }
      auto maxIt = std::max_element(
          freq.begin(), freq.end(),
          [](const auto& a, const auto& b) { return a.second < b.second; });
      std::cout << "самый частый эффект " << maxIt->first;
      if (maxIt->second > 1)
        std::cout << " (встречается " << maxIt->second << " раз)";
    }
    std::cout << "\n";
  }
  std::cout << "\n\n";
}
