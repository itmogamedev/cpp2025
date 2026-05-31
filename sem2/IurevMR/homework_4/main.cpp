#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

std::vector<int> generateVector(std::size_t size = 20) {
    std::vector<int> data(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-50, 100);

    std::generate(data.begin(), data.end(), [&]() {
        return dist(gen);
    });

    return data;
}

void printVector(std::ofstream& out, const std::string& title, const std::vector<int>& data) {
    out << title;

    if (data.empty()) {
        out << "empty";
    } else {
        std::copy(data.begin(), data.end(), std::ostream_iterator<int>(out, " "));
    }

    out << '\n';
}

void writeMinMax(std::ofstream& out, const std::vector<int>& data) {
    auto [minIt, maxIt] = std::minmax_element(data.begin(), data.end());

    out << "Minimum element: " << *minIt << '\n';
    out << "Maximum element: " << *maxIt << '\n';
}

void sortAscending(std::vector<int>& data) {
    std::sort(data.begin(), data.end());
}

void writeCounts(std::ofstream& out, const std::vector<int>& data) {
    auto positiveCount = std::count_if(data.begin(), data.end(), [](int value) {
        return value > 0;
    });

    auto negativeCount = std::count_if(data.begin(), data.end(), [](int value) {
        return value < 0;
    });

    auto zeroCount = std::count(data.begin(), data.end(), 0);

    out << "Positive count: " << positiveCount << '\n';
    out << "Negative count: " << negativeCount << '\n';
    out << "Zero count: " << zeroCount << '\n';
}

double calculateAverage(const std::vector<int>& data) {
    int sum = std::accumulate(data.begin(), data.end(), 0);

    return static_cast<double>(sum) / static_cast<double>(data.size());
}

void writeAverage(std::ofstream& out, const std::vector<int>& data) {
    out << "Average: " << calculateAverage(data) << '\n';
}

void removeEvenNumbers(std::vector<int>& data) {
    auto newEnd = std::remove_if(data.begin(), data.end(), [](int value) {
        return value % 2 == 0;
    });

    data.erase(newEnd, data.end());
}

std::vector<int> makeSortedUniqueVector(std::vector<int> data) {
    std::sort(data.begin(), data.end());

    auto newEnd = std::unique(data.begin(), data.end());

    data.erase(newEnd, data.end());

    return data;
}

void processVariant1() {
    auto data = generateVector();
    std::ofstream out("output.txt");

    printVector(out, "Generated vector: ", data);

    writeMinMax(out, data);

    sortAscending(data);
    printVector(out, "Sorted vector: ", data);

    writeCounts(out, data);

    writeAverage(out, data);

    removeEvenNumbers(data);
    printVector(out, "Vector without even numbers: ", data);

    auto uniqueData = makeSortedUniqueVector(data);
    printVector(out, "Sorted unique vector: ", uniqueData);
}

int main() {
    processVariant1();

    return 0;
}
