#include "shop_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

std::vector<Shop> readShopsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return {};
    }

    std::vector<Shop> shops;
    std::string line;
    Shop currentShop;

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        if (line.find("Магазин:") == 0) {
            if (!currentShop.name.empty() && !currentShop.items.empty()) {
                shops.push_back(std::move(currentShop));
                currentShop = Shop();
            }
            currentShop.name = trim(line.substr(8));
        }
        else if (line.find("Предметы:") == 0) {
            try {
                int count = std::stoi(trim(line.substr(9)));
                currentShop.items.reserve(count);

                for (int i = 0; i < count; ++i) {
                    if (!std::getline(file, line)) break;
                    line = trim(line);
                    if (line.empty()) {
                        --i;
                        continue;
                    }

                    std::istringstream iss(line);
                    std::vector<std::string> tokens;
                    std::string token;
                    while (iss >> token) {
                        tokens.push_back(token);
                    }

                    if (tokens.size() < 5) {
                        std::cerr << "Ошибка: некорректная строка предмета - " << line << std::endl;
                        continue;
                    }

                    std::string type = tokens[0];
                    std::string name = tokens[1];
                    int price = std::stoi(tokens[2]);
                    double weight = std::stod(tokens[3]);
                    std::string paramStr = tokens[4];

                    try {
                        if (type == "Оружие") {
                            int damage = std::stoi(paramStr);
                            currentShop.items.push_back(
                                std::make_unique<Weapon>(name, price, weight, damage)
                            );
                        }
                        else if (type == "Броня") {
                            int defense = std::stoi(paramStr);
                            currentShop.items.push_back(
                                std::make_unique<Armor>(name, price, weight, defense)
                            );
                        }
                        else if (type == "Зелье") {
                            double duration = std::stod(paramStr);
                            currentShop.items.push_back(
                                std::make_unique<Potion>(name, price, weight, duration)
                            );
                        }
                        else if (type == "Свиток") {
                            currentShop.items.push_back(
                                std::make_unique<Scroll>(name, price, weight, paramStr)
                            );
                        }
                        else {
                            std::cerr << "Ошибка: неизвестный тип предмета - " << type << std::endl;
                        }
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Ошибка при создании предмета: " << e.what() << std::endl;
                    }
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка при чтении количества предметов: " << e.what() << std::endl;
            }
        }
    }

    if (!currentShop.name.empty()) {
        shops.push_back(std::move(currentShop));
    }

    return shops;
}