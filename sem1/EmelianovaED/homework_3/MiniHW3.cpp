#include <windows.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>
// Абстрактный класс MagicItem
class MagicItem {
 protected:
  std::string name_item;
  int price_item;
  double weight_item;

 public:
  virtual std::variant<int, double, std::string> getSpecParam() = 0;
  virtual ~MagicItem() = default;
  int getPrice() const {
    return price_item;
  }  // Геттер для возвращения значения price_item
  double getWeight() const {
    return weight_item;
  }  // Геттер для возвращения значения weight_item
  std::string getName() const {
    return name_item;
  }  // Геттер для возвращения значения name_item
};

class Weapon : public MagicItem {
  int damage_item;

 public:
  // Конструктор Weapon
  Weapon(const std::string& n, int pr, double we, int dam) {
    name_item = n;
    price_item = pr;
    weight_item = we;
    damage_item = dam;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return damage_item;
  }
};

class Armor : public MagicItem {
  int defense_item;

 public:
  // Конструктор Armor
  Armor(const std::string& n, int pr, double we, int def) {
    name_item = n;
    price_item = pr;
    weight_item = we;
    defense_item = def;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return defense_item;
  }
};

class Potion : public MagicItem {
  double duration_item;

 public:
  // Конструктор Potion
  Potion(const std::string& n, int pr, double we, double dur) {
    name_item = n;
    price_item = pr;
    weight_item = we;
    duration_item = dur;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return duration_item;
  }
};

class Scroll : public MagicItem {
  std::string effect_item;

 public:
  // Конструктор Scroll
  Scroll(const std::string& n, int pr, double we, const std::string& dur) {
    name_item = n;
    price_item = pr;
    weight_item = we;
    effect_item = dur;
  }
  std::variant<int, double, std::string> getSpecParam() override {
    return effect_item;
  }
};
// Класс Shop для анализа предметов в магазинах
class Shop {
 private:
  std::string name_shop;
  std::vector<MagicItem*> items;

 public:
  Shop() = default;
  // Запрет копирования, чтобы избежать двойного удаления
  Shop(const Shop&) = delete;
  Shop& operator=(const Shop&) = delete;

  // Разрешение перемещения
  Shop(Shop&& other) noexcept
      : name_shop(std::move(other.name_shop)), items(std::move(other.items)) {
    other.items.clear();
  }
  Shop& operator=(Shop&& other) noexcept {
    if (this != &other) {
      for (MagicItem* it : items) delete it;
      name_shop = std::move(other.name_shop);
      items = std::move(other.items);
      other.items.clear();
    }
    return *this;
  }

  std::string getShopName() const {
    return name_shop;
  }  // Геттер для возварщения названия магазина
  int getItemCount() const {
    return static_cast<int>(items.size());
  }  // Геттер для возварщения количества предметов
  MagicItem* getItem(int index) const {
    if (index >= 0 && index < getItemCount()) {
      return items[index];
    }
    return nullptr;
  }
  void setNameShop(const std::string& n) {
    name_shop = n;
  }  // Сеттер для инициализации name_shop
  void addItem(MagicItem* item) {
    items.push_back(item);
  }  // Добавление предметов

