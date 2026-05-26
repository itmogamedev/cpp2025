#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void execute(std::string in, std::string out, int thr, std::string word) {
  std::ifstream fin(in);
  std::ofstream fout(out);
  std::vector<std::string> v, v_orig, v_filt;
  std::string s;

  if (!fin.is_open()) return;
  while (std::getline(fin, s)) v.push_back(s);
  v_orig = v;

  v.erase(std::remove_if(v.begin(), v.end(),
                         [thr](std::string s) { return s.length() < thr; }),
          v.end());
  v_filt = v;

  for (auto& line : v)
    for (char& c : line)
      if (c == ' ') c = '_';
  auto it = std::find_if(v.begin(), v.end(), [&word](std::string s) {
    return s.find(word) != std::string::npos;
  });

  int total = 0;
  std::vector<int> lens;
  for (const auto& line : v) {
    int count = 0;
    for (char c : line)
      if (c != '_') count++;
    total += count;
    lens.push_back((int)line.length());
  }

  fout << "1. Original:\n";
  for (const auto& x : v_orig) fout << x << "\n";
  fout << "\n2. After removing short lines:\n";
  for (const auto& x : v_filt) fout << x << "\n";
  fout << "\n3. After replacing spaces with '_':\n";
  for (const auto& x : v) fout << x << "\n";
  fout << "\n4. Search result for '" << word
       << "': " << (it != v.end() ? *it : "Not found") << "\n";
  fout << "\n5. Total characters (excluding '_'): " << total
       << "\n\n6. Line lengths: ";
  for (int l : lens) fout << l << " ";
}

int main() {
  execute("input.txt", "output.txt", 5, "C++");
  return 0;
}