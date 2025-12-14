#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
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
  MagicItem(const std::string& n, int p, double w)
      : name(n), price(p), weight(w) {}
  virtual ~MagicItem() = default;

  const std::string& getName() const { return name; }
  int getPrice() const { return price; }
  double getWeight() const { return weight; }

  virtual std::string getTypeName() const = 0;
  virtual std::variant<int, double, std::string> getSpecParam() const = 0;
};

class Weapon : public MagicItem {
 public:
  int damage;

  Weapon(const std::string& n, int p, double w, int d)
      : MagicItem(n, p, w), damage(d) {}

  std::string getTypeName() const override { return "Weapon"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return damage;
  }
};

class Armor : public MagicItem {
 public:
  int defense;

  Armor(const std::string& n, int p, double w, int def)
      : MagicItem(n, p, w), defense(def) {}

  std::string getTypeName() const override { return "Armor"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return defense;
  }
};

class Potion : public MagicItem {
 public:
  double duration;

  Potion(const std::string& n, int p, double w, double dur)
      : MagicItem(n, p, w), duration(dur) {}

  std::string getTypeName() const override { return "Potion"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return duration;
  }
};

class Scroll : public MagicItem {
 public:
  std::string effect;

  Scroll(const std::string& n, int p, double w, const std::string& eff)
      : MagicItem(n, p, w), effect(eff) {}

  std::string getTypeName() const override { return "Scroll"; }

  std::variant<int, double, std::string> getSpecParam() const override {
    return effect;
  }
};

struct Shop {
  std::string name;
  std::vector<std::unique_ptr<MagicItem>> items;
};

static std::string trim(const std::string& s) {
  size_t left = 0;
  while (left < s.size() && std::isspace(static_cast<unsigned char>(s[left]))) {
    ++left;
  }
  size_t right = s.size();
  while (right > left &&
         std::isspace(static_cast<unsigned char>(s[right - 1]))) {
    --right;
  }
  return s.substr(left, right - left);
}

void readShopsFromFile(const std::string& filename, std::vector<Shop>& shops) {
  std::ifstream in(filename);
  std::string line;

  while (std::getline(in, line)) {
    line = trim(line);
    if (line.rfind("Shop:", 0) != 0) continue;

    Shop shop;
    shop.name = trim(line.substr(std::string("Shop:").length()));

    while (std::getline(in, line)) {
      line = trim(line);
      if (line.empty()) continue;
      if (line.rfind("Items:", 0) == 0) break;
    }

    int item_count = std::stoi(trim(line.substr(line.find(':') + 1)));

    for (int i = 0; i < item_count; ++i) {
      std::getline(in, line);
      line = trim(line);
      if (line.empty()) {
        --i;
        continue;
      }

      std::istringstream iss(line);
      std::string type, item_name;
      int price;
      double weight;
      iss >> type >> item_name >> price >> weight;

      std::string spec;
      std::getline(iss, spec);
      spec = trim(spec);

      if (type == "Weapon") {
        shop.items.push_back(std::make_unique<Weapon>(item_name, price, weight,
                                                      std::stoi(spec)));
      } else if (type == "Armor") {
        shop.items.push_back(
            std::make_unique<Armor>(item_name, price, weight, std::stoi(spec)));
      } else if (type == "Potion") {
        shop.items.push_back(std::make_unique<Potion>(item_name, price, weight,
                                                      std::stod(spec)));
      } else {
        shop.items.push_back(
            std::make_unique<Scroll>(item_name, price, weight, spec));
      }
    }

    shops.push_back(std::move(shop));
  }
}

void printShopStats(const Shop& shop) {
  std::cout << "=== Shop: " << shop.name << " ===\n";
  size_t total_items = shop.items.size();

  std::cout << "Total items: " << total_items << "\n\n";

  double sum_price = 0.0;
  double sum_weight = 0.0;

  for (const auto& item : shop.items) {
    sum_price += item->getPrice();
    sum_weight += item->getWeight();
  }

  std::cout << std::fixed << std::setprecision(2);

  if (total_items > 0) {
    std::cout << "Average price: " << (sum_price / total_items) << "\n";
    std::cout << "Average weight: " << (sum_weight / total_items) << " kg\n\n";
  }

  int cnt_weapon = 0, cnt_armor = 0, cnt_potion = 0;
  long long sum_weapon = 0, sum_armor = 0;
  double sum_potion = 0.0;
  std::map<std::string, int> freq_scroll;

  for (const auto& item : shop.items) {
    auto param = item->getSpecParam();
    std::string type = item->getTypeName();

    if (type == "Weapon") {
      cnt_weapon++;
      sum_weapon += std::get<int>(param);
    } else if (type == "Armor") {
      cnt_armor++;
      sum_armor += std::get<int>(param);
    } else if (type == "Potion") {
      cnt_potion++;
      sum_potion += std::get<double>(param);
    } else if (type == "Scroll") {
      freq_scroll[std::get<std::string>(param)]++;
    }
  }

  if (cnt_weapon == 0)
    std::cout << "- Weapon: none\n";
  else
    std::cout << "- Weapon: avg damage = " << (double)sum_weapon / cnt_weapon
              << "\n";

  if (cnt_armor == 0)
    std::cout << "- Armor: none\n";
  else
    std::cout << "- Armor: avg defense = " << (double)sum_armor / cnt_armor
              << "\n";

  if (cnt_potion == 0)
    std::cout << "- Potions: none\n";
  else
    std::cout << "- Potions: avg duration = " << (double)sum_potion / cnt_potion
              << "\n";

  if (freq_scroll.empty())
    std::cout << "- Scrolls: none\n";
  else {
    std::string best_effect;
    int best_count = -1;
    for (auto& entry : freq_scroll) {
      if (entry.second > best_count) {
        best_count = entry.second;
        best_effect = entry.first;
      }
    }
    std::cout << "- Scrolls: most common effect = " << best_effect << "\n";
  }

  std::cout << "\n";
}

int main() {
  std::string filename = "shops.txt";

  std::vector<Shop> shops;
  readShopsFromFile(filename, shops);

  for (const auto& shop : shops) {
    printShopStats(shop);
  }

  return 0;
}
