#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cstring>
#include <algorithm> // для remove_if
#include<locale>
#include<windows.h>
#include<cstdlib>


// Базовый класс для предметов
class Item {
protected:
    std::string name;
public:
    double price;
    double weight;

    Item(const std::string& n, double p, double w) : name(n), price(p), weight(w) {}
    virtual ~Item() = default;

    virtual void display() const = 0;
};

// Класс оружия
class Weapon : public Item {
public:
    double damage;
    Weapon(const std::string& n, double p, double w, double dmg)
        : Item(n, p, w), damage(dmg) {}

    void display() const override {
        std::cout << "  - " << name << ": Цена " << price
             << ", Вес " << weight
             << ", Урон " << damage << std::endl;
    }
};

// Класс брони
class Armor : public Item {
public:
    int defense;
    Armor(const std::string& n, double p, double w, int def)
        : Item(n, p, w), defense(def) {}

    void display() const override {
        std::cout << "  - " << name << ": Цена " << price
             << ", Вес " << weight
             << ", Защита " << defense << std::endl;
    }
};

// Класс зелий
class Potion : public Item {
public:
    double effectPower;
    Potion(const std::string& n, double p, double w, double effect)
        : Item(n, p, w), effectPower(effect) {}

    void display() const override {
        std::cout << "  - " << name << ": Название " << name
             << ", Цена " << price
             << ", Вес " << weight
             << ", Эффект " << effectPower << std::endl;
    }
};

// Класс свитков
class Scroll : public Item {
public:
    std::string effectType;
    Scroll(const std::string& n, double p, double w, const std::string& effect)
        : Item(n, p, w), effectType(effect) {}

    void display() const override {
        std::cout << "  - " << name << ": Название " << name
             << ", Цена " << price
             << ", Вес " << weight
             << ", Эффект " << effectType << std::endl;
    }
};

// Класс магазина
class Shop {
    std::string name;
    std::vector<std::shared_ptr<Item>> items;
public:
    Shop(const std::string& n) : name(n) {}

    void addItem(std::shared_ptr<Item> item) {
        items.push_back(item);
    }

    void display() const {
        std::cout << "Магазин: " << name << "\nПредметы:\n";
        for (const auto& item : items) {
            item->display();
        }
        std::cout << std::endl;
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

        std::cout << "Статистика для магазина: " << name << "\n";
        std::cout << "Общее число предметов: " << totalItems << "\n";
        std::cout << "Общая стоимость: " << totalPrice << "\n";
        std::cout << "Общий вес: " << totalWeight << "\n";
        std::cout << "Предметов оружия: " << weaponCount << "\n";
        std::cout << "Предметов брони: " << armorCount << "\n";
        std::cout << "Зелий: " << potionCount << "\n";
        std::cout << "Свитков: " << scrollCount << "\n\n";
    }
};

// Функция для чтения данных из файла
void readData(const std::string& filename, std::vector<Shop>& shops) {
    SetConsoleOutputCP("chcp 1251");
    SetConsoleCP("chcp 1251");
    std::ifstream ifs(filename);
    if (!ifs) {
        std::cout << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(ifs, line)) {
        // Ищем строку с магазином
        if (line.find("Магазин:") == 0) {
            std::string shopName = line.substr(strlen("Магазин:"));
            // Убираем пробелы по краям
            shopName.erase(shopName.find_last_not_of(" \t") + 1);
            shopName.erase(0, shopName.find_first_not_of(" \t"));

            // Следующая строка с количеством предметов
            if (!getline(ifs, line)) break;
            int itemCount = 0;
            if (line.find("Предметы:") == 0) {
                std::string countStr = line.substr(strlen("Предметы:"));
                countStr.erase(0, countStr.find_first_not_of(" \t"));
                countStr.erase(countStr.find_last_not_of(" \t") + 1);
                itemCount = stoi(countStr);
            }

            Shop shop(shopName);

            // Читаем предметы
            for (int i = 0; i < itemCount; ++i) {
                if (!std::getline(ifs, line)) break;
                std::istringstream iss(line);
                std::string type, name;
                double price, weight;
                iss >> type >> name >> price >> weight;

                if (type == "Оружие") { // оружие
                    double damage;
                    iss >> damage;
                    auto item = std::make_shared<Weapon>(name, price, weight, damage);
                    shop.addItem(item);
                } else if (type == "Броня") { // броня
                    int defense;
                    iss >> defense;
                    auto item = std::make_shared<Armor>(name, price, weight, defense);
                    shop.addItem(item);
                } else if (type == "Зелье") { // зелье
                    double effectPower;
                    iss >> effectPower;
                    auto item = std::make_shared<Potion>("Зелье " + name, price, weight, effectPower);
                    shop.addItem(item);
                } else if (type == "Свиток") { // свиток
                    std::string effectType;
                    std::getline(iss >> ws, effectType);
                    auto item = std::make_shared<Scroll>(name + " свиток", price, weight, effectType);
                    shop.addItem(item);
                }
            }

            shops.push_back(shop);
        }
    }
}

int main() {
    SetConsoleOutputCP("chcp 1251");
    SetConsoleCP("chcp 1251");
    std::string filename = "data.txt"; // предполагается, что файл data.txt существует и в нем есть данные
    std::vector<Shop> shops;

    readData(filename, shops);

    // Вывод предметов каждого магазина
    for (const auto& shop : shops) {
        shop.display();
    }

    // Вывод статистики по магазинам
    for (const auto& shop : shops) {
        shop.printStatistics();
    }

    return 0;
}