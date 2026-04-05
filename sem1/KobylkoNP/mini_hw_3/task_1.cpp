#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

// Абстрактный базовый класс
class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& n, int p, double w)
      : name(n), price(p), weight(w) {}
  virtual ~MagicItem() = default;

  // Чисто виртуальный метод для получения специфического параметра
  virtual std::variant<int, double, std::string> getSpecParam() const = 0;

  // Геттеры
  std::string getName() const { return name; }
  int getPrice() const { return price; }
  double getWeight() const { return weight; }

  // Виртуальный метод для получения типа предмета
  virtual std::string getType() const = 0;
};

// Класс Оружие
class Weapon : public MagicItem {
 private:
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int d)
      : MagicItem(n, p, w), damage(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }

  std::string getType() const override { return "Weapon"; }
};

// Класс Броня
class Armor : public MagicItem {
 private:
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int d)
      : MagicItem(n, p, w), defense(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return defense;
  }

  std::string getType() const override { return "Armor"; }
};

// Класс Зелье
class Potion : public MagicItem {
 private:
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double d)
      : MagicItem(n, p, w), duration(d) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }

  std::string getType() const override { return "Potion"; }
};

// Класс Свиток
class Scroll : public MagicItem {
 private:
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& e)
      : MagicItem(n, p, w), effect(e) {}

  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }

  std::string getType() const override { return "Scroll"; }
};

// Класс для представления магазина
class Shop {
 private:
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;

 public:
  Shop(const std::string& n) : name(n) {}

  void addItem(std::unique_ptr<MagicItem> item) {
    items.push_back(std::move(item));
  }

  // Вычисление средней цены
  double getAveragePrice() const {
    if (items.empty()) return 0.0;
    double total = 0;
    for (const auto& item : items) {
      total += item->getPrice();
    }
    return total / items.size();
  }

  // Вычисление среднего веса
  double getAverageWeight() const {
    if (items.empty()) return 0.0;
    double total = 0;
    for (const auto& item : items) {
      total += item->getWeight();
    }
    return total / items.size();
  }

  // Получение статистики по типам предметов
  void printTypeStatistics() const {
    std::map<std::string, std::vector<std::variant<int, double, std::string>>>
        typeParams;

    // Группировка параметров по типам
    for (const auto& item : items) {
      typeParams[item->getType()].push_back(item->getSpecParam());
    }

    // Вывод статистики для каждого типа
    std::vector<std::string> allTypes = {"Weapon", "Armor", "Potion", "Scroll"};

    for (const auto& type : allTypes) {
      std::cout << "- " << type << ": ";

      if (typeParams.find(type) == typeParams.end()) {
        std::cout << "not available" << std::endl;
        continue;
      }

      const auto& params = typeParams[type];

      if (type == "Weapon" || type == "Armor") {
        // Для оружия и брони - среднее значение int
        double sum = 0;
        for (const auto& param : params) {
          sum += std::get<int>(param);
        }
        std::cout << "average " << (type == "Weapon" ? "damage" : "defense")
                  << " = " << static_cast<int>(sum / params.size())
                  << std::endl;
      } else if (type == "Potion") {
        // Для зелий - среднее значение double
        double sum = 0;
        for (const auto& param : params) {
          sum += std::get<double>(param);
        }
        std::cout << "average duration = " << std::fixed << std::setprecision(1)
                  << sum / params.size() << std::endl;
        std::cout.unsetf(std::ios_base::floatfield);
      } else if (type == "Scroll") {
        // Для свитков - самый частый эффект
        std::map<std::string, int> effectCount;
        for (const auto& param : params) {
          effectCount[std::get<std::string>(param)]++;
        }

        std::string mostCommon;
        int maxCount = 0;
        for (const auto& pair : effectCount) {
          if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommon = pair.first;
          }
        }
        std::cout << "most frequent effect " << mostCommon << std::endl;
      }
    }
  }

  void printReport() const {
    std::cout << "=== Shop: " << name << " ===" << std::endl;
    std::cout << "Total items: " << items.size() << std::endl << std::endl;

    std::cout << "Average price: " << std::fixed << std::setprecision(2)
              << getAveragePrice() << " gold" << std::endl;
    std::cout << "Average weight: " << std::fixed << std::setprecision(2)
              << getAverageWeight() << " kg" << std::endl
              << std::endl;

    std::cout << "Item statistics:" << std::endl;
    printTypeStatistics();
    std::cout << std::endl;
  }

  const std::string& getName() const { return name; }
  size_t getItemCount() const { return items.size(); }
};

