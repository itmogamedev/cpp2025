#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// читаем строчки черезв вектор
// не считываем файл - выводим сор€нчик, считываем - дЄм дальш
bool readLines(const std::string& filename, std::vector<std::string>& lines) {
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Sorry, there is no such a file: " << filename << "\n";
    return false;
  }
  std::string line;
  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }
  return true;
}

void writeVector(std::ofstream& out, const std::string& header,
                 const std::vector<std::string>& vec) {
  out << header << "\n";
  std::for_each(vec.begin(), vec.end(),
                [&out](const std::string& s) { out << s << "\n"; });
  out << "\n";
}

int main() {
  // считываем инпут
  std::cout << std::filesystem::current_path() << "\n";
  std::vector<std::string> lines;
  if (!readLines("input.txt", lines)) {
    return 1;
  }

  std::ofstream output_file("output.txt");
  if (!output_file.is_open()) {
    std::cerr << "Error: cannot open output.txt\n";
    return 1;
  }

  // выводим наш вектор
  writeVector(output_file, "=== Original lines ===", lines);

  // убираем все строчки покороче
  int threshold = 0;
  std::cout << "Enter minimum line length (threshold): ";
  std::cin >> threshold;

  auto is_too_short = [threshold](const std::string& s) {
    return static_cast<int>(s.size()) < threshold;
  };
  lines.erase(std::remove_if(lines.begin(), lines.end(), is_too_short),
              lines.end());

  writeVector(output_file, "=== Lines after removing short lines ===", lines);

  // замен€ем тут пробелы на _
  std::for_each(lines.begin(), lines.end(), [](std::string& s) {
    std::replace(s.begin(), s.end(), ' ', '_');
  });

  writeVector(output_file,
              "=== Lines after replacing spaces with '_' ===", lines);

  // ищем искомое ищущим искателем слово
  std::string search_word;
  std::cout << "Enter a word to search for (only in Latin letters): ";
  std::cin >> search_word;

  auto contains_word = [&search_word](const std::string& s) {
    return s.find(search_word) != std::string::npos;
  };

  auto found_it = std::find_if(lines.begin(), lines.end(), contains_word);

  output_file << "=== Search result for word \"" << search_word << "\" ===\n";
  if (found_it != lines.end()) {
    output_file << "Found in line: " << *found_it << "\n";
  } else {
    output_file << "Word not found.\n";
  }
  output_file << "\n";

  // считаем длины длины выживших строк
  int total_chars = std::accumulate(
      lines.begin(), lines.end(), 0, [](int sum, const std::string& s) {
        return sum + static_cast<int>(std::count_if(
                         s.begin(), s.end(), [](char c) { return c != '_'; }));
      });

  output_file << "=== Total character count (excluding '_') ===\n";
  output_file << total_chars << "\n\n";

  // строим вектор из показателей длин выживших строк
  std::vector<int> lengths(lines.size());
  std::transform(
      lines.begin(), lines.end(), lengths.begin(),
      [](const std::string& s) { return static_cast<int>(s.size()); });

  output_file << "=== Vector of line lengths ===\n";
  std::for_each(lengths.begin(), lengths.end(),
                [&output_file](int len) { output_file << len << " "; });
  output_file << "\n";

  std::cout << "Done. Results written to output.txt\n";
  return 0;
}
