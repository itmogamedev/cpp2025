#include <iostream>
#include <string>

#include "../Header Files/text_processor.h"

int main() {
  std::size_t threshold = 0;
  std::cout << "Enter minimum line length threshold: ";
  std::cin >> threshold;
  std::cin.ignore();
  std::string search_word;
  std::cout << "Enter word to search: ";
  std::getline(std::cin, search_word);
  homework::runHomework("input.txt", "output.txt", threshold, search_word);
  std::cout << "Done. Results written to output.txt\n";
  return 0;
}
