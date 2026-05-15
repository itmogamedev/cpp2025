#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  ///////////////////////////////////////////////////////////////////
  // 1. Считать все строки из файла
  ///////////////////////////////////////////////////////////////////

  std::ifstream input_file("input.txt");
  if (!input_file.is_open()) {
    std::cerr << "Error with opening input.txt\n An' it's not ma' fault..."
              << std::endl;
    return 1;
  }
  // Исходный вектор строк
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }
  input_file.close();

  ///////////////////////////////////////////////////////////////////
  // 2. Реализовать всякое с использованием лямбда-выражений
  ///////////////////////////////////////////////////////////////////

  // Удаление коротких строк
  int inp;
  std::cout << "Input POROG size of string: ";
  std::cin >> inp;

  std::vector<std::string> after_remove = lines;
  after_remove.erase(
      std::remove_if(after_remove.begin(), after_remove.end(),
                     [inp](const std::string& s) { return s.length() < inp; }),
      after_remove.end());

  // Замена пробелов на '_'
  std::vector<std::string> after_replace = after_remove;
  std::for_each(
      after_replace.begin(), after_replace.end(),
      [](std::string& str) { std::replace(str.begin(), str.end(), ' ', '_'); });

  // Поиск строки, содержащей слово
  std::string word;
  std::cout << "Input WORD witch you going to found: ";
  std::cin >> word;

  auto find_word = [&word](const std::vector<std::string>& vec) -> std::string {
    auto it =
        std::find_if(vec.begin(), vec.end(), [&word](const std::string& str) {
          return str.find(word) != std::string::npos;
        });
    if (it != vec.end())
      return *it;
    else
      return "Строка не была найдена";
  };

  std::string line_with_word = find_word(after_remove);

  // Подсчёт общего количества символов без '_'
  auto char_count = [](const std::vector<std::string>& vec) -> int {
    int total = 0;
    for (const auto& str : vec) {
      for (char ch : str) {
        if (ch != '_') {
          ++total;
        }
      }
    }
    return total;
  };

  int totalChars = char_count(after_replace);

  // Создание вектора длин строк
  auto create_vec_of_length =
      [](const std::vector<std::string>& vec) -> std::vector<int> {
    std::vector<int> lengths;
    for (const auto& str : vec) {
      lengths.push_back(str.length());
    }
    return lengths;
  };

  std::vector<int> vec_of_length = create_vec_of_length(after_replace);

  ///////////////////////////////////////////////////////////////////
  // 3. Вывести в файл output.txt
  ///////////////////////////////////////////////////////////////////
  std::ofstream out_file("output.txt");
  if (!out_file.is_open()) {
    std::cerr << "Error with creating output.txt\n And it's can be my "
                 "fault...(but it's not))"
              << std::endl;
    return 1;
  }
  // удобная, *настраиваемая* лямбда для записи векторов строк в файл
  auto print_str_vec = [&out_file](const std::vector<std::string>& vec,
                                   const std::string& title) {
    out_file << "\n\n" << title << ":\n";
    for (const auto& s : vec) {
      out_file << "  " << s << "\n";
    }
    out_file << "\n";
  };

  // удобная, *настраиваемая* лямбда для записи векторов чисел в файл
  auto print_int_vec = [&out_file](const std::vector<int>& vec,
                                   const std::string& title) {
    out_file << title << ":\n";
    for (int len : vec) {
      out_file << len << "; ";
    }
    out_file << "\n";
  };

  // собсна запись в файл (не прям красивая, но какая есть)
  print_str_vec(lines, "Исходный вектор строк");
  print_str_vec(after_remove, "Вектор строк после удаления коротких строк");
  print_str_vec(after_replace, "Вектор строк после замены пробелов на '_'");
  out_file << "Первая строка содержащая \"" << word << "\":\n";
  out_file << "  " << line_with_word << "\n\n";
  out_file << "Общее количество символов без учёта '_' : " << totalChars
           << "\n\n";
  print_int_vec(vec_of_length, "Вектор длин строк");

  // усё
  out_file.close();
  return 0;
}
