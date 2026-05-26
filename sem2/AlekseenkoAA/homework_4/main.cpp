// minihomework4.cpp : Этот файл содержит функцию "main". Здесь начинается и
// заканчивается выполнение программы.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

int main() {
  std::fstream fs_out;
  fs_out.open("output.txt", std::ios::out);

  std::vector<int> numbers(20);
  std::vector<int> unique_numbers;

  if (fs_out.is_open()) {
    auto printVector = [&fs_out](const std::vector<int>& vec) {
      std::for_each(vec.begin(), vec.end(), [&fs_out](const int& value) {
        std::cout << value << " ";
        fs_out << value << " ";
      });
      std::cout << "\n";
      fs_out << "\n";
    };

    auto printLine = [&fs_out](const std::string& line) {
      std::cout << line << "\n";
      fs_out << line << "\n";
    };

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(-50, 100);

    std::generate(
        numbers.begin(), numbers.end(),
        [&distribution, &generator]() { return distribution(generator); });

    std::cout << "Сгенерированный вектор: \n";  // толкко показ
    std::for_each(numbers.begin(), numbers.end(),
                  [&fs_out](const int& value) { std::cout << value << " "; });

    auto minmax_result = std::minmax_element(numbers.begin(), numbers.end());

    printLine("\nМинимальный элемент: ");
    printLine(std::to_string(*minmax_result.first));

    printLine("\nМаксимальный элемент: ");
    printLine(std::to_string(*minmax_result.second));

    std::sort(numbers.begin(), numbers.end());

    printLine("\nОтсортированный вектор: ");
    printVector(numbers);

    int positive_count = std::count_if(numbers.begin(), numbers.end(),
                                       [](int value) { return value > 0; });

    int negative_count = std::count_if(numbers.begin(), numbers.end(),
                                       [](int value) { return value < 0; });

    int zero_count = std::count_if(numbers.begin(), numbers.end(),
                                   [](int value) { return value == 0; });

    printLine("\nКоличество положительных элементов: ");
    printLine(std::to_string(positive_count));

    printLine("\nКоличество отрицательных элементов: ");
    printLine(std::to_string(negative_count));

    printLine("\nКоличество нулевых элементов: ");
    printLine(std::to_string(zero_count));

    double average = std::accumulate(numbers.begin(), numbers.end(), 0.0) /
                     static_cast<double>(numbers.size());

    printLine("\nСреднее арифметическое: ");
    printLine(std::to_string(average));

    numbers.erase(
        std::remove_if(numbers.begin(), numbers.end(),
                       [average](int value) { return value < average; }),
        numbers.end());

    printLine("\nПосле удаления чисел меньше среднего арифметического: ");
    printVector(numbers);

    std::sort(numbers.begin(), numbers.end());
    std::unique_copy(numbers.begin(), numbers.end(),
                     std::back_inserter(unique_numbers));

    printLine("\nВектор уникальных значений: ");
    printVector(unique_numbers);
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