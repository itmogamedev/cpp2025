#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <numeric>
#include <cmath>

using namespace std;

// Вывод вектора в файл
void print_vector(const string& title, const vector<int>& vec, ofstream& output_file) {
    output_file << "\n--- " << title << " ---\n";
    if (vec.empty()) {
        output_file << "(Вектор пуст)\n";
        return;
    }
    // Используем std::copy и ostream_iterator, чтобы избежать циклов for/while
    ostream_iterator<int> out(output_file, " ");
    cout << "Элементы: "; // Для консольного вывода
    std::copy(vec.begin(), vec.end(), out);
    output_file << "\n";
}

// Вывод значения в файл
template <typename T>
void write_result(ofstream& output_file, const string& label, T value) {
    output_file << "Результат " << label << ": " << value << endl;
}

int main() {
    const string OUTPUT_FILE = "output.txt";
    ofstream output_file(OUTPUT_FILE);

    if (!output_file.is_open()) {
        cerr << "Ошибка: Не удалось создать файл " << OUTPUT_FILE << "." << endl;
        return 1;
    }

    // Генерация случайного вектора
    const int VECTOR_SIZE = 20;
    vector<int> data(VECTOR_SIZE);
    
    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 generator(rd());
    // Диапазон: [-50, 100]
    std::uniform_int_distribution<> distribution(-50, 100);

    // Заполнение вектора (без циклов)
    std::generate(data.begin(), data.end(), [&]() {
        return distribution(generator);
    });

    int min_val, max_val;

    // Итератор на минимальный элемент
    auto min_it = std::min_element(data.begin(), data.end());
    min_val = *min_it;
    write_result(output_file, "Минимальный элемент", min_val);

    // Итератор на максимальный элемент
    auto max_it = std::max_element(data.begin(), data.end());
    max_val = *max_it;
    write_result(output_file, "Максимальный элемент", max_val);

    std::sort(data.begin(), data.end());
    print_vector("Вектор после сортировки", data, output_file);
    
    // Подсчет по условию (без циклов)

    long long positive_count = std::count_if(data.begin(), data.end(), 
        [](int x){ return x > 0; }); // Захват по значению [=]

    long long negative_count = std::count_if(data.begin(), data.end(), 
        [](int x){ return x < 0; });

    long long zero_count = std::count_if(data.begin(), data.end(), 
        [](int x){ return x == 0; });
    
    write_result(output_file, "Количество положительных элементов", positive_count);
    write_result(output_file, "Количество отрицательных элементов", negative_count);
    write_result(output_file, "Количество нулевых элементов", zero_count);

    // Сумма (long long для избежания переполнения)
    long long sum = std::accumulate(data.begin(), data.end(), 0LL, [](long long acc, int x) {
        return acc + x;
    });

    double average = static_cast<double>(sum) / VECTOR_SIZE;
    write_result(output_file, "Среднее арифметическое", round(average * 100.0) / 100.0); // Округление

    vector<int> odd_numbers;

    // Фильтрация в новый вектор (проверка на нечетность)
    std::copy_if(data.begin(), data.end(), std::back_inserter(odd_numbers), 
        [](int x) { return x % 2 != 0; });

    // Результат (только нечетные)
    vector<int>& result_v1 = odd_numbers;

    // Копия нечетных чисел
    vector<int> unique_odd_numbers = result_v1;

    // Сортировка для уникальности
    std::sort(unique_odd_numbers.begin(), unique_odd_numbers.end());

    // Удаление дубликатов
    auto last = std::unique(unique_odd_numbers.begin(), unique_odd_numbers.end());
    unique_odd_numbers.erase(last, unique_odd_numbers.end());

    print_vector("Уникальные значения после фильтрации и сортировки", unique_odd_numbers, output_file);

    output_file.close();
    cout << "Обработка завершена успешно!\n";
    cout << "Все результаты записаны в файл: " << OUTPUT_FILE << endl;

    return 0;
}
