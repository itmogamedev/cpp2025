#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

// классы

class MagicItem {
 public:
  std::string name;
  int price;
  double weight;
  virtual std::variant<int, double, std::string> getSpecParam() = 0;
  int getPrice() { return price; }
  double getWeight() { return weight; }
  virtual std::string getType() = 0;
};

class Weapon : public MagicItem {
 public:
  Weapon(std::string name, int price, double weight, int damage) {
    this->name = name;
    this->price = price;
    this->weight = weight;
    this->damage = damage;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return damage;
  }
  int damage;

  std::string getType() override { return "Оружие"; }
};

class Armor : public MagicItem {
 public:
  Armor(std::string name, int price, double weight, int defense) {
    this->name = name;
    this->price = price;
    this->weight = weight;
    this->defense = defense;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return defense;
  }
  int defense;

  std::string getType() override { return "Броня"; }
};

class Potion : public MagicItem {
 public:
  Potion(std::string name, int price, double weight, double duration) {
    this->name = name;
    this->price = price;
    this->weight = weight;
    this->duration = duration;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return duration;
  }
  double duration;

  std::string getType() override { return "Зелье"; }
};

class Scroll : public MagicItem {
 public:
  Scroll(std::string name, int price, double weight, std::string effect) {
    this->name = name;
    this->price = price;
    this->weight = weight;
    this->effect = effect;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return effect;
  }
  std::string effect;

  std::string getType() override { return "Свиток"; };
};

class Shop {
 public:
  std::vector<MagicItem*> items;

  std::string name;

  Shop(std::string name) { this->name = name; }

  void add(MagicItem* item) { items.push_back(item); }

  void analyze() {
    std::cout << "=== Магазин: " << name << " ===" << std::endl;
    std::cout << "Всего предметов: " << items.size() << std::endl;

    double sumPrice = 0;
    double sumWeight = 0;

    for (auto& item : items) {
      sumPrice += item->getPrice();
      sumWeight += item->getWeight();
    }
    double avgPrice = items.empty() ? 0 : sumPrice / items.size();
    double avgWeight = items.empty() ? 0 : sumWeight / items.size();

    std::cout << "Средняя цена: " << std::fixed << std::setprecision(2)
              << avgPrice << " золота" << std::endl;
    std::cout << "Средний вес: " << avgWeight << " кг" << std::endl;

    std::cout << "\nСтатистика по предметам:" << std::endl;

    analyzeType("Оружие");
    analyzeType("Броня");
    analyzeType("Зелье");
    analyzeType("Свиток");

    std::cout << std::endl;
  }

  void analyzeType(const std::string& type) {
    std::vector<std::variant<int, double, std::string>> params;

    for (const auto& item : items) {
      if (item->getType() == type) {
        params.push_back(item->getSpecParam());
      }
    }

    if (params.empty()) {
      std::cout << "- " << type << ": нет в наличии" << std::endl;
      return;
    }

    // ср знач

    if (type == "Оружие" || type == "Броня") {
      double sum = 0;
      for (const auto& param : params) {
        sum += std::get<int>(param);
      }
      double avg = sum / params.size();
      std::cout << "- " << type << ": средний показатель "
                << (type == "Оружие" ? "урона" : "защиты") << " = " << avg
                << std::endl;
    } else if (type == "Зелье") {
      double sum = 0;
      for (const auto& param : params) {
        sum += std::get<double>(param);
      }
      double avg = sum / params.size();
      std::cout << "- " << type << ": средняя длительность = " << avg
                << std::endl;
    } else if (type == "Свиток") {
      std::map<std::string, int> frequency;
      for (const auto& param : params) {
        frequency[std::get<std::string>(param)]++;
      }

      std::string mostCommon;
      int maxCount = 0;
      for (const auto& [effect, count] : frequency) {
        if (count > maxCount) {
          maxCount = count;
          mostCommon = effect;
        }
      }

      std::cout << "- " << type << ": самый частый эффект " << mostCommon
                << std::endl;
    }
  }
};

// чтение txt
std::vector<Shop*> readFile(const std::string& filename) {
  std::vector<Shop*> shops;
  std::ifstream file(filename);
  std::string line;

  Shop* currentShop = nullptr;

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    if (line.find("Магазин:") == 0) {
      std::string shopName = line.substr(8);
      currentShop = new Shop(shopName);
      shops.push_back(currentShop);
    } else if (line.find("Предметы:") == 0) {
      continue;
    } else {
      std::istringstream isstr(line);
      std::string type, name;
      int price;
      double weight;
      std::string specParam;

      isstr >> type >> name >> price >> weight >> specParam;

      if (type == "Оружие") {
        int damage = std::stoi(specParam);
        currentShop->add(new Weapon(name, price, weight, damage));
      } else if (type == "Броня") {
        int defense = std::stoi(specParam);
        currentShop->add(new Armor(name, price, weight, defense));
      } else if (type == "Зелье") {
        double duration = std::stod(specParam);
        currentShop->add(new Potion(name, price, weight, duration));
      } else if (type == "Свиток") {
        currentShop->add(new Scroll(name, price, weight, specParam));
      }
    }
  }

  file.close();
  return shops;
}

int main() {
  setlocale(LC_ALL, "ru");

  std::vector<Shop*> shops = readFile("shops.txt");

  for (auto& shop : shops) {
    shop->analyze();
  }

  return 0;
}
