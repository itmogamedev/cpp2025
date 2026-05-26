#include <string>
#include <vector>
void work();
class TextProcessor {
 public:
  bool loadFromFile(const std::string& filename);
  void saveToFile(const std::string& filename, int threshold,
                  const std::string& search_word) const;
  void removeShortLines(int threshold);
  void replaceSpacesWithUnderscore();
  std::string findLineWithWord(const std::string& word) const;
  int countCharsWithoutUnderscore() const;

  const std::vector<int>& getLengths() const { return lengths; }
  const std::vector<std::string>& getCurrentLines() const {
    return current_lines;
  }
  const std::vector<std::string>& getOriginalLines() const {
    return original_lines;
  }

 private:
  std::vector<std::string> original_lines;
  std::vector<std::string> current_lines;
  std::vector<int> lengths;
};
