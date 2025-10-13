#include <iostream>
#include <string>
#include <cctype>

bool isint(std::string str) { // Функция проверки строки на возможный перевод в тип int
    try {
        std::stoi(str);
    } catch (...) {
        return false;
    }
    return true;
}

bool isfloat(std::string str){ // Функция проверки строки на возможный перевод в тип float
    try{
        std::stof(str);
    } catch (...) {
        return false;
    }
    return true;
}

bool quit(std::string q){ // Функция, реализующая пользовательский выход из функции программы
    if(q == "y" || q == "Y"){
        return 1;
    }
    else if (q == "n" || q == "N"){
        return 0;
    }
    else{
        std::cout << "_______________________" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Неизвестная команда, выход в меню..." << std::endl;
        std::cout << "_______________________" << std::endl;
        return 1;
    }
}


int trapS() // Функция, считающая площадь трапеции
{
    bool quit_flag = false; // Флаг для обработки пользовательского выхода из функции

    while(true){        
        if(quit_flag == true){ // Проверка флага, определяет надо ли выходить из функции
            return 0;
        }
        else{
            std::string a, b, h, q; // Инициализация переменных, для точного нахождения площади трапеции необходим тип float
            float c; 
            
            std::cout << "_______________________" << std::endl; // Ввод данных
            std::cout << " " << std::endl;
            std::cout << "Введите основание A:"; 
            std::cin >> a;
            if(isfloat(a)){
                std::cout << "Введите основание B:"; 
                std::cin >> b;
                if (isfloat(b)){
                    std::cout << "Введите высоту H:"; 
                    std::cin >> h;
                    if (isfloat(h)){
                        float fa = std::stof(a);
                        float fb = std::stof(b);
                        float fh = std::stof(h);
                        c = ((fa+fb)/2)*fh;  // Нахождение площади трапеции

                        std::cout << " " << std::endl;
                        std::cout << "Площадь трапеции: "; // Вывод
                        std::cout << c << std::endl;

                        std::cout << "_______________________" << std::endl;
                        std::cout << " " << std::endl;
                        std::cout << "Вернуться в меню(Y/N): ";
                        std::cin >> q; // Ввод в переменную q

                        quit_flag = quit(q); // Изменения флага пользовательского выхода из функции
                    }
                    else{
                        std::cout << "Некорректный ввод. Переход в меню...";
                        quit_flag = true;
                    }   
                }
                else{
                    std::cout << "Некорректный ввод. Переход в меню...";
                    quit_flag = true;
                }
            }
            else{
                std::cout << "Некорректный ввод. Переход в меню...";
                quit_flag = true;
            }
        }
        
    }
}

int squarectS()  // Функция, считающая площадь прямоугольника или квадрата
{
    bool quit_flag = false; // Флаг для обработки пользовательского выхода из функции
    while (true){ 
        if (quit_flag == true){ // Проверка флага, определяет надо ли выходить из функции
            return 0;
        }
        else{
            std::string a, b, q; // Инициализация переменных

            std::cout << "_______________________" << std::endl; // Ввод данных
            std::cout << " " << std::endl;
            std::cout << "Введите сторону A:";
            std::cin >> a;
            if(isint(a)){
                std::cout << "Введите сторону B:";
                std::cin >> b;
                if(isint(b)){
                    std::cout << " " << std::endl;
                    std::cout << "Площадь квадрата:";
                    int int_a = std::stoi(a); 
                    int int_b = std::stoi(b);
                    std::cout << int_a*int_b << std::endl; // Нахождение площади прямоугольника
                              
                    std::cout << "_______________________" << std::endl;
                    std::cout << " " << std::endl;
                    std::cout << "Вернуться в меню(Y/N): ";
                    std::cin >> q; // Ввод в переменную q
            
                    quit_flag = quit(q); // Изменения флага пользовательского выхода из функции

                }else{
                    std::cout << "Некорректный ввод. Переход в меню..." << std::endl;
                    quit_flag = true;
                }
            }
            else{
                std::cout << "Некорректный ввод. Переход в меню..." << std::endl;
                quit_flag = true;
            }
        }
           
    }
        
}


int main()
{
    while (true)
    {
        std::string i; // Инициализация переменной
        std::cout << " " << std::endl; // Вывод доступных функций
        std::cout << "1. Подсчет площади прямоугольника" << std::endl;
        std::cout << "2. Подсчет площади трапеции" << std::endl;
        std::cout << "3. Выход из программы" << std::endl;
        std::cout << "Введите номер функции: ";
        
        std::cin >> i; // Ввод в переменную
        if(isint(i)){ // Проверка переменной на число типа Int
            if(stoi(i) == 1){ // Переключение на функции
                squarectS();
            }
            else if (stoi(i) == 2){
                trapS();
            }
            else if (stoi(i) == 3){
                return 0;
            }
            else { // Если неизвестный номер функции
                std::cout << " " << std::endl; 
                std::cout << "Такой функции не предусмотрено" << std::endl; 
                std::cout << " " << std::endl;                
                std::cin.clear();
            }
        }
        else{ // Если неизвестный символ
            std::cout << " " << std::endl;
            std::cout << "Такой функции не предусмотрено" << std::endl; 
            std::cout << " " << std::endl;        
            std::cin.clear();
        }
    }
    }