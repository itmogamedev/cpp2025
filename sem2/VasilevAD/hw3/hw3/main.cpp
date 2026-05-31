#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>


int main() {
  std::ifstream in_file("input.txt");
  if (!in_file.is_open()) {
    std::cerr << "Failed to open input.txt\n";
    return 1;
  }

  std::vector<std::string> original_lines;
  std::string current_line;
  while (std::getline(in_file, current_line)) {
    original_lines.push_back(current_line);
  }
  in_file.close();

  // ввод параметров
  size_t length_threshold = 0;
  std::cout << "Enter the minimum string length threshold: ";
  std::cin >> length_threshold;

  std::string search_word;
  std::cout << "Enter the word to search for: ";
  std::cin >> search_word;

  std::ofstream out_file("output.txt");
  if (!out_file.is_open()) {
    std::cerr << "Failed to open output.txt\n";
    return 1;
  }

  // вектор в который записываем
  std::vector<std::string> working_lines = original_lines;


  printVectorString(out_file, working_lines, "Original strings");

  // удаление коротких строк (лямбда с захватом по значению)
  working_lines.erase(std::remove_if(working_lines.begin(), working_lines.end(),
                                     [length_threshold](const std::string& s) {
                                      return s.length() < length_threshold; }),
                                      working_lines.end());

  printVectorString(out_file, working_lines, "After removing short strings");

  // замена всех пробелов
  std::for_each(working_lines.begin(), working_lines.end(), [](std::string& s) {
    std::replace(s.begin(), s.end(), ' ', '_');
  });

  printVectorString(out_file, working_lines, "After replacing spaces with '_'");

  // поиск строки
  auto found_it = std::find_if(working_lines.begin(), working_lines.end(),
                   [&search_word](const std::string& s) {
                     return s.find(search_word) != std::string::npos;
                   });

  out_file << "--- Search result for word '" << search_word << "' ---\n";
  if (found_it != working_lines.end()) {
    out_file << "Found in string: " << *found_it << "\n\n";
  } else {
    out_file << "Word not found.\n\n";
  }

  // подсчёт количества символов
  int char_count = std::accumulate(
      working_lines.begin(), working_lines.end(), 0,
      [](int current_sum, const std::string& s) {
        return current_sum + std::count_if(s.begin(), s.end(),
                                           [](char c) { return c != '_'; });
      });

  out_file << "--- Total characters excluding '_' ---\n";
  out_file << char_count << "\n\n";

  // создание нового вектора
  std::vector<int> lengths;
  lengths.reserve(working_lines.size());
  std::transform(
      working_lines.begin(), working_lines.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });

  printVectorInt(out_file, lengths, "Lengths of strings");

  out_file.close();
  std::cout << "Processing complete. Results are saved in output.txt\n";

  return 0;
}


void printVectorString(std::ofstream& out, const std::vector<std::string>& vec,
                       const std::string& title) {
  out << "--- " << title << " ---\n";
  for (const auto& str : vec) {
    out << str << "\n";
  }
  out << "\n";
}

void printVectorInt(std::ofstream& out, const std::vector<int>& vec,
                    const std::string& title) {
  out << "--- " << title << " ---\n";
  for (const auto& val : vec) {
    out << val << " ";
  }
  out << "\n\n";
}