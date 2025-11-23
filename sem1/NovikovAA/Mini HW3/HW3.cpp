#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>
#include <variant>
#include <vector>

using namespace std;

class MagicItem {
 public:
  string name;
  int price;
  double weight;

  MagicItem(string n, int p, double w) : name(n), price(p), weight(w) {}
  virtual ~MagicItem() = default;
  virtual std::variant<int, double, string> getSpecParam() const = 0;
};

class Weapon : public MagicItem {
 public:
  int damage;
  Weapon(string n, int p, double w, int d) : MagicItem(n, p, w), damage(d) {}
  std::variant<int, double, string> getSpecParam() const override {
    return damage;
  }
};

class Armor : public MagicItem {
 public:
  int defense;
  Armor(string n, int p, double w, int d) : MagicItem(n, p, w), defense(d) {}
  std::variant<int, double, string> getSpecParam() const override {
    return defense;
  }
};

class Potion : public MagicItem {
 public:
  double duration;
  Potion(string n, int p, double w, double d)
      : MagicItem(n, p, w), duration(d) {}
  std::variant<int, double, string> getSpecParam() const override {
    return duration;
  }
};

class Scroll : public MagicItem {
 public:
  string effect;
  Scroll(string n, int p, double w, string e) : MagicItem(n, p, w), effect(e) {}
  std::variant<int, double, string> getSpecParam() const override {
    return effect;
  }
};

struct Shop {
  string name;
  vector<shared_ptr<MagicItem>> items;
};

vector<Shop> readDataFromFile(const string& filename) {
  ifstream file(filename);
  vector<Shop> shops;
  string line;

  while (getline(file, line)) {
    if (line.rfind("Shop: ", 0) == 0) {
      string shopName = line.substr(line.find(":") + 2);

      getline(file, line);
      int numItems = stoi(line.substr(line.find(":") + 2));

      Shop shop;
      shop.name = shopName;

      for (int i = 0; i < numItems; i++) {
        getline(file, line);
        stringstream ss(line);

        string type, name;
        int price;
        double weight;

        ss >> type >> name >> price >> weight;

        if (type == "Weapon") {
          int damage;
          ss >> damage;
          shop.items.push_back(
              make_shared<Weapon>(name, price, weight, damage));
        } else if (type == "Armor") {
          int defense;
          ss >> defense;
          shop.items.push_back(
              make_shared<Armor>(name, price, weight, defense));
        } else if (type == "Potion") {
          double duration;
          ss >> duration;
          shop.items.push_back(
              make_shared<Potion>(name, price, weight, duration));
        } else if (type == "Scroll") {
          string effect;
          ss >> effect;
          shop.items.push_back(
              make_shared<Scroll>(name, price, weight, effect));
        }
      }
      shops.push_back(shop);
    }
  }
  return shops;
}

void printShopStats(const Shop& shop) {
  cout << "\n=== Shop: " << shop.name << " ===\n";
  cout << "Items: " << shop.items.size() << "\n";

  double totalPrice = 0, totalWeight = 0;

  map<string, vector<std::variant<int, double, string>>> stats;

  for (auto& item : shop.items) {
    totalPrice += item->price;
    totalWeight += item->weight;

    string type;
    if (dynamic_cast<Weapon*>(item.get()))
      type = "Weapon";
    else if (dynamic_cast<Armor*>(item.get()))
      type = "Armor";
    else if (dynamic_cast<Potion*>(item.get()))
      type = "Potion";
    else if (dynamic_cast<Scroll*>(item.get()))
      type = "Scroll";

    stats[type].push_back(item->getSpecParam());
  }

  cout << "Average price: " << totalPrice / shop.items.size();
  cout << " Average weight: " << totalWeight / shop.items.size();

  cout << "\nItem Stats:\n";

  if (stats["Weapon"].empty())
    cout << "- Weapon: out of stock\n";
  else {
    int sum = 0;
    for (auto& v : stats["Weapon"]) sum += get<int>(v);
    cout << "- Weapon: average damage = " << sum / stats["Weapon"].size()
         << "\n";
  }

  if (stats["Armor"].empty())
    cout << "- Armor: out of stock\n";
  else {
    int sum = 0;
    for (auto& v : stats["Armor"]) sum += get<int>(v);
    cout << "- Armor: average defense = " << sum / stats["Armor"].size()
         << "\n";
  }

  if (stats["Potion"].empty())
    cout << "- Potion: out of stock\n";
  else {
    double sum = 0;
    for (auto& v : stats["Potion"]) sum += get<double>(v);
    cout << "- Potion: average duration = " << sum / stats["Potion"].size()
         << "\n";
  }

  if (stats["Scroll"].empty())
    cout << "- Scroll: out of stock\n";
  else {
    map<string, int> freq;
    for (auto& v : stats["Scroll"]) freq[get<string>(v)]++;

    string most;
    int best = 0;
    for (auto& p : freq) {
      if (p.second > best) {
        most = p.first;
        best = p.second;
      }
    }
    cout << "- Scrolls: most common effect = " << most << "\n";
  }
}

int main() {
  vector<Shop> shops = readDataFromFile("shops.txt");

  for (auto& shop : shops) {
    printShopStats(shop);
  }

  return 0;
}
