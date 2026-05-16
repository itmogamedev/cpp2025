#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using SpecVar = std::variant<int, double, std::string>;

// ===== Базовый и дочерние классы =====

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem(const std::string& n, int p, double w)
      : name(n), price(p), weight(w) {}

  virtual ~MagicItem() = default;

  int getPrice() const { return price; }
  double getWeight() const { return weight; }

  virtual SpecVar getSpecParam() const = 0;
  virtual std::string getType() const = 0;
};

class Weapon : public MagicItem {
  int damage;

 public:
  Weapon(const std::string& n, int p, double w, int d)
      : MagicItem(n, p, w), damage(d) {}

  SpecVar getSpecParam() const override { return damage; }
  std::string getType() const override { return "Weapon"; }
};

class Armor : public MagicItem {
  int defense;

 public:
  Armor(const std::string& n, int p, double w, int d)
      : MagicItem(n, p, w), defense(d) {}

  SpecVar getSpecParam() const override { return defense; }
  std::string getType() const override { return "Armor"; }
};

class Potion : public MagicItem {
  double duration;

 public:
  Potion(const std::string& n, int p, double w, double dur)
      : MagicItem(n, p, w), duration(dur) {}

  SpecVar getSpecParam() const override { return duration; }
  std::string getType() const override { return "Potion"; }
};

class Scroll : public MagicItem {
  std::string effect;

 public:
  Scroll(const std::string& n, int p, double w, const std::string& e)
      : MagicItem(n, p, w), effect(e) {}

  SpecVar getSpecParam() const override { return effect; }
  std::string getType() const override { return "Scroll"; }
};

// ===== Данные по магазину =====

struct ShopData {
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;
};

// ===== Чтение файла со всеми магазинами =====

std::vector<ShopData> readFile() {
  std::ifstream file("task_1.txt");
  std::vector<ShopData> shops;

  if (!file.is_open()) {
    std::cerr << "Не удалось открыть task_1.txt\n";
    return shops;
  }

  ShopData current;
  bool haveShop = false;

  std::string line, key;
  std::string shop_name, num_items;
  std::string item_name;
  int price;
  double weight;
  int intSpec;
  double dblSpec;
  std::string strSpec;

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    std::istringstream iss(line);
    iss >> key;

    if (key == "===" || key == "Магазин:") {
      if (haveShop) {
        shops.push_back(std::move(current));
        current = ShopData{};
      }
      iss >> shop_name;
      current.name = shop_name;
      haveShop = true;
    } else if (key == "Items:" || key == "Предметы:") {
      iss >> num_items;  // можно просто проигнорировать
    } else if (key == "Weapon" || key == "Оружие") {
      iss >> item_name >> price >> weight >> intSpec;
      current.items.push_back(
          std::make_unique<Weapon>(item_name, price, weight, intSpec));
    } else if (key == "Armor" || key == "Броня") {
      iss >> item_name >> price >> weight >> intSpec;
      current.items.push_back(
          std::make_unique<Armor>(item_name, price, weight, intSpec));
    } else if (key == "Potion" || key == "Зелье") {
      iss >> item_name >> price >> weight >> dblSpec;
      current.items.push_back(
          std::make_unique<Potion>(item_name, price, weight, dblSpec));
    } else if (key == "Scroll" || key == "Свиток") {
      iss >> item_name >> price >> weight >> strSpec;
      current.items.push_back(
          std::make_unique<Scroll>(item_name, price, weight, strSpec));
    }
  }

  if (haveShop) {
    shops.push_back(std::move(current));
  }

  return shops;
}

// ===== Вспомогательные функции для средних =====

double avgInt(const std::vector<int>& v) {
  if (v.empty()) return 0.0;
  long long s = 0;
  for (int x : v) s += x;
  return static_cast<double>(s) / v.size();
}

double avgDouble(const std::vector<double>& v) {
  if (v.empty()) return 0.0;
  double s = 0.0;
  for (double x : v) s += x;
  return s / v.size();
}

std::string mostFrequent(const std::vector<std::string>& v) {
  if (v.empty()) return "";
  std::map<std::string, int> freq;
  for (auto& s : v) freq[s]++;
  std::string best;
  int bestCnt = 0;
  for (auto& [val, cnt] : freq) {
    if (cnt > bestCnt) {
      bestCnt = cnt;
      best = val;
    }
  }
  return best;
}

// ===== Расчёт и вывод статистики по магазину =====

void printShopStats(const ShopData& shop) {
  int totalItems = static_cast<int>(shop.items.size());
  double sumPrice = 0.0;
  double sumWeight = 0.0;

  std::vector<int> weaponDamage;
  std::vector<int> armorDefense;
  std::vector<double> potionDuration;
  std::vector<std::string> scrollEffects;

  for (const auto& ptr : shop.items) {
    sumPrice += ptr->getPrice();
    sumWeight += ptr->getWeight();

    std::string type = ptr->getType();
    SpecVar sp = ptr->getSpecParam();

    if ((type == "Weapon" || type == "Оружие") &&
        std::holds_alternative<int>(sp))
      weaponDamage.push_back(std::get<int>(sp));
    else if ((type == "Armor" || type == "Броня") &&
             std::holds_alternative<int>(sp))
      armorDefense.push_back(std::get<int>(sp));
    else if ((type == "Potion" || type == "Зелье") &&
             std::holds_alternative<double>(sp))
      potionDuration.push_back(std::get<double>(sp));
    else if ((type == "Scroll" || type == "Свиток") &&
             std::holds_alternative<std::string>(sp))
      scrollEffects.push_back(std::get<std::string>(sp));
  }

  double midPrice = totalItems ? sumPrice / totalItems : 0.0;
  double midWeight = totalItems ? sumWeight / totalItems : 0.0;

  std::cout << "=== Магазин: " << shop.name << " ===\n";
  std::cout << "Всего предметов: " << totalItems << "\n";
  std::cout << "Средняя цена: " << std::fixed << std::setprecision(2)
            << midPrice << " золота\n";
  std::cout << "Средний вес: " << std::fixed << std::setprecision(2)
            << midWeight << " кг\n\n";

  std::cout << "Статистика по предметам:\n";

  if (!weaponDamage.empty())
    std::cout << "- Оружие: средний урон = " << std::fixed
              << std::setprecision(0) << avgInt(weaponDamage) << "\n";
  else
    std::cout << "- Оружие: нет в наличии\n";

  if (!armorDefense.empty())
    std::cout << "- Броня: средняя защита = " << std::fixed
              << std::setprecision(0) << avgInt(armorDefense) << "\n";
  else
    std::cout << "- Броня: нет в наличии\n";

  if (!potionDuration.empty())
    std::cout << "- Зелья: средняя длительность = " << std::fixed
              << std::setprecision(1) << avgDouble(potionDuration) << "\n";
  else
    std::cout << "- Зелья: нет в наличии\n";

  if (!scrollEffects.empty())
    std::cout << "- Свитки: самый частый эффект = "
              << mostFrequent(scrollEffects) << "\n";
  else
    std::cout << "- Свитки: нет в наличии\n";

  std::cout << "\n";
}

// ===== main =====

int main() {
  std::setlocale(LC_ALL, "ru");

  std::vector<ShopData> shops = readFile();

  for (const auto& shop : shops) {
    printShopStats(shop);
  }
}
