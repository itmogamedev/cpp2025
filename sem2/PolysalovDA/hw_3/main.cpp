#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

void writeOutputFile(const std::vector<std::string>& data,
                     const std::vector<std::string>& filtered_data,
                     const std::vector<std::string>& removed_vowels_data,
                     int word_index, int total_characters_no_vowels,
                     const std::vector<int>& strings_lengths) {
  std::ofstream output_file("output.txt");
  if (output_file.is_open()) {
    output_file << "Original data:\n";
    for (const auto& line : data) {
      output_file << line << std::endl;
    }
    output_file << '\n';
    output_file << "Filtered data:\n";
    for (const auto& line : filtered_data) {
      output_file << line << std::endl;
    }
    output_file << '\n';
    output_file << "Data with vowels removed:\n";
    for (const auto& line : removed_vowels_data) {
      output_file << line << std::endl;
    }
    output_file << '\n';
    output_file << "Search result: " << word_index << std::endl;
    output_file << '\n';
    output_file << "Total characters without vowels: "
                << total_characters_no_vowels << std::endl;
    output_file << '\n';
    output_file << "Lengths of strings: " << "\n";
    for (const auto& length : strings_lengths) {
      output_file << length << std::endl;
    }
    output_file.close();
  }
}

std::vector<std::string> readInputFile() {
  std::vector<std::string> data;
  std::ifstream input_file("input.txt");
  std::string line;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      data.push_back(line);
    }
    input_file.close();
  }
  return data;
}

std::tuple<std::vector<std::string>, std::vector<std::string>,
           std::vector<std::string>, int, int, std::vector<int>>
processData() {
  std::vector<std::string> data = readInputFile();

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

  auto filterData = [=]() -> std::vector<std::string> {
    int barrier = inputBarrier();
    std::vector<std::string> result;
    std::copy_if(
        data.begin(), data.end(), std::back_inserter(result),
        [=](const std::string& str) { return str.length() >= barrier; });
    return result;
  };

  auto removeVowels = [=]() -> std::vector<std::string> {
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
                        std::tolower(c) != 'u');
              });
          return new_str;
        });
    return result;
  };

  auto findWord = [&]() -> int {
    std::string word = inputWord();
    auto it =
        std::find_if(data.begin(), data.end(), [&](const std::string& str) {
          return str.find(word) != std::string::npos;
        });
    if (it != data.end()) {
      return std::distance(data.begin(), it);
    } else {
      return -1;
    }
  };

  auto countTotalCharacters =
      [&](const std::vector<std::string>& some_data) -> int {
    int total = 0;
    for (const auto& line : some_data) {
      total += line.length();
    }
    return total;
  };

  auto countStringsLengths =
      [&](const std::vector<std::string>& some_data) -> std::vector<int> {
    std::vector<int> lengths;
    std::transform(some_data.begin(), some_data.end(),
                   std::back_inserter(lengths),
                   [](const std::string& str) { return str.length(); });
    return lengths;
  };

  std::vector<std::string> filtered_data = filterData();
  std::vector<std::string> removed_vowels_data = removeVowels();
  int word_index = findWord();
  int total_characters_no_vowels = countTotalCharacters(removed_vowels_data);
  std::vector<int> strings_lengths = countStringsLengths(data);

  return {data,
          filtered_data,
          removed_vowels_data,
          word_index,
          total_characters_no_vowels,
          strings_lengths};
}

int main() {
  auto [data, filtered_data, removed_vowels_data, word_index, total_no_wovels,
        strings_length] = processData();
  writeOutputFile(data, filtered_data, removed_vowels_data, word_index,
                  total_no_wovels, strings_length);
  return 0;
}