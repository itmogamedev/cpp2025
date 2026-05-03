#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void writeOutputFile(
    const std::tuple<std::vector<std::string>, std::vector<std::string>,
                     std::vector<std::string>, int, int, std::vector<int>>&
        data_tuple,
    std::ofstream& output_file) {
  auto [data, filtered_data, removed_vowels_data, word_index, total_no_vowels,
        strings_lengths] = data_tuple;

  if (output_file.is_open()) {
    output_file << "Original data:\n";
    std::for_each(data.begin(), data.end(),
                  [&](const auto& line) { output_file << line << std::endl; });
    output_file << '\n';
    output_file << "Filtered data:\n";
    std::for_each(filtered_data.begin(), filtered_data.end(),
                  [&](const auto& line) { output_file << line << std::endl; });
    output_file << '\n';
    output_file << "Data with vowels removed:\n";
    std::for_each(removed_vowels_data.begin(), removed_vowels_data.end(),
                  [&](const auto& line) { output_file << line << std::endl; });
    output_file << '\n';
    output_file << "Search result: " << word_index << std::endl;
    output_file << '\n';
    output_file << "Total characters without vowels: " << total_no_vowels
                << std::endl;
    output_file << '\n';
    output_file << "Lengths of strings:\n";
    std::for_each(
        strings_lengths.begin(), strings_lengths.end(),
        [&](const auto& length) { output_file << length << std::endl; });
    output_file.close();
  }
}

auto readInputFile = [](std::ifstream& input_file) -> std::vector<std::string> {
  std::vector<std::string> data;
  std::string line;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      data.push_back(line);
    }
    input_file.close();
  }
  return data;
};

auto inputBarrier = []() -> int {
  int barrier;
  std::cout << "Enter the barrier of strings length(string that less than "
               "barrier will be removed): ";
  std::cin >> barrier;
  return barrier;
};

auto inputWord = []() -> std::string {
  std::string word;
  std::cout << "Enter the word to search: ";
  std::cin >> word;
  return word;
};

auto filterData =
    [](int barrier,
       const std::vector<std::string>& data) -> std::vector<std::string> {
  std::vector<std::string> result;
  std::copy_if(
      data.begin(), data.end(), std::back_inserter(result),
      [barrier](const std::string& str) { return str.length() >= barrier; });
  return result;
};

auto removeVowels =
    [](const std::vector<std::string>& data) -> std::vector<std::string> {
  std::vector<std::string> result;
  std::transform(
      data.begin(), data.end(), std::back_inserter(result),
      [](const std::string& str) {
        std::string new_str;
        std::copy_if(
            str.begin(), str.end(), std::back_inserter(new_str), [](char c) {
              return !std::isalpha(c) ||
                     (std::tolower(c) != 'a' && std::tolower(c) != 'e' &&
                      std::tolower(c) != 'i' && std::tolower(c) != 'o' &&
                      std::tolower(c) != 'u' && std::tolower(c) != 'y');
            });
        return new_str;
      });
  return result;
};

auto findWord = [](const std::vector<std::string>& some_data,
                   const std::string& word) -> int {
  auto it = std::find_if(some_data.begin(), some_data.end(),
                         [&](const std::string& str) {
                           return str.find(word) != std::string::npos;
                         });
  if (it != some_data.end()) {
    return std::distance(some_data.begin(), it);
  } else {
    return -1;
  }
};

auto countTotalCharacters =
    [](const std::vector<std::string>& some_data) -> int {
  return std::accumulate(some_data.begin(), some_data.end(), 0,
                         [](int total, const std::string& str) {
                           return total + static_cast<int>(str.length());
                         });
};

auto countStringsLengths =
    [](const std::vector<std::string>& some_data) -> std::vector<int> {
  std::vector<int> lengths;
  std::transform(
      some_data.begin(), some_data.end(), std::back_inserter(lengths),
      [](const std::string& str) { return static_cast<int>(str.length()); });
  return lengths;
};

auto processData = [](const std::vector<std::string>& data, int barrier,
                      const std::string& word) {
  std::vector<std::string> filtered_data = filterData(barrier, data);
  std::vector<std::string> removed_vowels_data = removeVowels(data);
  int word_index = findWord(data, word);
  int total_characters_no_vowels = countTotalCharacters(removed_vowels_data);
  std::vector<int> strings_lengths = countStringsLengths(data);

  return std::make_tuple(data, filtered_data, removed_vowels_data, word_index,
                         total_characters_no_vowels, strings_lengths);
};

int main() {
  std::ifstream input_file("input.txt");
  std::ofstream output_file("output.txt");
  std::vector<std::string> data = readInputFile(input_file);
  int barrier = inputBarrier();
  std::string word = inputWord();
  writeOutputFile(processData(data, barrier, word), output_file);
  return 0;
}