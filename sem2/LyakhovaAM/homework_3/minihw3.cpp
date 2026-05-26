#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void solve() {
  std::vector<std::string> v_str;
  std::vector<int> str_len;

  auto del = [=](int length, std::vector<std::string>& v_str) {
    for (std::vector<std::string>::iterator it = v_str.begin();
         it != v_str.end();)
      if (it->size() < length)
        it = v_str.erase(it);
      else
        ++it;
  };

  auto replace = [=](std::vector<std::string>& v_str) {
    for (int i = 0; i < v_str.size(); ++i)
      for (int j = 0; j < v_str[i].size(); ++j)
        if (v_str[i][j] == ' ') v_str[i][j] = '_';
  };

  auto search = [&](const std::string& str) {
    for (int i = 0; i < v_str.size(); ++i) {
      int ind = v_str[i].find(str);
      if (ind < v_str[i].size()) return i;
    }
    return -1;
  };

  auto numberSymbols = [&]() {
    int count = 0;
    for (int i = 0; i < v_str.size(); ++i)
      for (int j = 0; j < v_str[i].size(); ++j)
        if (v_str[i][j] != '_') ++count;
    return count;
  };

  auto lenStrings = [&]() {
    str_len.resize(v_str.size());
    for (int i = 0; i < v_str.size(); ++i) str_len[i] = v_str[i].size();
  };

  std::ifstream file_input;
  std::ofstream file_output;
  std::string str;
  file_input.open("input.txt");
  file_output.open("output.txt");

  file_output << "File input:\n";
  while (std::getline(file_input, str)) {
    file_output << str << '\n';
    v_str.push_back(str);
  }

  int length;
  std::cout << "Enter the length of the string, less than which the strings "
               "will be deleted: ";
  std::cin >> length;
  del(length, v_str);
  file_output << "\nThe length of the string, less than which the strings were "
                 "deleted: "
              << length << "\nFile after that:\n";
  for (int i = 0; i < v_str.size(); ++i) file_output << v_str[i] << '\n';

  replace(v_str);
  file_output << "\nFile after replacing symbols:\n";
  for (int i = 0; i < v_str.size(); ++i) file_output << v_str[i] << '\n';

  std::cout << "\nWhat word will you search? ";
  std::cin >> str;
  int position;
  position = search(str);
  if (position != -1)
    file_output << "\nWord '" << str << "' found in string " << position + 1
                << '\n';
  else
    file_output << "\nWord '" << str << "' not found\n";

  int count;
  count = numberSymbols();
  file_output << "\nNumber of symbols: " << count << '\n';

  lenStrings();
  file_output << "\nLengths of strings:\n";
  for (auto length : str_len) file_output << length << '\n';
}

int main() {
  solve();
  return 0;
}
