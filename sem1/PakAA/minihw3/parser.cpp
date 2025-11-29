#include "parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "items.h"

std::vector<Shop> Parser::parseFile(const std::string& filename) {
    std::vector<Shop> shops;

    // Открываем файл в бинарном режиме и преобразуем в UTF-8
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return shops;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Удаляем BOM если присутствует
        if (line.size() >= 3 &&
            static_cast<unsigned char>(line[0]) == 0xEF &&
            static_cast<unsigned char>(line[1]) == 0xBB &&
            static_cast<unsigned char>(line[2]) == 0xBF) {
            line.erase(0, 3);
        }

        if (line.find("Магазин:") == 0) {
            std::string shop_name = line.substr(9);
            Shop shop(shop_name);

            std::getline(file, line);
            if (line.find("Предметы:") != 0) {
                std::cerr << "Ошибка формата файла: ожидалось 'Предметы:'\n";
                continue;
            }

            size_t colon_pos = line.find(':');
            int item_count = std::stoi(line.substr(colon_pos + 1));

            for (int i = 0; i < item_count && std::getline(file, line); ++i) {
                std::stringstream stream(line);
                std::string item_type, item_name;
                int item_price;
                double item_weight;

                stream >> item_type >> item_name >> item_price >> item_weight;
                std::replace(item_name.begin(), item_name.end(), '_', ' ');

                if (item_type == "Оружие") {
                    int item_damage;
                    stream >> item_damage;
                    shop.addItem(std::make_unique<Weapon>(
                        item_name, item_price, item_weight, item_damage));
                }
                else if (item_type == "Броня") {
                    int item_defense;
                    stream >> item_defense;
                    shop.addItem(std::make_unique<Armor>(
                        item_name, item_price, item_weight, item_defense));
                }
                else if (item_type == "Зелье") {
                    double item_duration;
                    stream >> item_duration;
                    shop.addItem(std::make_unique<Potion>(
                        item_name, item_price, item_weight, item_duration));
                }
                else if (item_type == "Свиток") {
                    std::string item_effect;
                    stream >> item_effect;
                    std::replace(item_effect.begin(), item_effect.end(), '_', ' ');
                    shop.addItem(std::make_unique<Scroll>(
                        item_name, item_price, item_weight, item_effect));
                }
            }

            shops.push_back(std::move(shop));
        }
    }

    file.close();
    return shops;
}