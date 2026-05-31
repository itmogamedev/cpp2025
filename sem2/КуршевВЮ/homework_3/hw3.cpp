#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <numeric> // для std::accumulate
#include <vector>

int main() {
  setlocale(0, "rus");

  std::ifstream input("input.txt");

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input, line)) {
    lines.push_back(line);
  }
  input.close();

  // Исходный вектор
  std::vector<std::string> original = lines;

  std::cout << "Введите порог длины строк, которые удалятся: ";
  int threshold;
  std::cin >> threshold;

  std::cout << "Введите слово, строку с которым хотите найти: ";
  std::string search_word;
  std::cin >> search_word;

  // 1. Удаление строк, длина которых меньше порога (захват по значению)
  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [threshold](const std::string& s) {
                               return s.length() < threshold;
                             }),
              lines.end());
  std::vector<std::string> after_remove = lines;

  // 2. Замена пробелов на "_"
  auto replaceSpaces = [](std::string& s) {
    std::replace(s.begin(), s.end(), ' ', '_');
  };

  for (std::string& s : lines) {
    replaceSpaces(s);
  }
  std::vector<std::string> after_replace = lines;

  // 3. Поиск строки, содержащей заданное слово
  auto it = std::find_if(lines.begin(), lines.end(),
                         [&search_word](const std::string& s) {
                           return s.find(search_word) != std::string::npos; //s.find() возвращает npos, если не находит подстроку
                         });
  std::string search_result = (it == lines.end()) ? "Не найдено" : *it;

  // 4. Подсчёт общего количества символов без "_"
  int total_chars = std::accumulate(  // accumulate "накапливает"
      lines.begin(), lines.end(), 0, [](int sum, const std::string& s) {
        return sum + std::count_if(s.begin(), s.end(),
                                   [](char c) { return c != '_'; });
      });

  // 5. Вектор длин строк
  std::vector<int> lengths;
  lengths.reserve(lines.size());
  std::transform(lines.begin(), lines.end(), std::back_inserter(lengths), // transform делает что то с lines, записывает результаты в lengths
                 [](const std::string& s) { return s.length(); });

  std::ofstream output("output.txt");

  auto printVector = [&output](const std::string& title, const auto& vec) {
    output << title << '\n';
    for (const auto& elem : vec) {
      output << elem << '\n';
    }
    output << '\n';
  };

  printVector("Исходный вектор строк:", original);
  printVector("Вектор строк после удаления коротких строк:", after_remove);
  printVector("Вектор строк после замены пробелов на \"_\":", after_replace);

  output << "Результат поиска заданного слова:\n" << search_result << "\n\n";
  output << "Общее количество символов без \"_\":\n" << total_chars << "\n\n";

  output << "Вектор длин строк:\n";
  for (int len : lengths) {
    output << len << '\n';
  }

  output.close();
  std::cout << "Вывод в output.txt" << std::endl;
}