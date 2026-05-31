// VARIANT 1
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

template <typename T>
void init(T& vec) {
  std::ofstream output_file("output.txt");
  output_file.clear();

  std::ifstream file("input.txt");
  std::string line;

  if (!file.is_open() || !output_file.is_open()) {
    std::cout << "Failed to open file" << std::endl;
  }

  std::string input_vec{"Input vector: {"};
  while (std::getline(file, line)) {
    vec.push_back(line);
    input_vec += line + "; ";
  }

  input_vec.erase(input_vec.length() - 2);
  input_vec += "}";
  output_file << input_vec << '\n';

  file.close();
  output_file.close();
}

void output(std::string data) {
  std::ofstream file("output.txt", std::ios::app);

  if (!file.is_open()) {
    std::cout << "Failed to open file" << std::endl;
  }

  file << data << '\n';
  file.close();
}

int main() {
  std::string str{};

  // INIT
  std::vector<std::string> vec{};
  init(vec);

  // LIMIT
  int limit{};
  std::cout << "Enter the limit of string length: ";
  std::cin >> limit;

  auto tempVecFormation = [limit, vec](std::vector<std::string> temp = {}) {
    for (int i{0}; i < vec.size(); i++) {
      if (vec[i].length() <= limit) {
        temp.push_back(vec[i]);
      }
    }
    return temp;
  };
  std::vector<std::string> temp_vec{tempVecFormation()};
  vec = std::move(temp_vec);

  str = "Strings with length over " + std::to_string(limit) + ": {";
  std::for_each(begin(vec), end(vec),
                [&str](std::string elem) { str += elem + "; "; });
  str.erase(str.length() - 2);
  str += "}";
  output(str);

  // SPACES TO _
  str = "Spaces changed to _ : {";
  std::for_each(begin(vec), end(vec), [&str](std::string& elem) {
    elem = std::regex_replace(elem, std::regex(" "), "_");
    str += elem + "; ";
  });
  str.erase(str.length() - 2);
  str += "}";
  output(str);

  // STRING SEARCH BY WORD
  std::string word{};
  std::cout << "Enter a word to find the string that contains it: ";
  std::cin >> word;

  str = "String that contains word " + word + ": ";
  auto search = [&]() {
    for (auto i{0}; i < vec.size(); i++) {
      if (vec[i].find(word) != std::string::npos) {
        str += vec[i];
        break;
      }
    }
  };
  search();
  output(str);

  // STRING LENGTH
  int count{};
  std::for_each(begin(vec), end(vec), [&count](std::string elem) {
    count += (elem.length() - std::count_if(begin(elem), end(elem),
                                            [](char c) { return c == '_'; }));
  });

  str = "Total number of characters without _ : " + std::to_string(count);
  output(str);

  // VECTOR OF LEN'S
  str = "Vector of strings lengths: {";
  std::vector<int> length_vec{};
  std::for_each(begin(vec), end(vec), [&length_vec, &str](auto elem) {
    auto count = elem.length() - std::count_if(begin(elem), end(elem),
                                               [](char c) { return c == '_'; });
    length_vec.push_back(count);
    str += std::to_string(count) + "; ";
  });

  str.erase(str.length() - 2);
  str += "}";
  output(str);

  return 0;
}
