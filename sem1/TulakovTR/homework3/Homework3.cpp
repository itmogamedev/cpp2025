#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cstring>
#include <algorithm>
using namespace std;


class Item {
protected:
    string name;
public:
    double price;
    double weight;

    Item(const string& n, double p, double w) : name(n), price(p), weight(w) {}
    virtual ~Item() = default;

    virtual void display() const = 0;
};


class Weapon : public Item {
public:
    double damage;
    Weapon(const string& n, double p, double w, double dmg)
        : Item(n, p, w), damage(dmg) {}

    void display() const override {
        cout << "  - " << name << ": Цена " << price
             << ", Вес " << weight
             << ", Урон " << damage << endl;
    }
};


class Armor : public Item {
public:
    int defense;
    Armor(const string& n, double p, double w, int def)
        : Item(n, p, w), defense(def) {}

    void display() const override {
        cout << "  - " << name << ": Цена " << price
             << ", Вес " << weight
             << ", Защита " << defense << endl;
    }
};


class Potion : public Item {
public:
    double effectPower;
    Potion(const string& n, double p, double w, double effect)
        : Item(n, p, w), effectPower(effect) {}

    void display() const override {
        cout << "  - " << name << ": Название " << name
             << ", Цена " << price
             << ", Вес " << weight
             << ", Эффект " << effectPower << endl;
    }
};


class Scroll : public Item {
public:
    string effectType;
    Scroll(const string& n, double p, double w, const string& effect)
        : Item(n, p, w), effectType(effect) {}

    void display() const override {
        cout << "  - " << name << ": Название " << name
             << ", Цена " << price
             << ", Вес " << weight
             << ", Эффект " << effectType << endl;
    }
};


class Shop {
    string name;
    vector<shared_ptr<Item>> items;
public:
    Shop(const string& n) : name(n) {}

    void addItem(shared_ptr<Item> item) {
        items.push_back(item);
    }

    void display() const {
        cout << "Магазин: " << name << "\nПредметы:\n";
        for (const auto& item : items) {
            item->display();
        }
        cout << endl;
    }

    void printStatistics() const {
        int totalItems = items.size();
        double totalPrice = 0.0;
        double totalWeight = 0.0;
        int weaponCount = 0, armorCount = 0, potionCount = 0, scrollCount = 0;

        for (const auto& item : items) {
            totalPrice += item->price;
            totalWeight += item->weight;

            if (dynamic_cast<Weapon*>(item.get())) {
                ++weaponCount;
            } else if (dynamic_cast<Armor*>(item.get())) {
                ++armorCount;
            } else if (dynamic_cast<Potion*>(item.get())) {
                ++potionCount;
            } else if (dynamic_cast<Scroll*>(item.get())) {
                ++scrollCount;
            }
        }

        cout << "Статистика для магазина: " << name << "\n";
        cout << "Общее число предметов: " << totalItems << "\n";
        cout << "Общая стоимость: " << totalPrice << "\n";
        cout << "Общий вес: " << totalWeight << "\n";
        cout << "Предметов оружия: " << weaponCount << "\n";
        cout << "Предметов брони: " << armorCount << "\n";
        cout << "Зелий: " << potionCount << "\n";
        cout << "Свитков: " << scrollCount << "\n\n";
    }
};


void readData(const string& filename, vector<Shop>& shops) {
    ifstream ifs(filename);
    if (!ifs) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return;
    }

    string line;
    while (getline(ifs, line)) {
        if (line.find("Магазин:") == 0) {
            string shopName = line.substr(strlen("Магазин:"));
            shopName.erase(shopName.find_last_not_of(" \t") + 1);
            shopName.erase(0, shopName.find_first_not_of(" \t"));

            
            if (!getline(ifs, line)) break;
            int itemCount = 0;
            if (line.find("Предметы:") == 0) {
                string countStr = line.substr(strlen("Предметы:"));
                countStr.erase(0, countStr.find_first_not_of(" \t"));
                countStr.erase(countStr.find_last_not_of(" \t") + 1);
                itemCount = stoi(countStr);
            }

            Shop shop(shopName);

            
            for (int i = 0; i < itemCount; ++i) {
                if (!getline(ifs, line)) break;
                istringstream iss(line);
                string type, name;
                double price, weight;
                iss >> type >> name >> price >> weight;

                if (type == "Оружие") { 
                    double damage;
                    iss >> damage;
                    auto item = make_shared<Weapon>(name, price, weight, damage);
                    shop.addItem(item);
                } else if (type == "Броня") { 
                    int defense;
                    iss >> defense;
                    auto item = make_shared<Armor>(name, price, weight, defense);
                    shop.addItem(item);
                } else if (type == "Зелье") { 
                    double effectPower;
                    iss >> effectPower;
                    auto item = make_shared<Potion>("Зелье " + name, price, weight, effectPower);
                    shop.addItem(item);
                } else if (type == "Свиток") { 
                    string effectType;
                    getline(iss >> ws, effectType);
                    auto item = make_shared<Scroll>(name + " свиток", price, weight, effectType);
                    shop.addItem(item);
                }
            }

            shops.push_back(shop);
        }
    }
}

int main() {
    string filename = "data.txt"; 
    vector<Shop> shops;

    readData(filename, shops);

    
    for (const auto& shop : shops) {
        shop.display();
    }

    
    for (const auto& shop : shops) {
        shop.printStatistics();
    }

    return 0;
}