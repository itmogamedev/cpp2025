#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

void processHomework() {
    std::ifstream input("input.txt");
    std::vector<std::string> originalLines;
    std::string line;
    while (std::getline(input, line)) {
        originalLines.push_back(line);
    }
    input.close();

    int threshold;
    std::string searchWord;
    std::cout << "Enter length threshold: ";
    std::cin >> threshold;
    std::cin.ignore();
    std::cout << "Enter word to search: ";
    std::getline(std::cin, searchWord);

    std::vector<std::string> afterShort = originalLines;
    afterShort.erase(
        std::remove_if(afterShort.begin(), afterShort.end(),
            [threshold](const std::string& str) {
                return str.length() < threshold;
            }),
        afterShort.end());

    std::vector<std::string> afterReplace = afterShort;
    for (auto& str : afterReplace) {
        std::replace_if(str.begin(), str.end(),
            [](char c) { return c == ' '; }, '_');
    }

    std::string searchResult;
    auto foundIter = std::find_if(afterReplace.begin(), afterReplace.end(),
        [&searchWord](const std::string& str) {
            return str.find(searchWord) != std::string::npos;
        });
    searchResult = (foundIter != afterReplace.end())
        ? "Found: " + *foundIter
        : "Word not found.";

    int totalWithoutUnderscore = 0;
    for (const auto& str : afterReplace) {
        totalWithoutUnderscore += std::count_if(str.begin(), str.end(),
            [](char c) { return c != '_'; });
    }

    std::vector<int> lengths;
    std::transform(afterReplace.begin(), afterReplace.end(),
        std::back_inserter(lengths),
        [](const std::string& str) {
            return static_cast<int>(str.length());
        });

    std::ofstream output("output.txt");
    auto printBlock = [&output](const std::string& title,
        const std::vector<std::string>& vec) {
            output << title << ":\n";
            for (const auto& s : vec) {
                output << s << '\n';
            }
            output << '\n';
        };
    printBlock("Original vector of strings", originalLines);
    printBlock("After removing short strings", afterShort);
    printBlock("After replacing spaces with '_'", afterReplace);
    output << "Search result: " << searchResult << "\n\n";
    output << "Total number of characters without '_': "
        << totalWithoutUnderscore << "\n\n";
    output << "Vector of lengths:\n";
    for (size_t i = 0; i < lengths.size(); ++i) {
        output << lengths[i];
        if (i + 1 < lengths.size()) output << ' ';
    }
    output << std::endl;
    output.close();

    std::cout << "Processing finished. See output.txt" << std::endl;
}

int main() {
    processHomework();
    return 0;
}