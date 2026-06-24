#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

const std::set<char> kLetters = {'A', 'E', 'I', 'O', 'U', 'Y',
                                'a', 'e', 'i', 'o', 'u', 'y'};

int main() {
  int int_input;
  std::string str_input;
  std::vector<std::string> lines;
  std::ifstream file_in("input.txt");
  if (file_in.is_open()) {
    std::string line;
    while (std::getline(file_in, line)) {
      lines.push_back(line);
    }

    file_in.close();
  } else {
    std::cerr << "Unable to open input.txt file" << std::endl;
  }

  auto f1 = [lines](int n) mutable {
    for (int i = 0; i < lines.size(); ++i) {
      if (lines[i].size() < n) {
        lines.erase(lines.begin() + i--);
      }
    }

    return lines;
  };

  auto f2 = [lines]() mutable {
    for (int i = 0; i < lines.size(); ++i) {
      for (int j = 0; j < lines[i].size(); ++j) {
        if (kLetters.find(lines[i][j]) != kLetters.end()) {
          lines[i].erase(lines[i].begin() + j--);
        }
      }
    }

    return lines;
  };

  auto f3 = [&lines](const std::string& word) {
    for (int i = 0; i < lines.size(); ++i) {
      if (lines[i].find(word) != std::string::npos) {
        return true;
      }
    }

    return false;
  };

  auto f4 = [&lines]() {
    size_t sum = 0;
    for (int i = 0; i < lines.size(); ++i) {
      for (int j = 0; j < lines[i].size(); ++j) {
        if (lines[i][j] != '_') {
          ++sum;
        }
      }
    }

    return sum;
  };

  auto f5 = [&lines]() {
    std::vector<int> result;
    for (int i = 0; i < lines.size(); ++i) {
      result.push_back(lines[i].size());
    }

    return result;
  };

  std::cout << "Enter number to sort out lines by size:\n";
  std::cin >> int_input;

  auto result1 = f1(int_input);
  auto result2 = f2();

  std::cout << "Enter word to look for in lines:\n";
  std::cin >> str_input;

  auto result3 = f3(str_input);
  auto result4 = f4();
  auto result5 = f5();

  std::ofstream file_out("output.txt");
  if (file_out.is_open()) {
    auto f_cout = [&file_out]<typename T>(T& s) mutable {
      file_out << s << '\n';
    };
    std::for_each(result1.begin(), result1.end(), f_cout);
    file_out << '\n';
    std::for_each(result2.begin(), result2.end(), f_cout);
    file_out << '\n';
    file_out << (result3 ? "Found it! :)\n" : "Not Found :(\n");
    file_out << '\n';
    f_cout(result4);
    file_out << '\n';
    std::for_each(result5.begin(), result5.end(), f_cout);

    file_out.close();
  } else {
    std::cerr << "Unable to open outpun.txt file" << std::endl;
  }
  return 0;
}
