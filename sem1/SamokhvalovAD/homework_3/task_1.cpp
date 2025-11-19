#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <variant>
#include <fstream>


class MagicItem {
    public:
        MagicItem(std::string name, int price, double weight) : name(name), price(price), weight(weight) {}
        virtual std::variant<int, double, std::string> getSpecialParam() const = 0;
        virtual std::string getName() const = 0;
        virtual int getPrice() const = 0;
        virtual double getWeight() const = 0;
    private:
        std::string name;
        int price;
        double weight;
};


class Weapon : public MagicItem {
    public:
        Weapon(std::string name, int price, double weight, int damage)
            : MagicItem{name, price, weight}, damage(damage) {}
            
        std::variant<int, double, std::string> getSpecialParam() const override {
            return damage;
        }
            
        std::string getName() const override {
            return name;
        }

        int getPrice() const override {
            return price;
        }

        double getWeight() const override {
            return weight;
        }
    private:
        std::string name;
        int price;
        double weight;
        int damage;
};


// class Shop {
//     public:
//         Shop(std::string name) : name(name) {}
        
//         void addItem(const MagicItem& item) {
//             items.push_back(item);
//         }
        
//     private:
//         std::string name;
//         std::vector<MagicItem> items;
// };

void analyzeItem(std::string line) {
    std::istringstream iss(line);
    std::string type, name, price, weight, specialParam;
    iss >> type >> name >> price >> weight >> specialParam;
    std::cout << "Item Type: " << type << std::endl;
}


void analyzeShop(std::ifstream& file) {
    std::string line;
    std::string type, count;

    getline(file, line);
    std::cout << line << std::endl;
    std::istringstream iss(line);
    iss >> type >> count;

    for (int i = 0; i < std::stoi(count); i++) {
        getline(file, line);
        analyzeItem(line);
    }
    getline(file, line);
}


void readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }
    while (!file.eof()) {
        std::string line;
        getline(file, line);
        if (line.find("Shop") == 0) {
            analyzeShop(file);
            getline(file, line);
        }
    }
    file.close();
}


int main() {
    std::cout << "\t--Shop Analytics--" << std::endl;
    readFile("sem1/SamokhvalovAD/homework_3/data.txt");
    return 0;
}