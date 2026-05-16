#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    //Открываем файл input.txt для чтения исходных данных
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть input.txt" << std::endl;
        return 1;
    }

    //Читаем все строки из файла в вектор allLines
    std::vector<std::string> allLines;
    std::string currentLine;
    while (std::getline(inputFile, currentLine)) {
        allLines.push_back(currentLine);
    }
    inputFile.close();

    //Создаём файл output.txt, куда запишем все результаты
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: не удалось создать output.txt" << std::endl;
        return 1;
    }

    //Выводим исходный вектор строк
    std::cout << "Original lines from input.txt" << std::endl;
    for (const auto& line : allLines) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;

    outputFile << "Original vector of strings:" << std::endl;
    for (const auto& line : allLines) {
        outputFile << line << std::endl;
    }
    outputFile << std::endl;

    //Удаляем строки короче порога
    //Просим пользователя ввести минимальную длину
    std::cout << "Enter the minimum length threshold: ";
    int minLength;
    std::cin >> minLength;

    //Копируем исходный вектор, чтобы не потерять оригинал
    std::vector<std::string> linesAfterFilter = allLines;

    //Удаляем короткие строки с помощью лямбды
    //Лямбда захватывает minLength по значению [minLength]
    //чтобы порог не менялся во время работы алгоритма
    linesAfterFilter.erase(
        std::remove_if(linesAfterFilter.begin(), linesAfterFilter.end(),
            [minLength](const std::string& line) {
                return line.length() < static_cast<std::string::size_type>(minLength);
            }),
        linesAfterFilter.end()
    );

    //Выводим результат после фильтрации
    std::cout << "\n=== After removing lines shorter than " << minLength << " ===" << std::endl;
    for (const auto& line : linesAfterFilter) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;

    outputFile << "Vector of strings after removing short strings:" << std::endl;
    for (const auto& line : linesAfterFilter) {
        outputFile << line << std::endl;
    }
    outputFile << std::endl;

    //Заменяем пробелы на подчёркивания
    //Делаем копию, чтобы сохранить предыдущий этап
    std::vector<std::string> linesAfterReplace = linesAfterFilter;

    //Алгоритм замены: проходим по каждой строке и меняем ' ' на '_'
    //Используем лямбду внутри for_each
    std::for_each(linesAfterReplace.begin(), linesAfterReplace.end(), [](std::string& line) {
        std::replace(line.begin(), line.end(), ' ', '_');
    });

    std::cout << "After replacing spaces with underscores " << std::endl;
    for (const auto& line : linesAfterReplace) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;

    outputFile << "Vector of strings after replacing spaces with \"_\":" << std::endl;
    for (const auto& line : linesAfterReplace) {
        outputFile << line << std::endl;
    }
    outputFile << std::endl;

    //Поиск строки с заданным словом
    std::cout << "Enter the word to search for: ";
    std::string targetWord;
    std::cin >> targetWord;

    //Ищем первую строку, которая содержит targetWord
    //Лямбда захватывает targetWord по ссылке [&targetWord]
    auto foundIt = std::find_if(linesAfterReplace.begin(), linesAfterReplace.end(),
        [&targetWord](const std::string& line) {
            return line.find(targetWord) != std::string::npos;
        });

    std::cout << "\n Search result for word \"" << targetWord << "\" " << std::endl;
    if (foundIt != linesAfterReplace.end()) {
        std::cout << "Found: " << *foundIt << std::endl;
        outputFile << "Result of search for the word \"" << targetWord << "\": " << *foundIt << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
        outputFile << "Result of search for the word \"" << targetWord << "\": Not found" << std::endl;
    }
    std::cout << std::endl;
    outputFile << std::endl;

    //Считаем общее количество символов без подчёркиваний
    //Проходим по всем строкам после замены и считаем только "полезные" символы
    size_t totalCharacters = 0;
    for (const auto& line : linesAfterReplace) {
        for (char symbol : line) {
            if (symbol != '_') {
                ++totalCharacters;
            }
        }
    }

    std::cout << "Total number of characters (without underscores) " << std::endl;
    std::cout << totalCharacters << std::endl << std::endl;

    outputFile << "Total number of characters in all strings (without \"_\"): " << totalCharacters << std::endl << std::endl;

    //Создаём вектор длин строк
    //Для каждой строки после всех преобразований запоминаем её длину
    std::vector<int> lineLengths;
    for (const auto& line : linesAfterReplace) {
        lineLengths.push_back(static_cast<int>(line.length()));
    }

    std::cout << "Vector of string lengths " << std::endl;
    for (size_t i = 0; i < lineLengths.size(); ++i) {
        std::cout << lineLengths[i];
        if (i < lineLengths.size() - 1) std::cout << " ";
    }
    std::cout << std::endl << std::endl;

    outputFile << "Vector of string lengths:" << std::endl;
    for (size_t i = 0; i < lineLengths.size(); ++i) {
        outputFile << lineLengths[i];
        if (i < lineLengths.size() - 1) outputFile << " ";
    }
    outputFile << std::endl;

    outputFile.close();

    std::cout << "Results have been written to output.txt" << std::endl;

    return 0;
}