#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

class MagicItem {
 protected:
  std::string name;
  int price;
  double weight;

 public:
  MagicItem() = default;
  MagicItem(std::string& Name, int& Price, double& Weight)
      : name(Name), price(Price), weight(Weight) {};
  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
};

class Weapon : public MagicItem {
  int damage;

 public:
  Weapon(int& Damage, std::string& Name, int& Price, double& Weight)
      : damage(Damage), MagicItem(Name, Price, Weight) {}
  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }
};

class Armor : public MagicItem {
  int defense;

 public:
  Armor(int& Defense, std::string& Name, int& Price, double& Weight)
      : defense(Defense), MagicItem(Name, Price, Weight) {};
  std::variant<int, double, std::string> getSpecParam() const override {
    return defense;
  }
};

class Potion : public MagicItem {
  double duration;

 public:
  Potion(double& Duration, std::string& Name, int& Price, double& Weight)
      : duration(Duration), MagicItem(Name, Price, Weight) {};
  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }
};

class Scroll : public MagicItem {
  std::string effect;

 public:
  Scroll(std::string& Effect, std::string& Name, int& Price, double& Weight)
      : effect(Effect), MagicItem(Name, Price, Weight) {};
  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }
};
class Shop {
 public:
  std::string name;
  int kol_item{};
  std::vector<std::variant<Weapon, Armor, Potion, Scroll>> object;
  Shop(const std::string& Name, int Kol) : name(Name), kol_item(Kol) {}
};
static std::vector<Shop> Vec;

double getNumericValue(
    const std::variant<Weapon, Armor, Potion, Scroll>& item) {
  return std::visit(
      [](auto&& arg) -> double {
        auto spec_param = arg.getSpecParam();
        return std::visit(
            [](auto&& value) -> double {
              using T = std::decay_t<decltype(value)>;
              if constexpr (std::is_same_v<T, int>) {
                return static_cast<double>(value);
              } else if constexpr (std::is_same_v<T, double>) {
                return value;
              } else if constexpr (std::is_same_v<T, std::string>) {
                return static_cast<double>(value.length());
              }
            },
            spec_param);
      },
      item);
}

double calculateAverageSpecParam(const Shop& shop) {
  if (shop.object.empty()) {
    return 0.0;
  }

  double sum = 0.0;
  for (const auto& item : shop.object) {
    sum += getNumericValue(item);
  }

  return sum / shop.object.size();
}

double calculateOverallAverageSpecParam() {
  if (Vec.empty()) {
    return 0.0;
  }

  double total_sum = 0.0;
  int total_count = 0;

  for (const auto& shop : Vec) {
    if (!shop.object.empty()) {
      double shop_avg = calculateAverageSpecParam(shop);
      total_sum += shop_avg * shop.object.size();
      total_count += shop.object.size();
    }
  }

  return total_count > 0 ? total_sum / total_count : 0.0;
}

template <typename T>
double calculateAverageByType(const Shop& shop) {
  double sum = 0.0;
  int count = 0;

  for (const auto& item : shop.object) {
    if (std::holds_alternative<T>(item)) {
      sum += getNumericValue(item);
      count++;
    }
  }

  return count > 0 ? sum / count : 0.0;
}

void printAllStatistics() {
  std::cout << "=== stat of magazin ===" << std::endl;

  for (size_t i = 0; i < Vec.size(); ++i) {
    const auto& shop = Vec[i];
    std::cout << "\nMaagazin " << (i + 1) << ": " << shop.name << std::endl;
    std::cout << "Number item: " << shop.object.size() << std::endl;

    if (!shop.object.empty()) {
      double avg = calculateAverageSpecParam(shop);
      std::cout << "sr. spec param: " << avg << std::endl;

      // Статистика по типам
      double weapon_avg = calculateAverageByType<Weapon>(shop);
      double armor_avg = calculateAverageByType<Armor>(shop);
      double potion_avg = calculateAverageByType<Potion>(shop);
      double scroll_avg = calculateAverageByType<Scroll>(shop);

      if (weapon_avg > 0)
        std::cout << "  sr. damage weopon: " << weapon_avg << std::endl;
      if (weapon_avg <= 0) std::cout << "  There are no weopon " << std::endl;
      if (armor_avg > 0)
        std::cout << "  sr. defense armor: " << armor_avg << std::endl;
      if (armor_avg <= 0) std::cout << "  There are no armor " << std::endl;
      if (potion_avg > 0)
        std::cout << "  sr. duration of the potions " << potion_avg
                  << std::endl;
      if (potion_avg <= 0) std::cout << "  There are no potion " << std::endl;
      if (scroll_avg > 0)
        std::cout << "  Average scroll effect length: " << scroll_avg
                  << std::endl;
      if (scroll_avg <= 0) std::cout << "  There are no scroll " << std::endl;
    }
  }
}
void Read_from_file(std::string& name, std::string& kol_item,
                    std::string& name_class, std::string& name_item, int& price,
                    std::variant<int, double, std::string>& spec_par,
                    double& weight) {
  std::string line;
  std::ifstream file("magazin.txt");
  if (!file.is_open()) {
    std::cout << "I can't read this file" << std::endl;
    return;
  }
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string key_word;
    iss >> key_word;
    if (key_word == "Magazine:") {
      iss >> name;
      Vec.emplace_back(name, 0);
    }
    if (key_word == "Item:") {
      iss >> kol_item;
      int k = std::stoi(kol_item);
      Vec.back().kol_item = k;
    }
    if (key_word == "Weapon") {
      int spec_par_int;
      iss >> name_item >> price >> weight >> spec_par_int;
      spec_par = spec_par_int;
      Weapon weapon(spec_par_int, name_item, price, weight);
      Vec.back().object.emplace_back(weapon);
    }
    if (key_word == "Armor") {
      int spec_par_int;
      iss >> name_item >> price >> weight >> spec_par_int;
      spec_par = spec_par_int;
      Armor armor(spec_par_int, name_item, price, weight);
      Vec.back().object.emplace_back(armor);
    }
    if (key_word == "Potion") {
      double spec_par_int;
      iss >> name_item >> price >> weight >> spec_par_int;
      spec_par = spec_par_int;
      Potion potion(spec_par_int, name_item, price, weight);
      Vec.back().object.emplace_back(potion);
    }
    if (key_word == "Scroll") {
      std::string spec_par_int;
      iss >> name_item >> price >> weight >> spec_par_int;
      spec_par = spec_par_int;
      Scroll scroll(spec_par_int, name_item, price, weight);
      Vec.back().object.emplace_back(scroll);
    }
  }
  file.close();
};

int main() {
  std::string name, kol_item, name_class, name_item;
  int price;
  std::variant<int, double, std::string> spec_par;
  double weight;

  Read_from_file(name, kol_item, name_class, name_item, price, spec_par,
                 weight);

  printAllStatistics();
  return 0;
}
