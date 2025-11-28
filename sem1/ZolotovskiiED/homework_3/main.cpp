#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <variant>

class MagicItem {
protected:
    std::string name;
    int price;
    double weight;

public:
    MagicItem(const std::string& n, int p, double w) : name(n), price(p), weight(w) {}
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
        : MagicItem(n, p, w), damage(d) {
    }

    std::string getTypeName() const override { return "Оружие"; }

    std::variant<int, double, std::string> getSpecParam() const override {
        return damage;
    }
};

class Armor : public MagicItem {
public:
    int defense;

    Armor(const std::string& n, int p, double w, int def)
        : MagicItem(n, p, w), defense(def) {
    }

    std::string getTypeName() const override { return "Броня"; }

    std::variant<int, double, std::string> getSpecParam() const override {
        return defense;
    }
};

class Potion : public MagicItem {
public:
    double duration;

    Potion(const std::string& n, int p, double w, double dur)
        : MagicItem(n, p, w), duration(dur) {
    }

    std::string getTypeName() const override { return "Зелье"; }

    std::variant<int, double, std::string> getSpecParam() const override {
        return duration;
    }
};

class Scroll : public MagicItem {
public:
    std::string effect;

    Scroll(const std::string& n, int p, double w, const std::string& eff)
        : MagicItem(n, p, w), effect(eff) {
    }

    std::string getTypeName() const override { return "Свиток"; }

    std::variant<int, double, std::string> getSpecParam() const override {
        return effect;
    }
};

struct Shop {
    std::string name;
    std::vector<std::unique_ptr<MagicItem>> items;
};

static std::string trim(const std::string& s) {
    size_t l = 0;
    while (l < s.size() && std::isspace(static_cast<unsigned char>(s[l]))) ++l;
    size_t r = s.size();
    while (r > l && std::isspace(static_cast<unsigned char>(s[r - 1]))) --r;
    return s.substr(l, r - l);
}

void readShopsFromFile(const std::string& filename, std::vector<Shop>& shops) {
    std::ifstream in(filename);
    std::string line;

    while (std::getline(in, line)) {
        line = trim(line);
        if (line.rfind("Магазин:", 0) != 0) continue;

        Shop shop;
        shop.name = trim(line.substr(std::string("Магазин:").length()));

        while (std::getline(in, line)) {
            line = trim(line);
            if (line.empty()) continue;
            if (line.rfind("Предметы:", 0) == 0) break;
        }

        int count = std::stoi(trim(line.substr(line.find(':') + 1)));

        for (int i = 0; i < count; ++i) {
            std::getline(in, line);
            line = trim(line);
            if (line.empty()) { --i; continue; }

            std::istringstream iss(line);
            std::string type, itemName;
            int price;
            double weight;
            iss >> type >> itemName >> price >> weight;

            std::string spec;
            std::getline(iss, spec);
            spec = trim(spec);

            if (type == "Оружие") {
                shop.items.push_back(std::make_unique<Weapon>(
                    itemName, price, weight, std::stoi(spec)));
            }
            else if (type == "Броня") {
                shop.items.push_back(std::make_unique<Armor>(
                    itemName, price, weight, std::stoi(spec)));
            }
            else if (type == "Зелье") {
                shop.items.push_back(std::make_unique<Potion>(
                    itemName, price, weight, std::stod(spec)));
            }
            else {
                shop.items.push_back(std::make_unique<Scroll>(
                    itemName, price, weight, spec));
            }
        }

        shops.push_back(std::move(shop));
    }
}

void printShopStats(const Shop& shop) {
    std::cout << "=== Магазин: " << shop.name << " ===\n";
    size_t total = shop.items.size();

    std::cout << "Всего предметов: " << total << "\n\n";

    double sumPrice = 0.0;
    double sumWeight = 0.0;

    for (const auto& it : shop.items) {
        sumPrice += it->getPrice();
        sumWeight += it->getWeight();
    }

    std::cout << std::fixed << std::setprecision(2);

    if (total > 0) {
        std::cout << "Средняя цена: " << (sumPrice / total) << " золота\n";
        std::cout << "Средний вес: " << (sumWeight / total) << " кг\n\n";
    }

    int cntWeapon = 0, cntArmor = 0, cntPotion = 0;
    long long sumWeapon = 0, sumArmor = 0;
    double sumPotion = 0.0;
    std::map<std::string, int> freqScroll;

    for (const auto& it : shop.items) {
        auto param = it->getSpecParam();
        std::string type = it->getTypeName();

        if (type == "Оружие") {
            cntWeapon++;
            sumWeapon += std::get<int>(param);
        }
        else if (type == "Броня") {
            cntArmor++;
            sumArmor += std::get<int>(param);
        }
        else if (type == "Зелье") {
            cntPotion++;
            sumPotion += std::get<double>(param);
        }
        else if (type == "Свиток") {
            freqScroll[std::get<std::string>(param)]++;
        }
    }

    if (cntWeapon == 0) std::cout << "- Оружие: нет в наличии\n";
    else std::cout << "- Оружие: средний урон = " << (double)sumWeapon / cntWeapon << "\n";

    if (cntArmor == 0) std::cout << "- Броня: нет в наличии\n";
    else std::cout << "- Броня: средняя защита = " << (double)sumArmor / cntArmor << "\n";

    if (cntPotion == 0) std::cout << "- Зелья: нет в наличии\n";
    else std::cout << "- Зелья: средняя длительность = " << (double)sumPotion / cntPotion << "\n";

    if (freqScroll.empty()) std::cout << "- Свитки: нет в наличии\n";
    else {
        std::string best; int bestCount = -1;
        for (auto& p : freqScroll)
            if (p.second > bestCount) {
                bestCount = p.second;
                best = p.first;
            }
        std::cout << "- Свитки: самый частый эффект " << best << "\n";
    }

    std::cout << "\n";
}

int main() {
    setlocale(LC_CTYPE, "Russian");

    std::string filename = "shops.txt";

    std::vector<Shop> shops;
    readShopsFromFile(filename, shops);

    for (const auto& s : shops)
        printShopStats(s);

    return 0;
}
