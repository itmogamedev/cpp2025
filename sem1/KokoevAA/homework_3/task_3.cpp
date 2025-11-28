#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

using namespace std;
class MagicItem {
 public:
  string name;
  double price;
  double weight;

  MagicItem(const string& n, int p, double w) : name(n), price(p), weight(w) {}

  virtual ~MagicItem() {}

  virtual string getType() const = 0;

  virtual variant<int, double, string> getSpecParam() const = 0;
};

class Weapon : public MagicItem {
 public:
  int damage;

  Weapon(const string& n, int p, double w, int d)
      : MagicItem(n, p, w), damage(d) {}

  string getType() const override { return "Weapon"; }

  variant<int, double, string> getSpecParam() const override { return damage; }
};

class Armor : public MagicItem {
 public:
  int defense;

  Armor(const string& n, int p, double w, int def)
      : MagicItem(n, p, w), defense(def) {}

  string getType() const override { return "Armor"; }

  variant<int, double, string> getSpecParam() const override { return defense; }
};

class Potion : public MagicItem {
 public:
  double duration;

  Potion(const string& n, int p, double w, double dur)
      : MagicItem(n, p, w), duration(dur) {}

  string getType() const override { return "Potion"; }

  variant<int, double, string> getSpecParam() const override {
    return duration;
  }
};

class Scroll : public MagicItem {
 public:
  string effect;

  Scroll(const string& n, int p, double w, const string& eff)
      : MagicItem(n, p, w), effect(eff) {}

  string getType() const override { return "Scroll"; }

  variant<int, double, string> getSpecParam() const override { return effect; }
};

struct Shop {
  string name;
  vector<MagicItem*> items;
};

void printShopStats(const Shop& shop) {
  cout << "=== Магазин: " << shop.name << " ===" << endl;

  int totalItems = (int)shop.items.size();
  cout << "Всего предметов: " << totalItems << endl;

  double sumPrice = 0;
  double sumWeight = 0;

  long long sumWeaponDamage = 0;
  int countWeapon = 0;

  long long sumArmorDefense = 0;
  int countArmor = 0;

  double sumPotionDuration = 0;
  int countPotion = 0;

  map<string, int> scrollEffects;
  int countScroll = 0;

  for (int i = 0; i < (int)shop.items.size(); i++) {
    MagicItem* item = shop.items[i];

    sumPrice += item->price;
    sumWeight += item->weight;

    string type = item->getType();
    variant<int, double, string> param = item->getSpecParam();

    if (type == "Weapon") {
      int dmg = get<int>(param);
      sumWeaponDamage += dmg;
      countWeapon++;
    } else if (type == "Armor") {
      int def = get<int>(param);
      sumArmorDefense += def;
      countArmor++;
    } else if (type == "Potion") {
      double dur = get<double>(param);
      sumPotionDuration += dur;
      countPotion++;
    } else if (type == "Scroll") {
      string eff = get<string>(param);
      scrollEffects[eff]++;
      countScroll++;
    }
  }

  cout << fixed << setprecision(2);

  if (totalItems > 0) {
    cout << "Средняя цена: " << sumPrice / totalItems << " золота" << endl;
    cout << "Средний вес: " << sumWeight / totalItems << " кг" << endl;
  }

  cout << endl;
  cout << "Статистика по типам:" << endl;

  if (countWeapon > 0) {
    double avgDamage = (double)sumWeaponDamage / countWeapon;
    cout << "- Оружие: средний урон = " << avgDamage << endl;
  } else {
    cout << "- Оружие: нет в наличии" << endl;
  }

  if (countArmor > 0) {
    double avgDefense = (double)sumArmorDefense / countArmor;
    cout << "- Броня: средняя защита = " << avgDefense << endl;
  } else {
    cout << "- Броня: нет в наличии" << endl;
  }

  if (countPotion > 0) {
    double avgDuration = sumPotionDuration / countPotion;
    cout << "- Зелья: средняя длительность = " << avgDuration << endl;
  } else {
    cout << "- Зелья: нет в наличии" << endl;
  }

  if (countScroll > 0) {
    string bestEffect = "";
    int bestCount = 0;

    for (auto it = scrollEffects.begin(); it != scrollEffects.end(); ++it) {
      if (it->second > bestCount) {
        bestCount = it->second;
        bestEffect = it->first;
      }
    }

    cout << "- Свитки: самый частый эффект = " << bestEffect << endl;
  } else {
    cout << "- Свитки: нет в наличии" << endl;
  }

  cout << endl;
}

int main() {
  setlocale(LC_ALL, "Russian");

  ifstream fin("shops.txt");
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл shops.txt" << endl;
    return 1;
  }

  vector<Shop> shops;

  while (true) {
    string word;
    if (!(fin >> word)) {
      break;
    }

    if (word != "Shop:") {
      break;
    }

    string shopName;
    getline(fin, shopName);
    if (!shopName.empty() && shopName[0] == ' ') shopName.erase(0, 1);

    Shop shop;
    shop.name = shopName;

    string itemsWord;
    int itemsCount;
    fin >> itemsWord >> itemsCount;

    for (int i = 0; i < itemsCount; i++) {
      string type;
      string itemName;
      double price;
      double weight;

      fin >> type >> itemName >> price >> weight;

      if (type == "Weapon") {
        int damage;
        fin >> damage;
        shop.items.push_back(new Weapon(itemName, price, weight, damage));
      } else if (type == "Armor") {
        int defense;
        fin >> defense;
        shop.items.push_back(new Armor(itemName, price, weight, defense));
      } else if (type == "Potion") {
        double duration;
        fin >> duration;
        shop.items.push_back(new Potion(itemName, price, weight, duration));
      } else if (type == "Scroll") {
        string effect;
        fin >> effect;
        shop.items.push_back(new Scroll(itemName, price, weight, effect));
      } else {
        cout << "Неизвестный тип предмета: " << type << endl;
      }
    }

    shops.push_back(shop);
  }

  for (int i = 0; i < (int)shops.size(); i++) {
    printShopStats(shops[i]);
  }

  for (int i = 0; i < (int)shops.size(); i++) {
    for (int j = 0; j < (int)shops[i].items.size(); j++) {
      delete shops[i].items[j];
    }
  }

  return 0;
}
