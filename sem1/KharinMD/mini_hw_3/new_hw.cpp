#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// ==== ЗАМЕНА std::variant ====
struct SpecParam {
  enum ParamType { INT, DOUBLE, STRING } type;
  int i;
  double d;
  std::string s;

  SpecParam() : type(INT), i(0), d(0.0), s("") {}
  explicit SpecParam(int v) : type(INT), i(v), d(0.0), s("") {}
  explicit SpecParam(double v) : type(DOUBLE), i(0), d(v), s("") {}
  explicit SpecParam(const std::string& v) : type(STRING), i(0), d(0.0), s(v) {}
};

class MagicItem {
 protected:
  std::string name_;
  int price_;
  double weight_;

 public:
  MagicItem(std::string name, int price, double weight)
      : name_(name), price_(price), weight_(weight) {}
  virtual ~MagicItem() {}

  int GetPrice() const { return price_; }
  double GetWeight() const { return weight_; }
  std::string GetName() const { return name_; }

  virtual SpecParam GetSpecParam() const = 0;
  virtual std::string GetType() const = 0;
};

class Weapon : public MagicItem {
  int damage_;

 public:
  Weapon(std::string name, int price, double weight, int damage)
      : MagicItem(name, price, weight), damage_(damage) {}
  SpecParam GetSpecParam() const { return SpecParam(damage_); }
  std::string GetType() const { return "Оружие"; }
};

class Armor : public MagicItem {
  int defense_;

 public:
  Armor(std::string name, int price, double weight, int defense)
      : MagicItem(name, price, weight), defense_(defense) {}
  SpecParam GetSpecParam() const { return SpecParam(defense_); }
  std::string GetType() const { return "Броня"; }
};

class Potion : public MagicItem {
  double duration_;

 public:
  Potion(std::string name, int price, double weight, double duration)
      : MagicItem(name, price, weight), duration_(duration) {}
  SpecParam GetSpecParam() const { return SpecParam(duration_); }
  std::string GetType() const { return "Зелье"; }
};

class Scroll : public MagicItem {
  std::string effect_;

 public:
  Scroll(std::string name, int price, double weight, std::string effect)
      : MagicItem(name, price, weight), effect_(effect) {}
  SpecParam GetSpecParam() const { return SpecParam(effect_); }
  std::string GetType() const { return "Свиток"; }
};

struct Shop {
  std::string name_;
  std::vector<MagicItem*> items_;
};

void PrintStat(const std::string& type,
               std::map<std::string, std::vector<MagicItem*> >& groups) {
  if (groups[type].empty()) {
    std::cout << "- " << type << ": нет в наличии" << std::endl;
    return;
  }

  std::vector<MagicItem*>& vec = groups[type];

  if (type == "Свиток") {
    std::map<std::string, int> freq;
    for (size_t i = 0; i < vec.size(); ++i) {
      SpecParam p = vec[i]->GetSpecParam();
      if (p.type == SpecParam::STRING) {
        freq[p.s]++;
      }
    }

    std::string most_effect = freq.begin()->first;
    int max_count = freq.begin()->second;
    for (std::map<std::string, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
      if (it->second > max_count) {
        max_count = it->second;
        most_effect = it->first;
      }
    }

    std::cout << "- Свитки: самый частый эффект " << most_effect << std::endl;
  } else if (type == "Зелье") {
    double sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
      sum += vec[i]->GetSpecParam().d;
    }
    std::cout << "- Зелья: средняя длительность = " << (sum / vec.size()) << std::endl;
  } else if (type == "Оружие") {
    double sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
      sum += vec[i]->GetSpecParam().i;
    }
    std::cout << "- Оружие: средний урон = " << (sum / vec.size()) << std::endl;
  } else if (type == "Броня") {
    double sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
      sum += vec[i]->GetSpecParam().i;
    }
    std::cout << "- Броня: средняя защита = " << (sum / vec.size()) << std::endl;
  }
}

int main() {
  std::ifstream file("data.txt");
  if (!file) {
    std::cout << "Не удалось открыть файл!" << std::endl;
    return 1;
  }

  std::vector<Shop> shops;
  std::string word;

  while (file >> word) {
    if (word == "Магазин:") {
      Shop shop;
      file >> shop.name_;
      std::string temp;
      int count;
      file >> temp >> count;  // "Предметы:" N

      for (int i = 0; i < count; ++i) {
        std::string type, name;
        int price;
        double weight;

        file >> type >> name >> price >> weight;

        if (type == "Оружие") {
          int dmg;
          file >> dmg;
          shop.items_.push_back(new Weapon(name, price, weight, dmg));
        } else if (type == "Броня") {
          int def;
          file >> def;
          shop.items_.push_back(new Armor(name, price, weight, def));
        } else if (type == "Зелье") {
          double dur;
          file >> dur;
          shop.items_.push_back(new Potion(name, price, weight, dur));
        } else if (type == "Свиток") {
          std::string eff;
          file >> eff;
          shop.items_.push_back(new Scroll(name, price, weight, eff));
        }
      }

      shops.push_back(shop);
    }
  }

  for (size_t s = 0; s < shops.size(); ++s) {
    const Shop& shop = shops[s];

    std::cout << "=== Магазин: " << shop.name_ << " ===" << std::endl;

    int total = shop.items_.size();
    std::cout << "Всего предметов: " << total << std::endl;

    double sum_price = 0;
    double sum_weight = 0;
    for (size_t i = 0; i < shop.items_.size(); ++i) {
      sum_price += shop.items_[i]->GetPrice();
      sum_weight += shop.items_[i]->GetWeight();
    }

    std::cout << "Средняя цена: " << (sum_price / total) << " золота" << std::endl;
    std::cout << "Средний вес: " << (sum_weight / total) << " кг" << std::endl;
    std::cout << "Статистика по предметам:" << std::endl;

    std::map<std::string, std::vector<MagicItem*> > groups;
    for (size_t i = 0; i < shop.items_.size(); ++i) {
      groups[shop.items_[i]->GetType()].push_back(shop.items_[i]);
    }

    PrintStat("Оружие", groups);
    PrintStat("Броня", groups);
    PrintStat("Зелье", groups);
    PrintStat("Свиток", groups);

    std::cout << std::endl;
  }

  return 0;
}
