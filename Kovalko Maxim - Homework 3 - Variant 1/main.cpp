#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

void PrintVectorOfStrings(const std::string& title,
                          const std::vector<std::string>& vec,
                          std::ofstream& output_file) {
  output_file << "\n--- " << title << " ---\n";
  if (vec.empty()) {
    output_file << "(Вектор пуст)\n";
    return;
  }
  for (size_t i = 0; i < vec.size(); ++i) {
    output_file << "[" << i + 1 << "] " << vec[i] << "\n";
  }
}

void PrintVectorOfInts(const std::string& title, const std::vector<int>& vec,
                       std::ofstream& output_file) {
  output_file << "\n--- " << title << " ---\n";
  if (vec.empty()) {
    output_file << "(Вектор пуст)\n";
    return;
  }
  for (size_t i = 0; i < vec.size(); ++i) {
    output_file << "[" << i + 1 << "] " << vec[i] << "\n";
  }
}

int main() {
  // --- 1. Подготовка файлов и пользовательского ввода ---
  const std::string kInputFile = "input.txt";
  const std::string kOutputFile = "output.txt";

  // Открытие потоков для чтения и записи
  std::ifstream input_file(kInputFile);
  if (!input_file.is_open()) {
    std::cerr << "Ошибка: Не удалось открыть файл " << kInputFile
              << ". Убедитесь, что он находится в той же директории." << std::endl;
    return 1;
  }

  std::ofstream output_file(kOutputFile);
  if (!output_file.is_open()) {
    std::cerr << "Ошибка: Не удалось создать файл " << kOutputFile << "."
              << std::endl;
    return 1;
  }

  // Считывание всех строк из input.txt в исходный вектор
  std::vector<std::string> initial_lines;
  std::string line;
  while (std::getline(input_file, line)) {
    initial_lines.push_back(line);
  }
  input_file.close();

  // Запрос пользовательского ввода
  int threshold;
  std::cout << "Введите минимальную длину строки для фильтрации: ";
  std::cin >> threshold;
  std::cin.ignore();  // Очистка буфера после cin >> int

  std::string search_word;
  std::cout << "Введите слово для поиска (например, 'fun'): ";
  std::getline(std::cin, search_word);

  std::vector<std::string> filtered_lines;
  std::cout << "\n[INFO] Фильтрация строк... (Минимум " << threshold
            << " символов)" << std::endl;

  // Использование std::copy_if с лямбдой.
  // Захват `[threshold]` происходит по значению, что соответствует заданию.
  std::copy_if(initial_lines.begin(), initial_lines.end(),
               std::back_inserter(filtered_lines),
               [threshold](const std::string& s) {
                 return s.length() >= threshold;
               });

  std::vector<std::string> transformed_lines;
  std::cout << "[INFO] Выполнение Варианта 1: Замена пробелов..." << std::endl;

  for (const std::string& s : filtered_lines) {
    std::string new_s = s;
    size_t pos = 0;
    while ((pos = new_s.find(' ', pos)) != std::string::npos) {
      new_s.replace(pos, 1, "_");
      pos += 1;  // Перемещаемся на один символ дальше для избежания бесконечного цикла
    }
    transformed_lines.push_back(new_s);
  }

  std::string search_result;

  auto found = std::any_of(
      filtered_lines.begin(), filtered_lines.end(),
      [&search_word](const std::string& s) {
        return s.find(search_word) != std::string::npos;
      });

  if (found) {
    search_result = "В векторе найдена хотя бы одна строка, содержащая слово \"" +
                    search_word + "\".";
  } else {
    search_result = "Слово \"" + search_word + "\" не найдено ни в одной строке.";
  }

  long long total_char_count = 0;
  // Используем std::accumulate. Лямбда подсчитывает символы, кроме '_'
  total_char_count = std::accumulate(
        filtered_lines.begin(), filtered_lines.end(), 0LL,
        [&](long long current_sum, const std::string& s) {
          long long count = 0;
          for (char c : s) {
            if (c != '_') {
              count++;
            }
          }
          return current_sum + count;
        });

  std::vector<int> length_vector;

  // Используем std::transform для создания нового вектора из длин элементов
  std::transform(filtered_lines.begin(), filtered_lines.end(),
                 std::back_inserter(length_vector),
                 [](const std::string& s) {
                   return static_cast<int>(s.length());
                 });

  output_file << "========================================================\n";
  output_file << "             Результаты обработки\n";
  output_file << "========================================================\n";

  // 1. Исходный вектор строк
  PrintVectorOfStrings("Исходный Вектор Строк", initial_lines, output_file);

  // 2. Вектор после удаления коротких строк
  PrintVectorOfStrings(
      "Вектор После Фильтрации (Длина >= " + std::to_string(threshold) + ")",
      filtered_lines, output_file);

  // 3. Вектор после замены пробелов на "_" (Вариант 1)
  PrintVectorOfStrings(
      "Финальный Вектор После Трансформации (Пробел -> _)",
      transformed_lines, output_file);

  // 4. Результат поиска слова
  output_file << "\n--- Результат Поиска Слова ---\n";
  output_file << search_result << "\n";

  // 5. Общее количество символов без "_"
  output_file << "\n========================================================\n";
  output_file << "Общее количество символов во всех строках (без учета '_'): "
               << total_char_count << "\n";

  // 6. Вектор длин строк
  PrintVectorOfInts("Вектор Длин Строк", length_vector, output_file);

  std::cout << "\n========================================================\n";
  std::cout << "Обработка завершена успешно!\n";
  std::cout << "Все результаты записаны в файл: " << kOutputFile << std::endl;

  return 0;
}
