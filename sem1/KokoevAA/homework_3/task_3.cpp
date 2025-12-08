#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

class magic_item {
public:
    std::string name;
    double price;
    double weight;

    magic_item(const std::string& n, int p, double w) : name(n), price(p), weight(w) {}

    virtual ~magic_item() {}

    virtual std::string get_type() const = 0;

    virtual std::variant<int, double, std::string> get_spec_param() const = 0;
};

class weapon : public magic_item {
public:
    int damage;

    weapon(const std::string& n, int p, double w, int d)
        : magic_item(n, p, w), damage(d) {
    }

    std::string get_type() const override { return "Weapon"; }

    std::variant<int, double, std::string> get_spec_param() const override { return damage; }
};

class armor : public magic_item {
public:
    int defense;

    armor(const std::string& n, int p, double w, int def)
        : magic_item(n, p, w), defense(def) {
    }

    std::string get_type() const override { return "Armor"; }

    std::variant<int, double, std::string> get_spec_param() const override { return defense; }
};

class potion : public magic_item {
public:
    double duration;

    potion(const std::string& n, int p, double w, double dur)
        : magic_item(n, p, w), duration(dur) {
    }

    std::string get_type() const override { return "Potion"; }

    std::variant<int, double, std::string> get_spec_param() const override {
        return duration;
    }
};

class scroll : public magic_item {
public:
    std::string effect;

    scroll(const std::string& n, int p, double w, const std::string& eff)
        : magic_item(n, p, w), effect(eff) {
    }

    std::string get_type() const override { return "Scroll"; }

    std::variant<int, double, std::string> get_spec_param() const override { return effect; }
};

struct shop_t {
    std::string name;
    std::vector<magic_item*> items;
};

void print_shop_stats(const shop_t& shop) {
    std::cout << "=== Магазин: " << shop.name << " ===" << std::endl;

    int total_items = (int)shop.items.size();
    std::cout << "Всего предметов: " << total_items << std::endl;

    double sum_price = 0;
    double sum_weight = 0;

    long long sum_weapon_damage = 0;
    int count_weapon = 0;

    long long sum_armor_defense = 0;
    int count_armor = 0;

    double sum_potion_duration = 0;
    int count_potion = 0;

    std::map<std::string, int> scroll_effects;
    int count_scroll = 0;

    for (int i = 0; i < (int)shop.items.size(); i++) {
        magic_item* item = shop.items[i];

        sum_price += item->price;
        sum_weight += item->weight;

        std::string type = item->get_type();
        std::variant<int, double, std::string> param = item->get_spec_param();

        if (type == "Weapon") {
            int dmg = std::get<int>(param);
            sum_weapon_damage += dmg;
            count_weapon++;
        }
        else if (type == "Armor") {
            int def = std::get<int>(param);
            sum_armor_defense += def;
            count_armor++;
        }
        else if (type == "Potion") {
            double dur = std::get<double>(param);
            sum_potion_duration += dur;
            count_potion++;
        }
        else if (type == "Scroll") {
            std::string eff = std::get<std::string>(param);
            scroll_effects[eff]++;
            count_scroll++;
        }
    }

    std::cout << std::fixed << std::setprecision(2);

    if (total_items > 0) {
        std::cout << "Средняя цена: " << sum_price / total_items << " золота" << std::endl;
        std::cout << "Средний вес: " << sum_weight / total_items << " кг" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Статистика по типам:" << std::endl;

    if (count_weapon > 0) {
        double avg_damage = (double)sum_weapon_damage / count_weapon;
        std::cout << "- Оружие: средний урон = " << avg_damage << std::endl;
    }
    else {
        std::cout << "- Оружие: нет в наличии" << std::endl;
    }

    if (count_armor > 0) {
        double avg_defense = (double)sum_armor_defense / count_armor;
        std::cout << "- Броня: средняя защита = " << avg_defense << std::endl;
    }
    else {
        std::cout << "- Броня: нет в наличии" << std::endl;
    }

    if (count_potion > 0) {
        double avg_duration = sum_potion_duration / count_potion;
        std::cout << "- Зелья: средняя длительность = " << avg_duration << std::endl;
    }
    else {
        std::cout << "- Зелья: нет в наличии" << std::endl;
    }

    if (count_scroll > 0) {
        std::string best_effect = "";
        int best_count = 0;

        for (auto it = scroll_effects.begin(); it != scroll_effects.end(); ++it) {
            if (it->second > best_count) {
                best_count = it->second;
                best_effect = it->first;
            }
        }

        std::cout << "- Свитки: самый частый эффект = " << best_effect << std::endl;
    }
    else {
        std::cout << "- Свитки: нет в наличии" << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::ifstream fin("shops.txt");
    if (!fin.is_open()) {
        std::cout << "Не удалось открыть файл shops.txt" << std::endl;
        return 1;
    }

    std::vector<shop_t> shops;

    while (true) {
        std::string word;
        if (!(fin >> word)) {
            break;
        }

        if (word != "Shop:") {
            break;
        }

        std::string shop_name;
        std::getline(fin, shop_name);
        if (!shop_name.empty() && shop_name[0] == ' ') shop_name.erase(0, 1);

        shop_t shop;
        shop.name = shop_name;

        std::string items_word;
        int items_count;
        fin >> items_word >> items_count;

        for (int i = 0; i < items_count; i++) {
            std::string type;
            std::string item_name;
            double price;
            double weight;

            fin >> type >> item_name >> price >> weight;

            if (type == "Weapon") {
                int damage;
                fin >> damage;
                shop.items.push_back(new weapon(item_name, price, weight, damage));
            }
            else if (type == "Armor") {
                int defense;
                fin >> defense;
                shop.items.push_back(new armor(item_name, price, weight, defense));
            }
            else if (type == "Potion") {
                double duration;
                fin >> duration;
                shop.items.push_back(new potion(item_name, price, weight, duration));
            }
            else if (type == "Scroll") {
                std::string effect;
                fin >> effect;
                shop.items.push_back(new scroll(item_name, price, weight, effect));
            }
            else {
                std::cout << "Неизвестный тип предмета: " << type << std::endl;
            }
        }

        shops.push_back(shop);
    }

    for (int i = 0; i < (int)shops.size(); i++) {
        print_shop_stats(shops[i]);
    }

    for (int i = 0; i < (int)shops.size(); i++) {
        for (int j = 0; j < (int)shops[i].items.size(); j++) {
            delete shops[i].items[j];
        }
    }

    return 0;
}