  // Загрузка всех магазинов из файла
  static std::vector<Shop> loadShopsFromFile(const std::string& file_name) {
    std::vector<Shop> shops;
    std::ifstream file(file_name);
    if (!file.is_open()) {
      std::cout << "Ошибка при открывании файла" << std::endl;
      return shops;
    }

    while (true) {
      std::string shop_name;
      if (!(file >> shop_name)) break;  // конец файла

      std::string items_word;
      int items_count = 0;
      if (!(file >> items_word) || items_word != "Предметы" ||
          !(file >> items_count)) {
        // Неправильный формат
        break;
      }

      Shop s;
      s.setNameShop(shop_name);

      for (int i = 0; i < items_count; ++i) {
        std::string type, item_name;
        int item_price;
        double item_weight;
        // конец или ошибка формата
        if (!(file >> type >> item_name >> item_price >> item_weight)) {
          break;
        }
        if (type == "Оружие") {
          int item_damage;
          if (!(file >> item_damage)) break;
          s.addItem(
              new Weapon(item_name, item_price, item_weight, item_damage));
        } else if (type == "Броня") {
          int item_defense;
          if (!(file >> item_defense)) break;
          s.addItem(
              new Armor(item_name, item_price, item_weight, item_defense));
        } else if (type == "Зелье") {
          double item_duration;
          if (!(file >> item_duration)) break;
          s.addItem(
              new Potion(item_name, item_price, item_weight, item_duration));
        } else if (type == "Свиток") {
          std::string item_effect;
          if (!(file >> item_effect)) break;
          s.addItem(
              new Scroll(item_name, item_price, item_weight, item_effect));
        }
      }
      shops.push_back(std::move(s));
    }

    return shops;
  }
  // Анализ предметов магазинов: кол-во предметов, ср. цена, ср. вес, ср. урон,
  // ср. защита, ср. длительность, частый эффект
  void analyzeShop() const {
    int total_price = 0;
    int weapon_count = 0, armor_count = 0, potion_count = 0, scroll_count = 0;
    int weapon_damage_sum = 0, armor_defense_sum = 0;
    double total_weight = 0.0;
    double potion_duration_sum = 0.0;
    std::map<std::string, int> scroll_counts;

    std::cout << "=== Магазин: " << name_shop << " ===" << std::endl;
    int total_items = static_cast<int>(items.size());
    std::cout << "Всего предметов: " << total_items << std::endl;
    if (total_items == 0) {
      std::cout << "Нет предметов для анализа." << std::endl;
      return;
    }

    for (MagicItem* item : items) {
      total_price += item->getPrice();
      total_weight += item->getWeight();

      if (auto* weapon = dynamic_cast<Weapon*>(item)) {
        weapon_count++;
        weapon_damage_sum += std::get<int>(weapon->getSpecParam());
      } else if (auto* armor = dynamic_cast<Armor*>(item)) {
        armor_count++;
        armor_defense_sum += std::get<int>(armor->getSpecParam());
      } else if (auto* potion = dynamic_cast<Potion*>(item)) {
        potion_count++;
        potion_duration_sum += std::get<double>(potion->getSpecParam());
      } else if (auto* scroll = dynamic_cast<Scroll*>(item)) {
        scroll_count++;
        scroll_counts[std::get<std::string>(scroll->getSpecParam())]++;
      }
    }

    double avg_price = static_cast<double>(total_price) / total_items;
    double avg_weight = total_weight / total_items;
    std::cout << "Средняя цена: " << avg_price << " золота" << std::endl;
    std::cout << "Средний вес: " << avg_weight << " кг" << std::endl
              << std::endl;

    std::cout << "Статистика по предметам:" << std::endl;
    if (weapon_count > 0) {
      std::cout << "- Оружие: средний урон = "
                << static_cast<double>(weapon_damage_sum) / weapon_count
                << std::endl;
    } else {
      std::cout << "- Оружие: нет в наличии" << std::endl;
    }
    if (armor_count > 0) {
      std::cout << "- Броня: средняя защита = "
                << static_cast<double>(armor_defense_sum) / armor_count
                << std::endl;
    } else {
      std::cout << "- Броня: нет в наличии" << std::endl;
    }
    if (potion_count > 0) {
      std::cout << "- Зелья: средняя длительность = "
                << potion_duration_sum / potion_count << std::endl;
    } else {
      std::cout << "- Зелья: нет в наличии" << std::endl;
    }
    if (scroll_count > 0) {
      std::string most_common_effect;
      int max_count = 0;
      for (const auto& pr : scroll_counts) {
        if (pr.second > max_count) {
          max_count = pr.second;
          most_common_effect = pr.first;
        }
      }
      std::cout << "- Свитки: самый частый эффект " << most_common_effect
                << std::endl
                << std::endl;
    } else {
      std::cout << "- Свитки: нет в наличии" << std::endl;
    }
  }

  ~Shop() {
    for (MagicItem* item : items) {
      delete item;
    }
  }

  bool isLoaded() const { return !name_shop.empty(); }
};
int analyzeItems() {
  // Загружаем сразу все магазины
  auto shops = Shop::loadShopsFromFile("Shops.txt");
  if (shops.empty()) {
    std::cout << "Не удалось загрузить магазины" << std::endl;
    return 1;
  }

  for (const Shop& shop : shops) {
    std::cout << "Анализ магазина: " << shop.getShopName() << std::endl;
    shop.analyzeShop();
  }
}
int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  setlocale(LC_ALL, "RUS");
  analyzeItems();
  return 0;
}
