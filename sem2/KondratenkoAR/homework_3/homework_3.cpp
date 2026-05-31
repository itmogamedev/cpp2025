#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(in, line))
    lines.push_back(line);

  for (const auto& s : lines)
    out << s << "\n";
  out << "\n";

  int threshold;
  std::cout << "Enter threshold: ";
  std::cin >> threshold;

  lines.erase(
      std::remove_if(lines.begin(), lines.end(),
                     [threshold](const auto& s) { return (int)s.size() < threshold; }),
      lines.end());

  for (const auto& s : lines)
    out << s << "\n";
  out << "\n";

  for (auto& s : lines)
    std::replace(s.begin(), s.end(), ' ', '_');

  for (const auto& s : lines)
    out << s << "\n";
  out << "\n";

  std::string word;
  std::cout << "Enter word: ";
  std::cin >> word;

  auto it = std::find_if(lines.begin(), lines.end(),
                         [&word](const auto& s) { return s.find(word) != std::string::npos; });

  if (it != lines.end())
    out << "Found: " << *it << "\n";
  else
    out << "Not found\n";
  out << "\n";

  int total = 0;
  for (const auto& s : lines)
    for (char c : s)
      if (c != '_') total++;

  out << total << "\n\n";

  for (const auto& s : lines)
    out << s.size() << " ";

  return 0;
}