#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

int main() {
  // 1. Считывание всех строк из файла input.txt
  std::ifstream infile("input.txt");
  if (!infile.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл input.txt!" << std::endl;
    return 1;
  }

  std::vector<std::string> original_lines;
  std::string line;
  while (std::getline(infile, line)) {
    original_lines.push_back(line);
  }
  infile.close();

  // Ввод параметров пользователя
  size_t threshold;
  std::cout << "Введите порог длины строк: ";
  if (!(std::cin >> threshold)) {
    std::cerr << "Ошибка ввода порога!" << std::endl;
    return 1;
  }

  std::string search_word;
  std::cout << "Введите слово для поиска: ";
  std::cin >> search_word;

  // 2. Удаление коротких строк (Лямбда с захватом по значению)
  std::vector<std::string> filtered_lines = original_lines;
  filtered_lines.erase(
    std::remove_if(filtered_lines.begin(), filtered_lines.end(),
      [threshold](const std::string& s) {
        return s.length() < threshold;
      }),
    filtered_lines.end()
  );

  // 3. ВАРИАНТ 1: Замена пробелов на '_'
  std::vector<std::string> replaced_lines = filtered_lines;
  std::for_each(replaced_lines.begin(), replaced_lines.end(), [](std::string& s) {
    std::replace(s.begin(), s.end(), ' ', '_');
  });

  // 4. Поиск строки с заданным словом (Лямбда с захватом по ссылке)
  auto it = std::find_if(replaced_lines.begin(), replaced_lines.end(),
    [&search_word](const std::string& s) {
      return s.find(search_word) != std::string::npos;
    });
  std::string search_result = (it != replaced_lines.end()) ? *it : "Слово не найдено";

  // 5. Подсчёт общего количества символов без учета '_'
  size_t total_chars = std::accumulate(replaced_lines.begin(), replaced_lines.end(), size_t(0),
    [](size_t sum, const std::string& s) {
      size_t valid_chars = std::count_if(s.begin(), s.end(), [](char c) { return c != '_'; });
      return sum + valid_chars;
    });

  // 6. Создание нового вектора целых чисел с длинами строк
  std::vector<int> lengths;
  lengths.reserve(replaced_lines.size());
  std::transform(replaced_lines.begin(), replaced_lines.end(), std::back_inserter(lengths),
    [](const std::string& s) {
      return static_cast<int>(s.length());
    });

  // Запись результатов в файл output.txt
  std::ofstream outfile("output.txt");
  if (!outfile.is_open()) {
    std::cerr << "Ошибка: не удалось создать файл output.txt!" << std::endl;
    return 1;
  }

  outfile << "Исходный вектор строк:\n";
  for (const auto& s : original_lines) outfile << s << "\n";

  outfile << "\nВектор строк после удаления коротких строк:\n";
  for (const auto& s : filtered_lines) outfile << s << "\n";

  outfile << "\nВектор строк после замены пробелов на \"_\":\n";
  for (const auto& s : replaced_lines) outfile << s << "\n";

  outfile << "\nРезультат поиска заданного слова:\n";
  outfile << search_result << "\n";

  outfile << "\nОбщее количество символов без \"_\":\n";
  outfile << total_chars << "\n";

  outfile << "\nВектор длин строк:\n";
  for (int len : lengths) outfile << len << " ";
  outfile << "\n";

  outfile.close();
  std::cout << "Готово! Результаты успешно записаны в файл output.txt" << std::endl;

  return 0;
}