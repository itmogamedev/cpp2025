#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace homework {

std::vector<std::string> readLinesFromFile(const std::string& filename);

std::vector<std::string> filterShortLines(const std::vector<std::string>& lines,
                                          std::size_t threshold);

std::vector<std::string> replaceSpacesWithUnderscore(
    const std::vector<std::string>& lines);

std::string findFirstLineWithWord(const std::vector<std::string>& lines,
                                  const std::string& word);

std::size_t countCharactersWithoutUnderscore(
    const std::vector<std::string>& lines);

std::vector<int> computeLineLengths(const std::vector<std::string>& lines);

void writeResultsToFile(const std::string& filename,
                        const std::vector<std::string>& original,
                        const std::vector<std::string>& filtered,
                        const std::vector<std::string>& replaced,
                        std::size_t threshold, const std::string& search_word,
                        const std::string& search_result,
                        std::size_t character_count,
                        const std::vector<int>& lengths);

void runHomework(const std::string& input_filename,
                 const std::string& output_filename, std::size_t threshold,
                 const std::string& search_word);

}  // namespace homework
