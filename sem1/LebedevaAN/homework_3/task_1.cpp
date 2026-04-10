#include <iostream>
#include <fstream>
#include <variant>
#include <vector>
#include <map>
#include <io.h>
#include <fcntl.h>
#include <codecvt>

class MagicItem {
 protected:
  std::wstring name_;
  int price_;
  double weight_;
 public:
  MagicItem(const std::wstring &name, int price, double weight) : name_(name), price_(price), weight_(weight) {}
  virtual std::variant<int, double, std::wstring> getSpecialParam() const = 0;

  virtual std::wstring getItemName() const = 0;

  friend class Shop;
};

class Healing : public MagicItem {
 public:
  Healing(const std::wstring &name, int price, double weight, int health_points) : MagicItem(name, price, weight),
                                                                                   health_points_(health_points) {};
  std::variant<int, double, std::wstring> getSpecialParam() const {
    return health_points_;
  }

  std::wstring getItemName() const {
    return L"Лечение";
  }
 private:
  int health_points_;
};

class Joke : public MagicItem {
 public:
  Joke(const std::wstring &name, int price, double weight, const std::wstring &anecdote) : MagicItem(name,
                                                                                                     price,
                                                                                                     weight),
                                                                                           anecdote_(anecdote) {};
  std::variant<int, double, std::wstring> getSpecialParam() const {
    return anecdote_;
  }

  std::wstring getItemName() const {
    return L"Шутка";
  }
 private:
  std::wstring anecdote_;
};

class Defense : public MagicItem {
 public:
  Defense(const std::wstring &name, int price, double weight, double damage_reduction) : MagicItem(name, price, weight),
                                                                                         damage_reduction_(
                                                                                             damage_reduction) {};
  std::variant<int, double, std::wstring> getSpecialParam() const {
    return damage_reduction_;
  }

  std::wstring getItemName() const {
    return L"Защита";
  }
 private:
  double damage_reduction_;
};

class Dice : public MagicItem {
 public:
  Dice(const std::wstring &name, int price, double weight, int dice_luck) : MagicItem(name, price, weight),
                                                                            dice_luck_(dice_luck) {};

  std::variant<int, double, std::wstring> getSpecialParam() const {
    return dice_luck_;
  }

  std::wstring getItemName() const {
    return L"Кубик";
  }
 private:
  int dice_luck_;
};

class Shop {
 public:
  Shop(std::wstring shop_name) : shop_name_(shop_name) {}

  void addItem(std::wstring item_type, const std::wstring name, int cost, double weight, std::wstring special_param) {
    if (item_type == L"Лечение") {
      shop_items_.push_back(new Healing(name, cost, weight, std::stoi(special_param)));
    } else if (item_type == L"Защита") {
      shop_items_.push_back(new Defense(name, cost, weight, std::stod(special_param)));
    } else if (item_type == L"Шутка") {
      shop_items_.push_back(new Joke(name, cost, weight, special_param));
    } else if (item_type == L"Кубик") {
      shop_items_.push_back(new Dice(name, cost, weight, std::stoi(special_param)));
    }
  }

  void printStats() {
    std::wcout << L"=== Магазин: " << shop_name_ << L" ===\n";
    printSize();
    printAverageWeight();
    printAverageCost();
    printSpecialParams();
    std::wcout << L"\n\n";
  };

  void printSize() {
    std::wcout << L"Всего предметов: " << shop_items_.size() << L"\n";
  }

  void printAverageWeight() {
    double weight_sum = 0;
    for (auto i : shop_items_) {
      weight_sum += i->weight_;
    }

    std::wcout << L"Средний вес: " << double(weight_sum) / shop_items_.size() << L" кг\n";
  }

  void printAverageCost() {
    double cost_sum = 0;
    for (auto i : shop_items_) {
      cost_sum += i->price_;
    }

    std::wcout << L"Средняя стоимость: " << double(cost_sum) / shop_items_.size() << L" золота\n";
  }

  void printSpecialParams() {
    std::vector<int> healing;
    std::vector<int> dice;
    std::vector<double> defense;
    std::map<std::wstring, int> joke;

    for (auto i : shop_items_) {
      if (i->getItemName() == L"Лечение") {
        healing.push_back(get<int>(i->getSpecialParam()));
      } else if (i->getItemName() == L"Защита") {
        defense.push_back(get<double>(i->getSpecialParam()));
      } else if (i->getItemName() == L"Шутка") {
        if (joke.contains(get<std::wstring>(i->getSpecialParam()))) {
          ++joke[get<std::wstring>(i->getSpecialParam())];
        } else {
          joke[get<std::wstring>(i->getSpecialParam())] = 1;
        }
      } else if (i->getItemName() == L"Кубик") {
        dice.push_back(get<int>(i->getSpecialParam()));
      }
    }

    if (healing.size() == 0) {
      std::wcout << L"- Лечение: нет в наличии.\n";
    } else {
      double sum = 0;
      for (auto i : healing) {
        sum += i;
      }

      std::wcout << L"- Лечение: среднее число очков здоровья = " << sum / healing.size() << "\n";
    }

    if (defense.size() == 0) {
      std::wcout << L"- Защита: нет в наличии.\n";
    } else {
      double sum = 0;
      for (auto i : defense) {
        sum += i;
      }

      std::wcout << L"- Защита: среднее сопротивление к урону = " << sum / defense.size() << "\n";
    }

    if (joke.size() == 0) {
      std::wcout << L"- Шутка: нет в наличии.\n";
    } else {
      std::wstring most_frequent_joke = {};
      int max_count = 0;

      for (auto const &[key, val] : joke) {
        if (val > max_count) {
          max_count = val;
          most_frequent_joke = key;
        }
      }

      std::wcout << L"- Шутка: самая частая шутка = " << most_frequent_joke << "\n";
    }

    if (dice.size() == 0) {
      std::wcout << L"- Кубик: нет в наличии.\n";
    } else {
      double sum = 0;
      for (auto i : dice) {
        sum += i;
      }

      std::wcout << L"- Кубик: средняя удача = " << sum / dice.size() << "\n";
    }
  }

 private:
  std::wstring shop_name_;
  std::vector<MagicItem *> shop_items_;
};

int main() {
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stderr), _O_U16TEXT);

  std::wstring shop_name;
  std::wstring skip_word;
  int goods_quantity;

  std::wstring item_type;
  std::wstring name;
  int cost;
  double weight;
  std::wstring special_param;

  std::wifstream shop_file(L"MAGIC_SHOPS.txt");
  shop_file.imbue(std::locale(shop_file.getloc(), new std::codecvt_utf8<wchar_t>));

  while (shop_file >> skip_word) {
    shop_file >> shop_name;
    shop_file >> skip_word >> goods_quantity;
    Shop shop(shop_name);

    for (int i = 0; i < goods_quantity; ++i) {
      shop_file >> item_type;
      shop_file >> name;
      shop_file >> cost;
      shop_file >> weight;
      shop_file >> special_param;
      shop.addItem(item_type, name, cost, weight, special_param);
    }

    shop.printStats();
  }

  shop_file.close();
}