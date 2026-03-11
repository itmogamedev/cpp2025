#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <memory>
#include "Shop.h"

class fileReader {
public:
    static std::vector<shop> readShopsFromFile(const std::string& file_name);
};

#endif