// Функция для чтения данных из файла
std::vector<Shop> readShopsFromFile(const std::string& filename) {
  std::vector<Shop> shops;
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Error: could not open file " << filename << std::endl;
    std::cerr << "Make sure the file exists in the same folder as the program"
              << std::endl;
    return shops;
  }

  Shop* currentShop = nullptr;
  int expectedItems = 0;
  int readItems = 0;

  while (std::getline(file, line)) {
    // Пропускаем пустые строки
    if (line.empty()) continue;

    std::istringstream iss(line);
    std::string firstWord;
    iss >> firstWord;

    if (firstWord == "Shop:") {
      // Если мы читали предыдущий магазин, проверяем количество предметов
      if (currentShop && expectedItems > 0 && readItems != expectedItems) {
        std::cout << "Warning: in shop " << currentShop->getName()
                  << " expected " << expectedItems << " items, but read "
                  << readItems << std::endl;
      }

      std::string shopName;
      std::getline(iss, shopName);
      // Удаляем начальный пробел
      if (!shopName.empty() && shopName[0] == ' ') {
        shopName = shopName.substr(1);
      }
      shops.emplace_back(shopName);
      currentShop = &shops.back();
      readItems = 0;
    } else if (firstWord == "Items:") {
      if (currentShop) {
        iss >> expectedItems;
      }
    } else if (currentShop && !firstWord.empty()) {
      // Чтение данных предмета
      std::string type, name;
      int price;
      double weight;
      std::string specParamStr;

      type = firstWord;
      if (!(iss >> name >> price >> weight >> specParamStr)) {
        std::cerr << "Error reading item data in shop: "
                  << currentShop->getName() << std::endl;
        continue;
      }

      // Создание соответствующего объекта
      try {
        if (type == "Weapon") {
          int damage = std::stoi(specParamStr);
          currentShop->addItem(
              std::make_unique<Weapon>(name, price, weight, damage));
          readItems++;
        } else if (type == "Armor") {
          int defense = std::stoi(specParamStr);
          currentShop->addItem(
              std::make_unique<Armor>(name, price, weight, defense));
          readItems++;
        } else if (type == "Potion") {
          double duration = std::stod(specParamStr);
          currentShop->addItem(
              std::make_unique<Potion>(name, price, weight, duration));
          readItems++;
        } else if (type == "Scroll") {
          currentShop->addItem(
              std::make_unique<Scroll>(name, price, weight, specParamStr));
          readItems++;
        } else {
          std::cerr << "Unknown item type: " << type
                    << " in shop: " << currentShop->getName() << std::endl;
        }
      } catch (const std::exception& e) {
        std::cerr << "Error processing item " << name << " in shop "
                  << currentShop->getName() << ": " << e.what() << std::endl;
      }
    }
  }

  // Проверка для последнего магазина
  if (currentShop && expectedItems > 0 && readItems != expectedItems) {
    std::cout << "Warning: in shop " << currentShop->getName() << " expected "
              << expectedItems << " items, but read " << readItems << std::endl;
  }

  file.close();
  return shops;
}

int main() {
  std::string filename = "magic_shops.txt";

  std::cout << "Reading data from file: " << filename << "\n" << std::endl;

  // Чтение данных из файла
  std::vector<Shop> shops = readShopsFromFile(filename);

  if (shops.empty()) {
    std::cerr << "Failed to load shop data." << std::endl;
    std::cerr << "Please check:" << std::endl;
    std::cerr << "1. If file " << filename << " exists" << std::endl;
    std::cerr << "2. If the data format in the file is correct" << std::endl;
    std::cerr << "3. If the file is in the correct folder" << std::endl;
    return 1;
  }

  std::cout << "Successfully loaded shops: " << shops.size() << "\n"
            << std::endl;

  // Вывод отчетов для каждого магазина
  for (const auto& shop : shops) {
    shop.printReport();
  }

  std::cout << "Analysis completed. Press Enter to exit...";
  std::cin.get();

  return 0;
}
