#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main() {
  char* locale = setlocale(LC_ALL, "");

  std::ifstream file("input.txt");
  std::vector<std::string> lines;
  std::string line;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  }

  int porog;

  std::cout << "—ÚÓÍË, ‰ÎËÌ‡ ÍÓÚÓ˚ı ÏÂÌ¸¯Â ÔÓÓ„‡, Û‰‡ÎˇÚÒˇ. ¬‚Â‰ËÚÂ ÔÓÓ„: ";
  std::cin >> porog;

  auto f1 = [porog](std::string s) { return s.length() < porog; };
  std::vector<std::string> poroglines = lines;
  poroglines.erase(std::remove_if(poroglines.begin(), poroglines.end(), f1),
                   poroglines.end());

  auto f2 = [](std::string s) {
    std::replace(s.begin(), s.end(), ' ', '_');
    return s;
  };
  std::vector<std::string> lineswospace;
  for (auto line : lines) {
    lineswospace.push_back(f2(line));
  }

  std::string word;
  std::cout << "¬‚Â‰ËÚÂ ÒÎÓ‚Ó ‰Îˇ ÔÓËÒÍ‡: ";
  std::cin >> word;

  auto f3 = [&word](std::string str) -> bool {
    return str.find(word) != std::string::npos;
  };

  std::vector<std::string> found;
  for (auto line : lines) {
    if (f3(line)) {
      found.push_back(line);
    }
  }

  auto f4 = [](char c) { return c != '_'; };
  int allchars = 0;

  for (auto str : lines) {
    allchars += std::count_if(str.begin(), str.end(), f4);
  }

  std::vector<int> lengthstr;
  auto f5 = [](std::string str) -> int { return str.length(); };

  for (auto str : lines) {
    lengthstr.push_back(f5(str));
  }

  // ‚‚Ó‰
  std::ofstream file2("output.txt");

  file2 << "»—’ŒƒÕ€… ¬≈ “Œ– —“–Œ :\n";
  for (int i = 0; i < lines.size(); ++i) {
    file2 << "  " << std::setw(4) << (i + 1) << ". \"" << lines[i] << "\"\n";
  }

  file2 << "\n¬≈ “Œ– —“–Œ  œŒ—À≈ ”ƒ¿À≈Õ»ﬂ  Œ–Œ“ »’ —“–Œ :\n";
  file2 << " œÓÓ„: " << porog << " ÒËÏ‚ÓÎÓ‚\n";
  for (int i = 0; i < poroglines.size(); ++i) {
    file2 << "  " << std::setw(4) << (i + 1) << ". \"" << poroglines[i]
          << "\" (" << poroglines[i].length() << ")\n";
  }

  file2 << "\n¬≈ “Œ– —“–Œ  œŒ—À≈ «¿Ã≈Õ€ œ–Œ¡≈ÀŒ¬ Õ¿ \"_\":\n";
  for (int i = 0; i < lineswospace.size(); ++i) {
    file2 << "  " << std::setw(4) << (i + 1) << ". \"" << lineswospace[i]
          << "\"\n";
  }

  file2 << "\n–≈«”À‹“¿“ œŒ»— ¿ «¿ƒ¿ÕÕŒ√Œ —ÀŒ¬¿:\n";
  file2 << "»ÒÍÓÏÓÂ ÒÎÓ‚Ó: " << word << "\n";
  for (int i = 0; i < found.size(); ++i) {
    file2 << "     " << (i + 1) << ". " << found[i] << "\n";
  }

  file2 << "\nŒ¡Ÿ≈≈  ŒÀ»◊≈—“¬Œ —»Ã¬ŒÀŒ¬ ¡≈« \"_\": " << allchars << "\n";

  file2 << "\n¬≈ “Œ– ƒÀ»Õ —“–Œ :\n";
  for (int i = 0; i < lengthstr.size(); ++i) {
    file2 << "  " << std::setw(4) << (i + 1) << ". " << lengthstr[i] << "\n";
  }
}
