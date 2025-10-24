#include <iostream>
#include <string>
#include <cctype>

// Функция проверки строки на возможный перевод в тип int
bool IsInt(const std::string& str) {
    try {
        std::stoi(str);
    } catch (...) {
        return false;
    }
    return true;
}

// Функция проверки строки на возможный перевод в тип float
bool IsFloat(const std::string& str) {
    try {
        std::stof(str);
    } catch (...) {
        return false;
    }
    return true;
}

// Функция, реализующая пользовательский выход из функции программы
bool Quit(const std::string& q) {
    if (q == "y" || q == "Y") {
        return true;
    } else if (q == "n" || q == "N") {
        return false;
    } else {
        std::cout << "_______________________" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Неизвестная команда, выход в меню..." << std::endl;
        std::cout << "_______________________" << std::endl;
        return true;
    }
}

// Функция, считающая площадь трапеции
int CalculateTrapezoidArea() {
    bool quit_flag = false;  // Флаг для обработки пользовательского выхода из функции

    while (true) {        
        if (quit_flag) {  // Проверка флага, определяет надо ли выходить из функции
            return 0;
        }
        
        std::string a, b, h, q;
        float c; 
        
        std::cout << "_______________________" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Введите основание A:"; 
        std::cin >> a;
        
        if (!IsFloat(a)) {
            std::cout << "Некорректный ввод. Переход в меню...";
            quit_flag = true;
            continue;
        }
        
        std::cout << "Введите основание B:"; 
        std::cin >> b;
        
        if (!IsFloat(b)) {
            std::cout << "Некорректный ввод. Переход в меню...";
            quit_flag = true;
            continue;
        }
        
        std::cout << "Введите высоту H:"; 
        std::cin >> h;
        
        if (!IsFloat(h)) {
            std::cout << "Некорректный ввод. Переход в меню...";
            quit_flag = true;
            continue;
        }
        
        float fa = std::stof(a);
        float fb = std::stof(b);
        float fh = std::stof(h);
        c = ((fa + fb) / 2) * fh;  // Нахождение площади трапеции

        std::cout << " " << std::endl;
        std::cout << "Площадь трапеции: ";
        std::cout << c << std::endl;

        std::cout << "_______________________" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Вернуться в меню(Y/N): ";
        std::cin >> q;

        quit_flag = Quit(q);
    }
}

// Функция, считающая площадь прямоугольника или квадрата
int CalculateRectangleArea() {
    bool quit_flag = false;  // Флаг для обработки пользовательского выхода из функции
    
    while (true) { 
        if (quit_flag) {  // Проверка флага, определяет надо ли выходить из функции
            return 0;
        }
        
        std::string a, b, q;

        std::cout << "_______________________" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Введите сторону A:";
        std::cin >> a;
        
        if (!IsInt(a)) {
            std::cout << "Некорректный ввод. Переход в меню..." << std::endl;
            quit_flag = true;
            continue;
        }
        
        std::cout << "Введите сторону B:";
        std::cin >> b;
        
        if (!IsInt(b)) {
            std::cout << "Некорректный ввод. Переход в меню..." << std::endl;
            quit_flag = true;
            continue;
        }
        
        std::cout << " " << std::endl;
        std::cout << "Площадь прямоугольника:";
        int int_a = std::stoi(a); 
        int int_b = std::stoi(b);
        std::cout << int_a * int_b << std::endl;
                  
        std::cout << "_______________________" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Вернуться в меню(Y/N): ";
        std::cin >> q;
        
        quit_flag = Quit(q);
    }
}

int main() {
    while (true) {
        std::string i;
        std::cout << " " << std::endl;
        std::cout << "1. Подсчет площади прямоугольника" << std::endl;
        std::cout << "2. Подсчет площади трапеции" << std::endl;
        std::cout << "3. Выход из программы" << std::endl;
        std::cout << "Введите номер функции: ";
        
        std::cin >> i;
        
        if (!IsInt(i)) {
            std::cout << " " << std::endl;
            std::cout << "Такой функции не предусмотрено" << std::endl; 
            std::cout << " " << std::endl;
            std::cin.clear();
            continue;
        }
        
        int choice = std::stoi(i);
        if (choice == 1) {
            CalculateRectangleArea();
        } else if (choice == 2) {
            CalculateTrapezoidArea();
        } else if (choice == 3) {
            return 0;
        } else {
            std::cout << " " << std::endl;
            std::cout << "Такой функции не предусмотрено" << std::endl; 
            std::cout << " " << std::endl;
            std::cin.clear();
        }
    }
}