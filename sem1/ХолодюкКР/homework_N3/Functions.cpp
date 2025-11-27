#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using specParam = std::variant<int, double, std::string>;

class MagicItem {
protected:
    std::string name;
    int price;
    double weight;

public:
    MagicItem(std::string n, int p, double w)
        : name(std::move(n)), price(p), weight(w) {
    }
    virtual ~MagicItem() = default;
    virtual specParam getSpecParam() const = 0;
    int getPrice() const { return price; }
    double getWeight() const { return weight; }
    std::string getName() const { return name; }
};

class weapon : public MagicItem {
    int damage;
public:
    weapon(std::string n, int p, double w, int d)
        : MagicItem(n, p, w), damage(d) {
    }
    specParam getSpecParam() const override { return damage; }
};

class armor : public MagicItem {
    int protection;
public:
    armor(std::string n, int p, double w, int pr)
        : MagicItem(n, p, w), protection(pr) {
    }
    specParam getSpecParam() const override { return protection; }
};

class potion : public MagicItem {
    double duration;
public:
    potion(std::string n, int p, double w, double d)
        : MagicItem(n, p, w), duration(d) {
    }
    specParam getSpecParam() const override { return duration; }
};

class scroll : public MagicItem {
    int mana;
public:
    scroll(std::string n, int p, double w, int m)
        : MagicItem(n, p, w), mana(m) {
    }
    specParam getSpecParam() const override { return mana; }
};

void func() {
    std::ifstream inputFile("markets.txt", std::ios::app);

    std::string word;
    std::string n;
    int p;
    double w;
    std::string line;
    std::vector<weapon> weapons;
    std::vector<armor> armors;
    std::vector<potion> potions;
    std::vector<scroll> scrolls;


    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;

        std::getline(inputFile, line);
        std::cout << line << std::endl;

        int sum_p = 0;
        double sum_w = 0;
        int counter = line[line.size() - 1] - '0';

        for (int i = 0; i < counter; i++) {
            std::getline(inputFile, line);
            std::istringstream iss(line);

            iss >> word >> n >> p >> w;

            if (word == "Оружие") {
                int d;
                iss >> d;
                weapon item(n, p, w, d);
                weapons.push_back(item);
            }
            if (word == "Броня") {
                int pr;
                iss >> pr;
                armor item(n, p, w, pr);
                armors.push_back(item);
            }
            if (word == "Зелье") {
                double dur;
                iss >> dur;
                potion item(n, p, w, dur);
                potions.push_back(item);
            }
            if (word == "Свиток") {
                int m;
                iss >> m;
                scroll item(n, p, w, m);
                scrolls.push_back(item);
            }
        }
        std::getline(inputFile, line);

        std::cout << "Статистика по предметам:" << std::endl;

        int sum_pr = 0;
        int sum_d = 0;
        double sum_dur = 0;
        int sum_m = 0;

        if (!weapons.empty()) {
            for (weapon item : weapons) {
                sum_p += item.getPrice();
                sum_w += item.getWeight();
                sum_d += std::get<int>(item.getSpecParam());
            }
            std::cout << "- Оружие: средний урон = " << sum_d / weapons.size() << std::endl;
        }
        else {
            std::cout << "- Оружие: нет в наличии" << std::endl;
        }

        if (!armors.empty()) {
            for (armor item : armors) {
                sum_p += item.getPrice();
                sum_w += item.getWeight();
                sum_pr += std::get<int>(item.getSpecParam());
            }
            std::cout << "- Броня: средняя защита = " << sum_pr / armors.size() << std::endl;
        }
        else {
            std::cout << "- Броня: нет в наличии" << std::endl;
        }

        if (!potions.empty()) {
            for (potion item : potions) {
                sum_p += item.getPrice();
                sum_w += item.getWeight();
                sum_dur += std::get<double>(item.getSpecParam());
            }
            std::cout << "- Зелье: средняя длительность = " << sum_dur / potions.size() << std::endl;
        }
        else {
            std::cout << "- Зелье: нет в наличии" << std::endl;
        }

        if (!scrolls.empty()) {
            for (scroll item : scrolls) {
                sum_p += item.getPrice();
                sum_w += item.getWeight();
                sum_m += std::get<int>(item.getSpecParam());
            }
            std::cout << "- Свиток: средняя затрата маны = " << sum_m / scrolls.size() << std::endl;
        }
        else {
            std::cout << "- Свиток: нет в наличии" << std::endl;
        }
        std::cout << "Общая статистика:" << std::endl;
        std::cout << "- Средняя цена:" << sum_p / counter << std::endl;
        std::cout << "- Средний вес:" << sum_w / counter << std::endl;


        weapons.clear();
        armors.clear();
        potions.clear();
        scrolls.clear();
    }
}