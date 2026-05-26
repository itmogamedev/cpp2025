// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается
// и заканчивается выполнение программы.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::fstream fs;
  std::fstream fs_out;
  fs.open("input.txt", std::ios::in);
  fs_out.open("output.txt", std::ios::out);

  std::vector<std::string> text;

  std::vector<int> line_lenght;

  const std::string dictarory("aeiouyAEIOUY");

  if (fs.is_open() && fs_out.is_open()) {
    std::string line;
    while (std::getline(fs, line)) {
      text.push_back(line);
    }

    auto printVector = [&fs_out]<typename T>(const std::vector<T>& vec) {
      std::for_each(vec.begin(), vec.end(), [&fs_out](const T& value) {
        std::cout << value << "\n";
        fs_out << value << "\n";
      });
    };
    auto printLine = [&fs_out](const std::string& line) {
      std::cout << line << "\n";
      fs_out << line << "\n";
    };

    printLine("Исходный прочитанный вектор: \n");
    printVector(text);
    unsigned int lenght_goal = 0;

    std::cout << "\nВведите целевую длину строки: \n";
  retype_lenght:  // start retype
    if (!(std::cin >> lenght_goal)) {
      std::cout << "Попробуй ввести правильную целевую длину ещё раз!\n";
      lenght_goal = 0;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      goto retype_lenght;
    }
    // end of retype
    text.erase(std::remove_if(text.begin(), text.end(),
                              [lenght_goal](const std::string& line) {
                                return line.length() < lenght_goal;
                              }),
               text.end());

    printLine("\nПосле целевой длины: \n");
    printVector(text);

    std::for_each(text.begin(), text.end(), [&dictarory](std::string& s) {
      s.erase(std::remove_if(s.begin(), s.end(),
                             [&dictarory](char c) {
                               return dictarory.find(c) != std::string::npos;
                             }),
              s.end());
    });

    printLine("\nПосле удаления гласных по словарю: \n");
    printVector(text);

    std::cout << "\nВведите слово для поиска: ";

    std::string find_word("");
    std::cin >> find_word;

    auto result = std::find_if(text.begin(), text.end(),
                               [&find_word](const std::string& s) {
                                 return s.find(find_word) != std::string::npos;
                               });
    printLine("\nРезультат поиска заданного слова:\n");
    if (result != text.end()) {
      printLine(*result);
    } else {
      printLine("NULL (not found 404)");
    }

    int total = std::accumulate(
        text.begin(), text.end(), 0, [](int sum, const std::string& s) {
          return sum + std::count_if(s.begin(), s.end(),
                                     [](char c) { return c != '_'; });
        });

    printLine("\nОбщее количество символов без “_”: \n");
    printLine(std::to_string(total));

    std::for_each(text.begin(), text.end(),
                  [&line_lenght](const std::string& line) {
                    line_lenght.push_back(line.length());
                  });

    printLine("\nВектор длин строк: \n");
    printVector(line_lenght);
  }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и
//   другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый
//   элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий
//   элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" >
//   "Открыть" > "Проект" и выберите SLN-файл.
